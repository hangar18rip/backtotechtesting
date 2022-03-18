<?php
// *****************************************************************************
// Copyright 2003-2006 by A J Marston <http://www.tonymarston.net>
// Distributed under the GNU General Public Licence
// *****************************************************************************

// name = std.update1.inc

// type = update1

// This will allow a single database row to be displayed and updated.
// The primary key of the row is passed in $where from the previous screen.
// If multiple entries were selected in the prevous screen then a scrollbar
// will be made available for the user to scroll between these entries.

require_once 'include.general.inc';

// identify mode for xsl file
$mode = 'update';
$pattern_id = 'upd1';

// load session variables
initSession();

if (isset($_POST['quit']) or (isset($_POST['quit_x']))) {
    // cancel this screen, return to previous screen
    scriptPrevious(null, null, 'quit');
} // if

// define action buttons
$act_buttons['submit'] = 'submit';
$act_buttons['quit']   = 'cancel';

// create a class instance for the main database table
require_once "classes/$table_id.class.inc";
if (isset($script_vars['dbobject'])) {
    // use data from previous instance for this script
    $dbobject = unserialize($script_vars['dbobject']);
    // get previous data
    $fieldarray = $dbobject->getFieldArray();
} else {
    // create new instance for initial activation of this script
    $dbobject = new $table_id;
    $dbobject->sql_select = &$sql_select;
    $dbobject->sql_from = &$sql_from;
    $dbobject->sql_where = &$sql_where;
    $dbobject->sql_groupby = &$sql_groupby;
    $dbobject->sql_having = &$sql_having;
    // check that primary key is complete
    $dbobject->checkPrimaryKey = true;
} // if

if ($_SERVER['REQUEST_METHOD'] == 'GET') {
    // check if we are returning from a child form
    if (!empty($return_from)) {
        if ($return_action == 'choose' AND !empty($selection)) {
            // merge previous saved variables with selection from popup form
            $fieldarray = $dbobject->popupReturn($fieldarray, basename($return_from), $selection);
            $errors     = array_merge($errors, $dbobject->getErrors());
        } // if
        // some data may have been changed in the child form, so refresh it
        $fieldarray = $dbobject->getExtraData($fieldarray);
    } else {
        if (!empty($selection)) {
            // retrieve profile has been passed down from previous screen
            $where = $selection;
            $selection = null;
        } else {
            if (isset($scrolling)) {
                // retrieve values from scrolling array
                $where = $scrolling[$dbobject->getClassName()]['where'];
                $dbobject->setPageNo($scrolling[$dbobject->getClassName()]['curitem']);
            } // if
        } // if
        if (empty($where)) {
            scriptPrevious(getLanguageText('sys0081')); // 'Nothing has been selected yet.'
        } // if
        $dbobject->setRowsPerPage(1); // scroll through one item at a time
        if (isset($_GET['scrolling']) AND $_GET['scrolling'] == $dbobject->getClassName()) {
            // set index number of item to be read from current $where list
            $dbobject->setPageNo($_GET['item']);
        } // if
        // get data from the database
        $fieldarray = $dbobject->getData($where);
        if ($dbobject->errors) {
            // some sort of error - return to previous script
            scriptprevious($dbobject->getErrors(), $messages);
        } // if
        if ($dbobject->getNumRows() < 1) {
            scriptPrevious(getLanguageText('sys0085')); // 'Nothing retrieved from the database.'
        } // if
        // set variables to be included in XML output
        $scrolling[$dbobject->getClassName()]['curitem'] = $dbobject->getPageNo();
        $scrolling[$dbobject->getClassName()]['lastitem'] = $dbobject->getLastPage();
        $scrolling[$dbobject->getClassName()]['where'] = $where;
        // get any extra data and merge with $fieldarray
        $fieldarray = $dbobject->getExtraData($fieldarray);
        // rebuild selection criteria using primary key of 1st occurrence
        $where = array2where($fieldarray, $dbobject->getPkeyNames(), $dbobject);
    } // if
    unset($script_vars['selection']);
    $script_vars['where']     = $where;
    $script_vars['dbobject']  = serialize($dbobject);
    $script_vars['scrolling'] = $scrolling;
    $_SESSION[$_SERVER['PHP_SELF']] = $script_vars;
} // if

// look for entered data
if ($_SERVER['REQUEST_METHOD'] == 'POST') {
    // merge original data with POSTed data (so that fields which were displayed
    // but not POSTed are sent back if any errors are displayed).
    $fieldarray = array_update_associative($fieldarray, $_POST);
    // look for an action which is another script
    $errors = childForm($_POST, $dbobject, 'dbobject', $where, $fieldarray);
    if (empty($errors)) {
        $dbobject->startTransaction();
        // update this data in the database
        $fieldarray = $dbobject->updateRecord($fieldarray);
        if ($dbobject->errors) {
			// errors are keyed by object name
		    $errors[$dbobject->getClassName()] = $dbobject->getErrors();
		} // if
        if (empty($errors)) {
            $errors = $dbobject->commit();
        } // if
        if (!empty($errors)) {
            $dbobject->rollback();
        } else {
            if ($scrolling[$dbobject->getClassName()]['lastitem'] <= 1) {
                // update was OK - return to previous screen
                scriptPrevious(null, null, 'OK');
            } else {
                $messages[] = getLanguageText('sys0092'); // 'Record updated OK'
                // re-read database in case any other values have been changed
                $fieldarray = $dbobject->getData($where);
                // get any extra data and merge with $fieldarray
                $fieldarray = $dbobject->getExtraData($fieldarray);
                // save current data in session array
                $script_vars['dbobject'] = serialize($dbobject);
                $_SESSION[$_SERVER['PHP_SELF']] = $script_vars;
            } // if
        } // if
    } // if
} // if

// build list of objects for output to XML data
$xml_objects[]['root'] = &$dbobject;

// build XML document and perform XSL transformation
buildXML($xml_objects, $errors, $messages);
exit;

?>

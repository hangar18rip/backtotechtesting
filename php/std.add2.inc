<?php
// *****************************************************************************
// Copyright 2003-2006 by A J Marston <http://www.tonymarston.net>
// Distributed under the GNU General Public Licence
// *****************************************************************************

// name = std.add2.inc

// type = add2

// This will add an occurrence to the MANY entity in a ONE-to-MANY relationship
// with the ONE's identity passed in $where

require_once 'include.general.inc';

// identify mode for xsl file
$mode = 'insert';
$pattern_id = 'add2';

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
    if (is_long(key($fieldarray))) {
        // indexed by row, so use row zero only
        $fieldarray = $fieldarray[0];
    } // if
} else {
    // create new instance for initial activation of this script
    $dbobject = new $table_id;
    if (!empty($selection)) {
        // retrieve profile has been passed down from previous screen
        $where     = $selection;
        $selection = null;
    } // if
    // get initial data for a new record
    $fieldarray = $dbobject->getInitialData($where);
    if ($dbobject->errors) {
        scriptPrevious($dbobject->getErrors(), $messages);
    } // if
    // get any extra data and merge with $fieldarray
    $fieldarray = $dbobject->getExtraData($fieldarray);
} // if

if ($_SERVER['REQUEST_METHOD'] == 'GET') {
    // check if we are returning from a child form
    if (!empty($return_from)) {
        if ($return_action == 'choose' AND !empty($selection)) {
            // merge previous saved variables with selection from popup form
            $fieldarray = $dbobject->popupReturn($fieldarray, basename($return_from), $selection);
            $errors     = array_merge($errors, $dbobject->getErrors());
        } // if
    } // if
    if (empty($where)) {
        scriptPrevious(getLanguageText('sys0082')); // 'No parent has been selected yet.'
    } // if
    unset($script_vars['selection']);
    $script_vars['where']    = $where;
    $script_vars['dbobject'] = serialize($dbobject);
    $_SESSION[$_SERVER['PHP_SELF']] = $script_vars;
} // if

// look for entered data
if ($_SERVER['REQUEST_METHOD'] == 'POST') {
    if (isset($_POST['paste']) or (isset($_POST['paste_x']))) {
        // refetch initial data for primary key fields
        $fieldarray = $dbobject->getInitialData($where);
        // merge initial data with previously saved data
        $fieldarray = array_merge_nonkey($dbobject->fieldspec, $fieldarray, $_SESSION['data'][$table_id]);
        $fieldarray = $dbobject->getExtraData($fieldarray);
    } else {
        // merge original data with user's input (so that fields which were displayed
        // but not POSTed are sent back if any errors are displayed).
        $fieldarray = array_update_associative($fieldarray, $_POST);
        // look for an action which is another script
        $errors = childForm($_POST, $dbobject, 'dbobject', $where, $fieldarray);
        if (empty($errors)) {
            $dbobject->startTransaction();
            // add this data to the database
            $fieldarray = $dbobject->insertRecord($fieldarray);
            if ($dbobject->errors) {
				// errors are keyed by object name
			    $errors[$dbobject->getClassName()] = $dbobject->getErrors();
			} // if
            if (empty($errors)) {
                $errors = $dbobject->commit();
                // update was OK - return to previous screen
                scriptPrevious(null, null, 'OK');
            } else {
                $dbobject->rollback();
            } // if
        } // if
    } // if
} // if

if (isset($_SESSION['data'][$table_id])) {
    // saved data exists, so allow a PASTE button
    $prepend = array('paste' => 'paste');
    $act_buttons = array_merge($prepend, $act_buttons);
} // if

// build list of objects for output to XML data
$xml_objects[]['root'] = &$dbobject;

// build XML document and perform XSL transformation
buildXML($xml_objects, $errors, $messages);
exit;

?>

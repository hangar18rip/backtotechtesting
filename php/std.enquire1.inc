<?php
// *****************************************************************************
// Copyright 2003-2006 by A J Marston <http://www.tonymarston.net>
// Distributed under the GNU General Public Licence
// *****************************************************************************

// name = std.enquire1.inc
// type = enquire1

// This will display a sngle selected database occurrence using $where
// (as supplied from the previous screen)

require_once 'include.general.inc';

// identify mode for xsl file
$mode = 'read';
$pattern_id = 'enq1';

// load session variables
initSession();

// look for a button being pressed
if ($_SERVER['REQUEST_METHOD'] == 'POST') {
    if (isset($_POST['quit']) or (isset($_POST['quit_x']))) {
        // cancel this screen, return to previous screen
        scriptPrevious();
    } // if
} // if

// define action buttons
$act_buttons['quit'] = 'close';

// create a class instance for the main database table
require_once "classes/$table_id.class.inc";
$dbobject = new $table_id;

$dbobject->sql_select  = &$sql_select;
$dbobject->sql_from    = &$sql_from;
$dbobject->sql_where   = &$sql_where;
$dbobject->sql_groupby = &$sql_groupby;
$dbobject->sql_having  = &$sql_having;
// check that primary key is complete
$dbobject->checkPrimaryKey = true;
// scroll through one item at a time
$dbobject->setRowsPerPage(1);

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

if (isset($_GET['scrolling']) AND $_GET['scrolling'] == $dbobject->getClassName()) {
    // set index number of item to be read from current $where list
    $dbobject->setPageNo($_GET['item']);
} // if

// get data from the database
$fieldarray = $dbobject->getData($where);

if ($dbobject->getErrors()) {
    // some sort of error - return to previous script
    scriptprevious($dbobject->getErrors(), $messages);
} // if

// check number of rows returned
if ($dbobject->getNumRows() < 1) {
    scriptPrevious(getLanguageText('sys0085')); // 'Nothing retrieved from the database.'
} // if

// set variables to be included in XML output
$scrolling[$dbobject->getClassName()]['curitem']  = $dbobject->getPageNo();
$scrolling[$dbobject->getClassName()]['lastitem'] = $dbobject->getLastPage();
$scrolling[$dbobject->getClassName()]['where']    = $where;

unset($script_vars['selection']);
$script_vars['where']     = $where;
$script_vars['scrolling'] = $scrolling;
$_SESSION[$_SERVER['PHP_SELF']] = $script_vars;

// get any extra data and merge with $fieldarray (using only first row)
$fieldarray = $dbobject->getExtraData($fieldarray);

// rebuild selection using primary key of retrieved row
$where = array2where($fieldarray, $dbobject->getPkeyNames(), $dbobject);

if (!empty($_POST)) {
    // look for an action which is another script
    $errors = childForm($_POST, $dbobject, 'dbobject', $where, $fieldarray);
} // if

// build list of objects for output to XML data
$xml_objects[]['root'] = &$dbobject;

// build XML document and perform XSL transformation
buildXML($xml_objects, $errors, $messages);
exit;

?>

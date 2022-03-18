<?php
// *****************************************************************************
// Copyright 2003-2006 by A J Marston <http://www.tonymarston.net>
// Distributed under the GNU General Public Licence
// *****************************************************************************

// name = std.list2.inc

// type = list2

// This will list rows of MANY in a ONE-to-MANY relationship.
// The primary key of ONE will be passed in $where from the previous screen.

require_once 'include.general.inc';

// identify mode for xsl file
$mode = 'read';
$pattern_id = 'list2';

// load session variables
initSession();

if (isset($_POST['quit']) or (isset($_POST['quit_x']))) {
    // the 'quit' button has been pressed, so ...
    // clear this script from session details and return to previous page
    if (isset($act_buttons) AND array_key_exists('choose', $act_buttons)) {
        scriptPrevious('Nothing selected from popup screen.');
    } else {
        scriptPrevious();
    } // if
} // if

// define action buttons
$act_buttons['reset'] = 'reset';
$act_buttons['quit']  = 'close';

// create a class instance for the inner database table
require_once "classes/$inner_table.class.inc";
if (isset($script_vars['dbinner'])) {
    // use previous instance from session data
    $dbinner = unserialize($script_vars['dbinner']);
} else {
    // create new instance for initial activation of this script
    $dbinner = new $inner_table;
    $dbinner->sql_select  = &$inner_sql_select;
    $dbinner->sql_from    = &$inner_sql_from;
    $dbinner->sql_where   = &$inner_sql_where;
    $dbinner->sql_groupby = &$inner_sql_groupby;
    $dbinner->sql_having  = &$inner_sql_having;
    $dbinner->setDefaultOrderby($inner_sql_orderby);
} // if

// the 'choose' button should only be used in popup screens
if (isset($_POST['choose']) or (isset($_POST['choose_x']))) {
    $messages = chooseButton($_POST, $dbinner);
} // if

if (!empty($_POST)) {
    // look for an action which is another script
    $errors = childForm($_POST, $dbinner, 'dbinner', $where);
} // if

// create a class instance for the outer database table
require_once "classes/$outer_table.class.inc";
if (isset($script_vars['dbouter'])) {
    // use previous instance from session data
    $dbouter = unserialize($script_vars['dbouter']);
    // get data from previous instance
    $outer_data = $dbouter->getFieldArray();
    if (!is_string(key($outer_data))) {
        // indexed by row, so use first row only
        $outer_data = $outer_data[key($outer_data)];
    } // if
} else {
    // create new instance for initial activation of this script
    $dbouter = new $outer_table;
    $dbouter->sql_select  = &$outer_sql_select;
    $dbouter->sql_from    = &$outer_sql_from;
    $dbouter->sql_where   = &$outer_sql_where;
    $dbouter->sql_groupby = &$outer_sql_groupby;
    $dbouter->sql_having  = &$outer_sql_having;
    $dbouter->setDefaultOrderby($outer_sql_orderby);
    // check that primary key is complete
    $dbouter->checkPrimaryKey = true;
    // scroll through one item at a time
    $dbouter->setRowsPerPage(1);
} // if

if (!empty($selection)) {
    // retrieve profile has been passed down from previous screen
    $where = $selection;
    $selection = null;
} else {
    if (isset($scrolling)) {
        // retrieve values from scrolling array
        $where = $scrolling[$dbouter->getClassName()]['where'];
        $dbouter->setPageNo($scrolling[$dbouter->getClassName()]['curitem']);
    } // if
} // if

if (empty($where)) {
    scriptPrevious(getLanguageText('sys0082')); // 'No parent has been selected yet.'
} // if

if (isset($_GET['scrolling']) AND $_GET['scrolling'] == $dbouter->getClassName()) {
    // set index number of item to be read from current $where list
    $dbouter->setPageNo($_GET['item']);
} // if

// get data for the outer table
$outer_data = $dbouter->getData($where);
if ($dbouter->getErrors()) {
    // some sort of error
    if ($dbouter->getLastPage() <= 1) {
        // only 1 entry requested, so return to previous script
        scriptprevious($dbouter->getErrors(), $messages);
    } else {
        // multiple entries requested, so display error message
        $errors = $dbouter->getErrors();
    } // if
} // if

if ($dbouter->getNumRows() < 1) {
    scriptPrevious(getLanguageText('sys0090', strtoupper($dbouter->getTableName()))); // 'Nothing retrieved from database table $outer'
} // if

// set variables to be included in XML output
$scrolling[$dbouter->getClassName()]['curitem']  = $dbouter->getPageNo();
$scrolling[$dbouter->getClassName()]['lastitem'] = $dbouter->getLastPage();
$scrolling[$dbouter->getClassName()]['where']    = $where;

// get any extra data and merge with $outer_data
$outer_data = $dbouter->getExtraData($outer_data);

// get primary key of row retrieved from OUTER entity
$where = array2where($outer_data, $dbouter->getPkeyNames(), $dbouter);

if (isset($_SESSION['rowsperpage'])) {
    $dbinner->setRowsPerPage($_SESSION['rowsperpage']);
} // if

if (isset($_GET['pagesize'])) {
    $dbinner->setRowsPerPage($_GET['pagesize']);
    $_SESSION['rowsperpage'] = $_GET['pagesize'];
} // if

// obtain the required page number (optional)
if (isset($_GET['page'])) {
    $dbinner->setPageNo($_GET['page']);
} // if

// obtain the 'orderby' field (optional)
if (isset($_GET['orderby'])) {
    if (isset($screen)) {
    	if (validateSortItem('inner', $_GET['orderby'], $dbinner, $screen)) {
        	$dbinner->setOrderBy($_GET['orderby'], $dbinner->sql_orderby_seq);
        } // if
    } else {
        $dbinner->setOrderBy($_GET['orderby'], $dbinner->sql_orderby_seq);
    } // if
} // if

// load optional criteria from search screen
if (isset($search)) {
    $dbinner->setSqlSearch($search);
} // if

// the '_x' suffix is returned if the button is changed to an image
if (isset($_POST['reset']) or (isset($_POST['reset_x']))) {
    // initialise all settings to start afresh
    $dbinner->setPageNo(null);
    $dbinner->setOrderBy(null);
    $dbinner->setOrderBySeq(null);
    $dbinner->setSqlSearch(null);
} // if

// get data from the database
$inner_data = $dbinner->getData($where);

if ($dbinner->getErrors()) {
    $errors = array_merge($errors, $dbinner->getErrors());
} // if
if ($dbinner->getNumRows() == 0) {
    $errors[] = getLanguageText('sys0088', strtoupper($inner_table)); // 'no entries found on $inner_table'
} // if

// get any additional data for current record
$inner_data = $dbinner->getExtraData($inner_data);

if (isset($_GET['action'])) {
    $fieldarray = $dbinner->setAction($_GET['action']);
} // if

// $where may have been changed in database object
$where = $dbinner->getWhere();

// get pagination details
$pagination['inner']['numrows']  = $dbinner->getNumRows();
$pagination['inner']['curpage']  = $dbinner->getPageNo();
$pagination['inner']['lastpage'] = $dbinner->getLastPage();

// ensure script variables are available throughout this session
unset($script_vars['selection']);
$script_vars['where']     = unqualifyWhere($where);
$script_vars['dbouter']   = serialize($dbouter);
$script_vars['dbinner']   = serialize($dbinner);
$script_vars['scrolling'] = $scrolling;
$_SESSION[$_SERVER['PHP_SELF']] = $script_vars;

// get sort details
$orderby     = $dbinner->getOrderBy();
$orderby_seq = $dbinner->getOrderBySeq($orderby, $dbinner->sql_orderby_seq);

// build list of objects for output to XML data
$xml_objects[]['root'] = &$dbouter;
$xml_objects[][$dbouter->getClassName()] = &$dbinner;

// build XML document and perform XSL transformation
buildXML($xml_objects, $errors, $messages);
exit;

?>

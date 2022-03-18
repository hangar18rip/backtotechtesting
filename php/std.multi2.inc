<?php
// *****************************************************************************
// Copyright 2003-2006 by A J Marston <http://www.tonymarston.net>
// Distributed under the GNU General Public Licence
// *****************************************************************************

// name = std.multi1.inc

// type = multi1

// This will allow multiple MANY occurrences in a ONE-to-MANY relationship to be
// modified in a single operation. The primary key of ONE is passed down in $where.

require_once 'include.general.inc';

// identify mode for xsl file
$mode = 'update';
$pattern_id = 'multi2';

// load session variables
initSession();

if (isset($_POST['quit']) or (isset($_POST['quit_x']))) {
    // clear this script from session details and return to previous page
    scriptPrevious(null, null, 'quit');
} // if

/// define action buttons
$act_buttons['reset']  = 'reset';
$act_buttons['submit'] = 'submit';
$act_buttons['quit']   = 'cancel';

// create a class instance for the inner database table
require_once "classes/$inner_table.class.inc";
if (isset($script_vars['dbinner'])) {
    // use data from previous instance of this script
    $dbinner = unserialize($script_vars['dbinner']);
} else {
    $dbinner = new $inner_table;
    $dbinner->sql_select  = &$inner_sql_select;
    $dbinner->sql_from    = &$inner_sql_from;
    $dbinner->sql_where   = &$inner_sql_where;
    $dbinner->sql_groupby = &$inner_sql_groupby;
    $dbinner->sql_having  = &$inner_sql_having;
} // if

if (!empty($_POST)) {
    // look for an action which is another script
    $errors = childForm($_POST, $dbinner, 'dbinner', $where);
} // if

// look for entered data
if (isset($_POST['submit']) or (isset($_POST['submit_x']))) {
    // retrieve current data
    $inner_data = $dbinner->getFieldArray();
    // update database with changes in POST array
    $dbinner->startTransaction();
    $inner_data = $dbinner->updateMultiple($inner_data, $_POST);
    if ($dbinner->errors) {
        $dbinner->rollback();
        // errors are keyed by object name
        $errors[$dbinner->getClassName()] = $dbinner->getErrors();
    } else {
        // update was OK
        $errors = $dbinner->commit();
        if ($errors) {
        	$dbobject->rollback();
        } else {
            $messages[] = getLanguageText('sys0091'); // 'Update successful'
        } // if
    } // if
} // if

// create a class instance for the outer database table
require_once "classes/$outer_table.class.inc";
if (isset($script_vars['dbouter'])) {
    // use data from previous instance of this script
    $dbouter = unserialize($script_vars['dbouter']);
    // get previously retrieved data
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
    // check that primary key is complete
    $dbouter->checkPrimaryKey = true;
    // set this object to 'noedit'
    $dbouter->xsl_params = array('outer_noedit' => 'y');
} // if

if ($_SERVER['REQUEST_METHOD'] == 'GET') {
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

    $dbouter->setRowsPerPage(1); // scroll through one item at a time
    if (isset($_GET['scrolling']) AND $_GET['scrolling'] == $dbouter->getClassName()) {
        // set index number of item to be read from current $where list
        $dbouter->setPageNo($_GET['item']);
    } // if

    // get data from the outer table
    $outer_data = $dbouter->getData($where);
    if ($dbouter->errors) {
        // some sort of error
        if ($dbouter->getLastPage() <= 1) {
            // only 1 entry requested, so return to previous script
            scriptprevious($dbouter->getErrors(), $messages);
        } else {
            // multiple entries requested, so disable SUBMIT button
            unset($act_buttons['submit']);
            $errors = $dbouter->getErrors();
        } // if
    } // if
    if ($dbouter->getNumRows() < 1) {
        scriptPrevious(getLanguageText('sys0085')); // 'Nothing retrieved from the database.'
    } // if

    // set variables to be included in XML output
    $scrolling[$dbouter->getClassName()]['curitem']  = $dbouter->getPageNo();
    $scrolling[$dbouter->getClassName()]['lastitem'] = $dbouter->getLastPage();
    $scrolling[$dbouter->getClassName()]['where']    = $where;

    // get any extra data and merge with $outer_data
    $outer_data = $dbouter->getExtraData($outer_data);
} // if

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
} else {
    if (!empty($order_by)) {
        $dbinner->setDefaultOrderby($order_by);
    } else {
        $dbinner->setDefaultOrderby($inner_sql_orderby);
    } // if
} // if

// load optional criteria from search screen
if (isset($search)) {
    $dbinner->setSqlSearch($search);
} // if

if (isset($_POST['reset']) or (isset($_POST['reset_x']))) {
    // initialise all settings to start afresh
    $dbinner->setPageNo(null);
    $dbinner->setOrderBy(null);
    $dbinner->setOrderBySeq(null);
    $dbinner->setSqlSearch(null);
} // if

// get primary key of row retrieved from OUTER entity
$where = array2where($outer_data, $dbouter->getPkeyNames(), $dbouter);

// ensure that column names are qualified in the 'where' clause
$null = array();
$inner_where = qualifyWhere($where, $dbouter->tablename, $dbouter->getFieldSpec(), null, null, null, $null);

// if ($_SERVER['REQUEST_METHOD'] == 'GET' OR isset($_POST['reset'])) {
if (empty($errors)) {
    // get data from the database
    $inner_data = $dbinner->getData($inner_where);

    $errors = $dbinner->getErrors();

    if ($dbinner->getNumRows() == 0) {
        $errors[] = getLanguageText('sys0088', strtoupper($inner_table)); // 'No entries found on $inner_table'
        unset($act_buttons['submit']);
    } // if

    // $where may have been changed in database object
    $where = $dbinner->getWhere();
} // if

if (isset($_GET['action'])) {
    $inner_data = $dbinner->setAction($_GET['action']);
} // if

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

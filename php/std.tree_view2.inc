<?php
// *****************************************************************************
// Copyright 2003-2006 by A J Marston <http://www.tonymarston.net>
// Distributed under the GNU General Public Licence
// *****************************************************************************

// name = std.tree_view2.inc

// type = tree view 2

// This will list nodes in a tree structure where the tables involved are:
// TREE_TYPE -> TREE_LEVEL -> TREE_NODE
// Each node belogs to a particular TYPE and LEVEL.
// A node can have only one parent but many children.
// The tree_type to be displayed will be passed in $selection.

require_once 'include.general.inc';

// identify mode for xsl file
$mode = 'read';
$pattern_id = 'tree2';

// load session variables
initSession();

if (isset($_POST['quit']) or (isset($_POST['quit_x']))) {
    // clear this script from session details and return to previous page
    if (isset($act_buttons) AND array_key_exists('choose', $act_buttons)) {
        scriptPrevious('Nothing selected from popup screen.');
    } else {
        scriptPrevious();
    } // if
} // if

// define action buttons
$act_buttons['expand']   = 'expand';
$act_buttons['collapse'] = 'collapse';
$act_buttons['quit']     = 'close';

// create a class instance for the inner database table
require_once "classes/$inner_table.class.inc";
if (isset($script_vars['dbinner'])) {
    // use data from previous instance for this script
    $dbinner = unserialize($script_vars['dbinner']);
} else {
    $dbinner = new $inner_table;
    $dbinner->sql_select  = &$inner_sql_select;
    $dbinner->sql_from    = &$inner_sql_from;
    $dbinner->sql_where   = &$inner_sql_where;
    $dbinner->sql_groupby = &$inner_sql_groupby;
    $dbinner->sql_having  = &$inner_sql_having;
    if (isset($inner_sql_orderby)) {
        $dbinner->setDefaultOrderby($inner_sql_orderby);
    } // if
} // if

// the 'choose' button should only be used in popup screens
if (isset($_POST['choose']) or (isset($_POST['choose_x']))) {
    $messages = chooseButton($_POST, $dbinner);
} // if

if (!empty($_POST)) {
    // look for an action which is another script
    $errors = childForm($_POST, $dbinner, 'dbinner', null);
} // if

// create a class instance for the outer database table
require_once "classes/$outer_table.class.inc";
if (isset($script_vars['dbouter'])) {
    // use data from previous instance for this script
    $dbouter = unserialize($script_vars['dbouter']);
    // build array of primary keys
    $outer_data = $dbouter->getFieldArray();
} else {
    $dbouter = new $outer_table;
    $dbouter->sql_select  = &$outer_sql_select;
    $dbouter->sql_from    = &$outer_sql_from;
    $dbouter->sql_where   = &$outer_sql_where;
    $dbouter->sql_groupby = &$outer_sql_groupby;
    $dbouter->sql_having  = &$outer_sql_having;
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
    // some sort of error - return to previous script
    scriptprevious($dbouter->getErrors(), $messages);
} // if
if ($dbouter->getNumRows() < 1) {
    scriptPrevious(getLanguageText('sys0085')); // 'Nothing retrieved from the database.'
} // if

// set variables to be included in XML output
$scrolling[$dbouter->getClassName()]['curitem']  = $dbouter->getPageNo();
$scrolling[$dbouter->getClassName()]['lastitem'] = $dbouter->getLastPage();
$scrolling[$dbouter->getClassName()]['where']    = $where;

// get primary key of row retrieved from OUTER entity
$where = array2where($outer_data, $dbouter->getPkeyNames(), $dbouter);

// get list of expanded nodes from session data
$expanded = $dbinner->getExpanded();

// look for optional instruction from previous script
if (!empty($instruction)) {
    if (array_key_exists('expand', $instruction)) {
        $expanded[$instruction['expand']] = true;
        unset($instruction['expand']);
    } // if
    // load remaining instructions into the database object
    $dbobject->setInstruction($instruction);
} // if

// look for instruction to expand a single node, or ALL nodes
if (isset($_GET['expand'])) {
    // add this node number to the list
    $expanded[$_GET['expand']] = true;
} // if
if (isset($_POST['expand'])) {
    // remove all nodes from the list
    $expanded = 'ALL';
} // if

// look for instruction to collapse a single node, or ALL nodes
if (isset($_GET['collapse'])) {
    // remove this node number from the list
    if (is_array($expanded)) {
        unset($expanded[$_GET['collapse']]);
    } // if
} // if
if (isset($_POST['collapse'])) {
    // remove all nodes from the list
    $expanded = null;
} // if

// get data for the inner table
// we start with the root node(s) for the selected tree_type
$inner_data = $dbinner->getNodeData($expanded, $where);
// retrieve any errors
$errors = $dbinner->getErrors();

if (count($inner_data) < 1) {
    $errors[] = getLanguageText('sys0088', strtoupper($inner_table)); // 'No entries found on $inner_table'
} // if
if (isset($_GET['action'])) {
    $fieldarray = $dbinner->setAction($_GET['action']);
} // if

// ensure script variables are available throughout this session
unset($script_vars['selection']);
$script_vars['where']     = $where;
$script_vars['dbouter']   = serialize($dbouter);
$script_vars['dbinner']   = serialize($dbinner);
$script_vars['scrolling'] = $scrolling;
$_SESSION[$_SERVER['PHP_SELF']] = $script_vars;

// build list of objects for output to XML data
$xml_objects[]['root'] = &$dbouter;
$xml_objects[][$dbouter->getClassName()] = &$dbinner;

// build XML document and perform XSL transformation
buildXML($xml_objects, $errors, $messages);
exit;

?>

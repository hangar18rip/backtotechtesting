<?php
//*****************************************************************************
// List the contents of the TREE_NODE table and allow the user to choose one or
// more occurrences. The identity of those selected will be returned to the
// previous screen. NOTE: This displays nodes in a tree view. 
//*****************************************************************************

//DebugBreak();
$outer_table = 'tree_type';					    // name of outer table
$inner_table = 'tree_node_jnr';          	    // name of inner table
$screen   = 'tree_structure.list.screen.inc';   // file identifying screen structure

// add 'choose' button to action bar
$act_buttons['choose'] = 'CHOOSE';

// can only select one entry
$select_one = true;
 
require 'std.tree_view2.inc';                   // activate controller

?>

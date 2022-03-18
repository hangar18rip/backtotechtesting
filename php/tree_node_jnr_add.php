<?php
//*****************************************************************************
// Allow occurrences of the TREE_NODE table to be linked to a parent node.
// The identity of the parent (NODE_ID_SNR) is passed from the previous screen while
// the list of child nodes to be linked is provided by a seperate popup screen.
//*****************************************************************************

//DebugBreak();
$table_id = 'tree_node_jnr';			// table name

$popup_screen = 'tree_node_jnr_popup.php';
//$popup_repeat = TRUE;

require 'std.update2.inc';              // activate controller

?>

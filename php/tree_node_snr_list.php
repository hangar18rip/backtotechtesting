<?php
//*****************************************************************************
// Show the selected entry of the TREE_NODE table (as selected in the previous screen)
// and continue showing parent entries until NODE_ID_SNR is empty.
//*****************************************************************************

$outer_table = 'tree_node'; 				    // name of outer table
$inner_table = 'tree_node_snr_s02';        	    // name of inner table
$screen   = 'tree_node_snr.list.screen.inc';    // file identifying screen structure

// identify extra parameters for a JOIN
$outer_sql_select = null;
$outer_sql_from   = null;
$outer_sql_where  = null;
$outer_sql_orderby = 'node_id';

$inner_sql_select = '';
$inner_sql_from   = '';
$inner_sql_where  = '';

// set default sort sequence
$inner_sql_orderby = 'tree_node.node_desc';

require 'std.list2.inc';                        // activate controller

?>

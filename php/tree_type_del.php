<?php
//*****************************************************************************
// This will allow an occurrences of the TREE_TYPE table to be deleted.
// The identity of the selected occurrence is passed down from the previous screen.
//*****************************************************************************

//DebugBreak();
$table_id = "tree_type";                    // table id
$screen   = 'tree_type.detail.screen.inc';  // file identifying screen structure

require 'std.delete1.inc';                  // activate controller

?>

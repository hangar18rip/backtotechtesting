<?php
//*****************************************************************************
// This will allow an occurrences of the PERSON table to be deleted.
// The identity of the selected occurrence is passed down from the previous screen.
//*****************************************************************************

//DebugBreak();
$table_id = "person";                   // table id
$screen   = 'person.detail.screen.inc'; // file identifying screen structure

require 'std.delete1.inc';              // activate controller

?>

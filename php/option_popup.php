<?php
//*****************************************************************************
// List the contents of the X_OPTION table and allow the user to view/modify
// the contents by activating other screens via navigation buttons. 
//*****************************************************************************

//DebugBreak();
$table_id = 'x_option';                 // table name
$screen   = 'option.list.screen.inc';   // file identifying screen structure

$act_buttons['choose'] = 'CHOOSE';      // add 'choose' button to action bar

require 'std.list1.inc';                // activate controller

?>

<?php
//*****************************************************************************
// List the contents of the PERSON table for a particular row of the PERS_TYPE
// table (as selected in the previous screen) and allow the user to view/modify
// the contents by activating other screens via navigation buttons. 
//*****************************************************************************

//DebugBreak();
$outer_table = 'pers_type';                 // name of outer table
$inner_table = 'person';                    // name of inner table
$screen   = 'person.list(a).screen.inc';    // file identifying screen structure

// identify extra parameters for a JOIN
$outer_sql_select  = NULL;
$outer_sql_from    = NULL;
$outer_sql_where   = NULL;
$outer_sql_orderby = NULL;

$inner_sql_select  = NULL;
$inner_sql_from    = NULL;
$inner_sql_where   = NULL;
$inner_sql_orderby = NULL;

$menu_buttons[] = array('button_text' => 'Person', 'task_id' => 'person_list.php');
$menu_buttons[] = array('button_text' => 'Person Type', 'task_id' => 'pers_type_list.php', 'active' => 'y');
$menu_buttons[] = array('button_text' => 'Option', 'task_id' => 'option_list.php');

require 'std.list2.inc';                // activate controller

?>

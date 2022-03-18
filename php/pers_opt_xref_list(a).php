<?php
//*****************************************************************************
// List the contents of the INNER table for a particular row of the OUTER
// table (as selected in the previous screen) and allow the user to view/modify
// the contents by activating other screens via navigation buttons.
//*****************************************************************************

//DebugBreak();
$outer_table = 'person';                     // name of outer table
$inner_table = 'pers_opt_xref';              // name of inner table
$screen   = 'pers_opt_xref.list(a).screen.inc'; // file identifying screen structure

// identify extra parameters for a JOIN
$outer_sql_select  = "person_id, CONCAT(first_name, ' ', last_name) AS person_name";
$outer_sql_from    = NULL;
$outer_sql_where   = NULL;
$outer_sql_orderby = NULL;

$inner_sql_select  = 'pers_opt_xref.option_id, pers_opt_xref.person_id, x_option.option_desc';
$inner_sql_from    = 'pers_opt_xref '.
                     'LEFT JOIN x_option ON (x_option.option_id=pers_opt_xref.option_id) ';
$inner_sql_where   = NULL;
$inner_sql_orderby = 'person_id';

$nav_buttons[] = array('button_text' => 'New', 'task_id' => 'pers_opt_xref_add(a).php', 'context_preselect' => 'N');
$nav_buttons[] = array('button_text' => 'Delete', 'task_id' => 'pers_opt_xref_del.php', 'context_preselect' => 'Y');
$nav_buttons[] = array('button_text' => 'Search', 'task_id' => 'option_search.php', 'context_preselect' => 'N');

require 'std.list2.inc';                    // activate controller

?>

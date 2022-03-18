<?php
//*****************************************************************************
// List the contents of the INNER table for a particular row of the OUTER
// table (as selected in the previous screen) and allow the user to view/modify
// the contents by activating other screens via navigation buttons.
//*****************************************************************************

//DebugBreak();
$outer_table = 'x_option';                     	// name of outer table
$inner_table = 'pers_opt_xref';              	// name of inner table
$screen   = 'pers_opt_xref.list(b).screen.inc'; // file identifying screen structure

// identify extra parameters for a JOIN
$outer_sql_select  = NULL;
$outer_sql_from    = NULL;
$outer_sql_where   = NULL;
$outer_sql_orderby = NULL;

$inner_sql_select  = 'pers_opt_xref.person_id,option_id,first_name,last_name,star_sign';
$inner_sql_from    = 'pers_opt_xref '.
                     'LEFT JOIN person ON (person.person_id=pers_opt_xref.person_id) ';
$inner_sql_where   = NULL;
$inner_sql_orderby = 'option_id';

$nav_buttons[] = array('button_text' => 'New', 'task_id' => 'pers_opt_xref_add(b).php', 'context_preselect' => 'N');
$nav_buttons[] = array('button_text' => 'Delete', 'task_id' => 'pers_opt_xref_del.php', 'context_preselect' => 'Y');
$nav_buttons[] = array('button_text' => 'Search', 'task_id' => 'person_search.php', 'context_preselect' => 'N');

require 'std.list2.inc';                // activate controller

?>

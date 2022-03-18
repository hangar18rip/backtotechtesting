<?php
//*****************************************************************************
// This will allow an occurrences of the LINK table to be added or deleted.
// The identity of the OUTER occurrence is passed down from the previous screen.
// The INNER table is defined using LEFT JOIN from within the LINK table.
// The existence of individual LINK table entries will be shown in a checkbox
// which can be toggled ON to create a record or OFF to delete a record.
//*****************************************************************************

$outer_table = 'x_option';    					// name of outer table
$link_table  = 'pers_opt_xref';       	        // name of link table
$inner_table = 'person';                        // name of inner table
$screen   = 'pers_opt_xref.link(b).screen.inc'; // file identifying screen structure

// identify extra parameters for a JOIN
$outer_sql_select = NULL;
$outer_sql_from   = NULL;
$outer_sql_where  = NULL;

// modify the sql select for the LINK table
$link_sql_select = 'person.first_name, person.last_name, person.star_sign';
$link_sql_from   = '';
$link_sql_where  = '';
$link_sql_orderby = 'option_id';

require 'std.link1.inc';                // activate controller

?>

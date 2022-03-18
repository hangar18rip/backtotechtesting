<?php
//*****************************************************************************
// List the contents of the PERSON table and allow the user to view/modify
// the contents by activating other screens via navigation buttons.
//*****************************************************************************

$table_id = 'person';                   // table name
$screen   = 'person.list.screen.inc';   // file identifying screen structure

// identify extra parameters for a JOIN
$sql_select = 'person.*, pers_type_desc';
$sql_from   = 'person '.
              'LEFT JOIN pers_type ON (person.pers_type_id = pers_type.pers_type_id)';
$sql_where  = '';

require 'std.list1.inc';                // activate controller

?>

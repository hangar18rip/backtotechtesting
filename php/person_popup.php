<?php
//*****************************************************************************
// List the contents of the PERSON table and allow the user to choose one or
// more occurrences. The identity of those selected will be returned to the
// previous screen.
//*****************************************************************************

//DebugBreak();
$table_id = 'person';                   // table name
$screen   = 'person.list.screen.inc';   // file identifying screen structure

// add 'choose' button to action bar
$act_buttons['choose'] = 'CHOOSE';

// identify extra parameters for a JOIN
$sql_select = '*';
$sql_from   = 'person '.
              'LEFT JOIN pers_type ON (pers_type.pers_type_id=person.pers_type_id)';
$sql_where  = '';

require 'std.list1.inc';                // activate controller

?>

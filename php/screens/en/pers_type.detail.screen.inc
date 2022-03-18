<?php
$structure['xsl_file'] = 'std.detail1.xsl';

$structure['tables']['main'] = 'pers_type';

$structure['main']['columns'][] = array('width' => 150);

$structure['main']['fields'][] = array('pers_type_id' => 'Id');
$structure['main']['fields'][] = array('pers_type_desc' => 'Description');
$structure['main']['fields'][] = array('created_date' => 'Created Date');
$structure['main']['fields'][] = array('created_user' => 'Created By');
$structure['main']['fields'][] = array('revised_date' => 'Revised Date');
$structure['main']['fields'][] = array('revised_user' => 'Revised By');

?>
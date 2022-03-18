<?php
$structure['xsl_file'] = 'std.list1.xsl';

$structure['tables']['main'] = 'pers_type';

$structure['main']['columns'][] = array('width' => 10);
$structure['main']['columns'][] = array('width' => 75);
$structure['main']['columns'][] = array('width' => 350);
$structure['main']['columns'][] = array('width' => '*');

$structure['main']['fields'][] = array('selectbox' => 'Select');
$structure['main']['fields'][] = array('pers_type_id' => 'Id');
$structure['main']['fields'][] = array('pers_type_desc' => 'Description');
$structure['main']['fields'][] = array('null' => '');

?>
<?php
$structure['xsl_file'] = 'std.tree.list2.xsl';

$structure['tables']['outer'] = 'tree_type';

$structure['outer']['columns'][] = array('width' => '25%');

$structure['outer']['fields'][] = array('tree_type_desc' => 'Tree Type');

$structure['tables']['inner'] = 'tree_node_jnr';

$structure['inner']['columns'][] = array('width' => 5);

$structure['inner']['fields'][] = array('selectbox' => 'Select');
$structure['inner']['fields'][] = array('node_desc' => 'Node Description', 'nosort' => 'y');

$structure['inner']['node_data_names'] = array('id' => 'node_id',
                                               'desc' => 'node_desc',
                                               'depth' => 'tree_level_seq',
                                               'child_count' => 'child_count',
                                               'expanded' => 'expanded',
                                               'icon' => 'icon');
?>
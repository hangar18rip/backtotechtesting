<?php
    // file created on June 15, 2005, 12:42 pm

    // field specifications for table sample.tree_node
    $fieldspec['node_id']                   = array('type' => 'integer',
                                                    'size' => 5,
                                                    'minvalue' => 0,
                                                    'maxvalue' => 65535,
                                                    'pkey' => 'y',
                                                    'required' => 'y',
                                                    'default' => '0');
    $fieldspec['tree_type_id']              = array('type' => 'string',
                                                    'size' => 8,
                                                    'required' => 'y',
                                                    'uppercase' => 'y');
    $fieldspec['tree_level_id']             = array('type' => 'integer',
                                                    'size' => 3,
                                                    'minvalue' => 0,
                                                    'maxvalue' => 255,
                                                    'required' => 'y',
                                                    'default' => '0');
    $fieldspec['node_desc']                 = array('type' => 'string',
                                                    'size' => 80,
                                                    'required' => 'y');
    $fieldspec['node_id_snr']               = array('type' => 'integer',
                                                    'size' => 5,
                                                    'minvalue' => 0,
                                                    'maxvalue' => 65535,
                                                    'noedit' => 'y');
    $fieldspec['external_code']             = array('type' => 'string',
                                                    'size' => 255,
                                                    'uppercase' => 'y');
    $fieldspec['created_date']              = array('type' => 'datetime',
                                                    'size' => 20,
                                                    'required' => 'y',
                                                    'default' => '2003-01-01 12:00:00',
                                                    'autoinsert' => 'y',
                                                    'noedit' => 'y');
    $fieldspec['created_user']              = array('type' => 'string',
                                                    'size' => 16,
                                                    'autoinsert' => 'y',
                                                    'noedit' => 'y');
    $fieldspec['revised_date']              = array('type' => 'datetime',
                                                    'size' => 20,
                                                    'autoupdate' => 'y',
                                                    'noedit' => 'y');
    $fieldspec['revised_user']              = array('type' => 'string',
                                                    'size' => 16,
                                                    'autoupdate' => 'y',
                                                    'noedit' => 'y');

    // primary key details
    $this->primary_key                      = array('node_id');

    // unique key details
    $this->unique_keys                      = array();

    // child relationship details
    $this->child_relations[]                = array('child' => 'person',
                                                    'type' => 'RES',
                                                    'fields' => array('node_id' => 'node_id'));

    $this->child_relations[]                = array('child' => 'tree_node',
                                                    'alias' => 'x_tree_node_jnr',
                                                    'type' => 'RES',
                                                    'fields' => array('node_id' => 'node_id_snr'));

    // parent relationship details
    $this->parent_relations[]               = array('parent' => 'tree_level',
                                                    'parent_field' => 'tree_level_desc',
                                                    'fields' => array('tree_type_id' => 'tree_type_id',
                                                                      'tree_level_id' => 'tree_level_id'));

    $this->parent_relations[]               = array('parent' => 'tree_node',
                                                    'alias' => 'x_tree_node_snr',
                                                    'parent_field' => 'node_desc AS node_desc_snr',
                                                    'fields' => array('node_id_snr' => 'node_id'));

    $this->parent_relations[]               = array('parent' => 'tree_type',
                                                    'parent_field' => 'tree_type_desc',
                                                    'fields' => array('tree_type_id' => 'tree_type_id'));

    // determines if database updates are recorded in an audit log
    $this->audit_logging                    = FALSE;

    // default sort sequence
    $this->default_orderby                  = 'node_id';

    // finished
?>
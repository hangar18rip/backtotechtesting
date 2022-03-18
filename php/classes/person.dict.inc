<?php
    // file created on July 17, 2005, 4:24 pm

    // field specifications for table sample.person
    $fieldspec['person_id']                 = array('type' => 'string',
                                                    'size' => 8,
                                                    'pkey' => 'y',
                                                    'required' => 'y',
                                                    'uppercase' => 'y');

    $fieldspec['pers_type_id']              = array('type' => 'string',
                                                    'size' => 6,
                                                    'required' => 'y',
                                                    'uppercase' => 'y',
                                                    'control' => 'dropdown',
                                                    'optionlist' => 'pers_type_id');

    $fieldspec['node_id']                   = array('type' => 'integer',
                                                    'size' => 5,
                                                    'minvalue' => 0,
                                                    'maxvalue' => 65535,
                                                    'control' => 'popup',
                                                    'task_id' => 'tree_structure_popup.php',
                                                    'foreign_field' => 'node_desc');

    $fieldspec['nat_ins_no']                = array('type' => 'string',
                                                    'size' => 10,
                                                    'required' => 'y',
                                                    'uppercase' => 'y');

    $fieldspec['first_name']                = array('type' => 'string',
                                                    'size' => 20,
                                                    'required' => 'y');

    $fieldspec['last_name']                 = array('type' => 'string',
                                                    'size' => 30,
                                                    'required' => 'y');

    $fieldspec['initials']                  = array('type' => 'string',
                                                    'size' => 6,
                                                    'uppercase' => 'y');

    $fieldspec['star_sign']                 = array('type' => 'string',
                                                    'size' => 3,
                                                    'required' => 'y',
                                                    'control' => 'dropdown',
                                                    'optionlist' => 'star_sign');

    $fieldspec['email_addr']                = array('type' => 'string',
                                                    'size' => 50,
                                                    'subtype' => 'email');

    $fieldspec['value1']                    = array('type' => 'integer',
                                                    'size' => 6,
                                                    'minvalue' => 0,
                                                    'maxvalue' => 65535);

    $fieldspec['value2']                    = array('type' => 'numeric',
                                                    'size' => 12,
                                                    'precision' => 10,
                                                    'scale' => 2,
                                                    'blank_when_zero' => 'y',
                                                    'minvalue' => 0,
                                                    'maxvalue' => 99999999.99);

    $fieldspec['start_date']                = array('type' => 'date',
                                                    'size' => 12,
                                                    'required' => 'y',
                                                    'default' => '2000-01-01');

    $fieldspec['end_date']                  = array('type' => 'date',
                                                    'size' => 12,
                                                    'default' => '9999-12-31',
                                                    'infinityisnull' => 'y');

    $fieldspec['picture']                   = array('type' => 'string',
                                                    'size' => 40,
                                                    'subtype' => 'image',
                                                    'imagewidth' => 75,
                                                    'imageheight' => 95,
                                                    'control' => 'filepicker',
                                                    'task_id' => 'filepicker.php');

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
    $this->primary_key                      = array('person_id');

    // unique key details
    $this->unique_keys[]                          = array('nat_ins_no');

    // child relationship details
    $this->child_relations[]                = array('child' => 'pers_opt_xref',
                                                    'type' => 'RES',
                                                    'fields' => array('person_id' => 'person_id'));

    // parent relationship details
    $this->parent_relations[]               = array('parent' => 'pers_type',
                                                    'parent_field' => 'pers_type_desc',
                                                    'fields' => array('pers_type_id' => 'pers_type_id'));

    $this->parent_relations[]               = array('parent' => 'tree_node',
                                                    'parent_field' => 'node_desc',
                                                    'fields' => array('node_id' => 'node_id'));

    // determines if database updates are recorded in an audit log
    $this->audit_logging                    = FALSE;

    // default sort sequence
    $this->default_orderby                  = 'person.last_name';

    // finished
?>
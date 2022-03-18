<?php
    // file created on June 15, 2005, 12:42 pm
    
    // field specifications for table sample.pers_opt_xref
    $fieldspec['person_id']                 = array('type' => 'string',
                                                    'size' => 8,
                                                    'pkey' => 'y',
                                                    'required' => 'y',
                                                    'uppercase' => 'y',
                                                    'noedit' => 'y');
    $fieldspec['option_id']                 = array('type' => 'string',
                                                    'size' => 8,
                                                    'pkey' => 'y',
                                                    'required' => 'y',
                                                    'uppercase' => 'y',
                                                    'noedit' => 'y');
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
    $this->primary_key                      = array('person_id',
                                                    'option_id');
    
    // unique key details 
    $this->unique_keys                      = array();
    
    // child relationship details 
    $this->child_relations                  = array();
    
    // parent relationship details 
    $this->parent_relations[]               = array('parent' => 'person',
                                                    'parent_field' => 'last_name',
                                                    'fields' => array('person_id' => 'person_id'));
    
    $this->parent_relations[]               = array('parent' => 'x_option',
                                                    'parent_field' => 'option_desc',
                                                    'fields' => array('option_id' => 'option_id'));
    
    // determines if database updates are recorded in an audit log 
    $this->audit_logging                    = FALSE;
    
    // default sort sequence 
    $this->default_orderby                  = '';
    
    // finished
?>
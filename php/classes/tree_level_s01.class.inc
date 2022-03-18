<?php
// *****************************************************************************
// Copyright 2003-2006 by A J Marston <http://www.tonymarston.net>
// *****************************************************************************
require_once 'tree_level.class.inc';
class tree_level_s01 extends tree_level
{
    // ****************************************************************************
    // this class is for use by script: tree_level_multi.php
    // ****************************************************************************

    // ****************************************************************************
    function checkChildNodes ($fieldarray)
    // Find out if the tree_level below the current level has changed...
    // If it has then any children of nodes on the current level must be orphaned.
    {
        if (empty($fieldarray['tree_level_id_jnr'])) {
            // did not have any children before, so ignore
            return;
        } // if

        $tree_type_id      = $fieldarray['tree_type_id'];
        $tree_level_id     = $fieldarray['tree_level_id'];
        $tree_level_id_jnr = $fieldarray['tree_level_id_jnr'];

        // create a new object to deal with child nodes
        $dbobject =& singleton::getInstance('tree_level');

        $dbobject->sql_select = "tree_level.tree_type_id, tree_level.tree_level_id, t2.tree_level_id as tree_level_id_jnr";
        $dbobject->sql_from = "tree_level LEFT JOIN tree_level AS t2 ON (t2.tree_type_id = tree_level.tree_type_id AND t2.tree_level_seq = (tree_level.tree_level_seq +1))";
        $where  = "tree_level.tree_type_id='$tree_type_id' AND tree_level.tree_level_id='$tree_level_id'";
        $newdata = $this->_dml_getdata($where);

        if ($newdata[0]['tree_level_id_jnr'] <> $tree_level_id_jnr) {
            // child level has changed, so update all nodes in previous child level
            require_once 'classes/tree_node.class.inc';
            $dbnode =& singleton::getInstance('tree_node');
            $where = "tree_type_id='$tree_type_id' AND tree_level_id='$tree_level_id_jnr'";
            $replace = "node_id_snr=NULL";
            $count = $dbnode->updateSelection($where, $replace);
        } // if

        return;

    } // checkChildNodes

    // ****************************************************************************
    function _cm_post_updateMultiple ($fieldarray)
    // perform custom processing after multiple database records have been updated.
    {
        // sort the rows according to 'tree_level_seq'
        foreach ($fieldarray as $row) {
            // create a new array indexed by 'tree_level_seq'
            $sortedarray[$row['tree_level_seq']] = $row;
        } // foreach

        ksort($sortedarray);            // sort this array
        $fieldarray = $sortedarray;     // replace original array

        foreach ($fieldarray as $rowdata) {
            // check child nodes in case they need to be updated
            $result = $this->checkChildNodes($rowdata);
            if ($this->errors) return $fieldarray;
        } // foreach

        return $fieldarray;

    } // _cm_post_updateMultiple

    // ****************************************************************************
    function _cm_pre_getData ($where, $where_array, $fieldarray=null)
    // perform custom processing before database record(s) are retrieved.
    // (WHERE is supplied in two formats - string and array)
    // $fieldarray may contain full details of the current record in the parent
    // class, not just its primary key.
    {
        // perform standard processing in the parent class
        $where = parent::_cm_pre_getData($where, $where_array);

        // unset rows_per_page for maintenance screen
        $this->rows_per_page = 0;

        // allow this field to be edited
        unset($this->fieldspec['tree_level_seq']['noedit']);

        // selection criteria must be limited to 'tree_type'
        $array1 = where2array($where);
        if (isset($array1['tree_type.tree_type_id'])) {
        	$array2['tree_type_id'] = $array1['tree_type.tree_type_id'];
        } else {
            $array2['tree_type_id'] = $array1['tree_type_id'];
        } // if
        $where = array2where($array2, $this->fieldspec);

        // include details of current junior level (if there is one)
        $this->sql_select = 'tree_level.tree_type_id,'
                          . 'tree_level.tree_level_id,'
                          . 'tree_level.tree_level_seq,'
                          . 'tree_level.tree_level_desc,'
                          . 't2.tree_level_id as tree_level_id_jnr,'
                          . 't2.tree_level_seq as tree_level_seq_jnr';
        $this->sql_from = 'tree_level LEFT JOIN tree_level AS t2 ON (t2.tree_type_id = tree_level.tree_type_id AND t2.tree_level_seq = (tree_level.tree_level_seq +1))';
        $this->sql_where = '';

        // these ields must be display only
        $this->fieldspec['tree_level_id']['noedit']   = 'y';
        $this->fieldspec['tree_level_desc']['noedit'] = 'y';

        return $where;

    } // _cm_pre_getData

    // ****************************************************************************
    function _cm_pre_updateMultiple ($fieldarray)
    // perform custom processing before multiple database records are updated.
    {
        $spec = $this->fieldspec['tree_level_seq'];

        // check that each update is valid
        $count = count($fieldarray);
        $used  = array();
        foreach ($fieldarray as $rownum => $rowdata) {
        	$seq = $rowdata['tree_level_seq'];
            if (strlen($seq) == 0) {
                // 'Cannot be empty'
                $this->errors[$rownum]['tree_level_seq'] = getLanguageText('e0004');
            } elseif (strlen($seq) > $spec['size']) {
                // "Value too large ($spec[size])"
                $this->errors[$rownum]['tree_level_seq'] = getLanguageText('e0005', $spec[size]);
            } elseif (strcmp($seq, (int)$seq)) {
                // 'Must be an integer'
                $this->errors[$rownum]['tree_level_seq'] = getLanguageText('e0006');
            } elseif (intval($seq) < 1) {
                // 'Must be greater than 0'
                $this->errors[$rownum]['tree_level_seq'] = getLanguageText('e0007');
            } elseif (intval($seq) > $count) {
                // "Must not be greater than $count"
                $this->errors[$rownum]['tree_level_seq'] = getLanguageText('e0008', $count);
            } // if

            // make sure that each value is used no more than once
            if (array_key_exists($seq, $used)) {
                // 'Value has already been used'
                $this->errors[$rownum]['tree_level_seq'] = getLanguageText('e0009');
            } else {
                $used[$seq] = 'y';
            } // if
        } // foreach

        return $fieldarray;

    } // _cm_pre_updateMultiple

// ****************************************************************************
} // end class
// ****************************************************************************

?>

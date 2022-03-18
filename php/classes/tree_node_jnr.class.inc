<?php
// *****************************************************************************
// Copyright 2003-2006 by A J Marston <http://www.tonymarston.net>
// *****************************************************************************
require_once 'tree_node.class.inc';
class tree_node_jnr extends tree_node
{
    // ****************************************************************************
    function _cm_deleteSelection ($selection)
    // delete/update a selection of records.
    {
        // $where must contain at least one occurrence of 'node_id='
        if (substr_count($selection, 'node_id=') < 1) {
            // 'Nothing has been selected yet'
            return getLanguageText('sys0081');
        } // if

        // delete relationships by setting NODE_ID_SNR to NULL on selected records.
        $count = $this->_dml_updateSelection($selection, 'node_id_snr=NULL');

        // "$count records were updated"
        return getLanguageText('sys0006', $count, $this->tablename);

    } // _cm_deleteSelection

    // ****************************************************************************
    function _cm_getNodeData ($expanded, $where, $wherearray = null)
    // retrieve requested node data from the database.
    // $expanded may be a list of nodes to be expanded, or 'ALL' nodes.
    // $where may contain specific selection criteria as a string.
    // $wherearray is $where but converted into an array.
    {
        $this->sql_select  = 'tree_node.node_id, tree_node.node_desc, tree_level.tree_level_seq, COUNT(child.node_id) AS child_count';
        $this->sql_from    = 'tree_node '
                           . 'LEFT JOIN tree_level ON (tree_level.tree_type_id=tree_node.tree_type_id AND tree_level.tree_level_id=tree_node.tree_level_id) '
                           . 'LEFT JOIN tree_node AS child ON (tree_node.node_id=child.node_id_snr) ';
        $this->sql_where   = 'tree_level.tree_type_id=tree_node.tree_type_id AND tree_level.tree_level_id=tree_node.tree_level_id';
        $this->sql_groupby = 'tree_node.node_id, tree_node.node_desc, tree_level.tree_level_seq';
        $this->sql_having  = '';
        $this->sql_orderby = 'tree_node.tree_level_id, tree_node.node_id';

        if (array_key_exists('tree_type_id', $wherearray)) {
            // look for root nodes within this tree_type
            $wherearray['tree_level_seq'] = 1;
            $where = array2where($wherearray);
        } // if

        $data_raw = $this->getData($where);

        foreach ($data_raw as $row => $rowdata) {
            // append data for current node to output array
            $css_array = array();
            $fieldarray[] = $this->formatData($rowdata, $css_array);
            $node_id = $rowdata['node_id'];
            if ($rowdata['child_count'] > 0) {
                // child nodes exist, but do we expand them?
                if ($expanded == 'ALL' or array_key_exists($node_id, $expanded)) {
                    // tell system this row has been expanded
                    $fieldarray[count($fieldarray)-1]['expanded'] = 'y';
                    // this replaces 'ALL' with a list of actual nodes
                    $this->expanded[$node_id] = true;
                    // get the child nodes belonging to this parent node
                    $childdata = $this->getNodeData($expanded, "node_id_snr='$node_id'");
                    // add in child data after the parent
                    $fieldarray = array_merge($fieldarray, $childdata);
                } else {
                    unset($this->expanded[$node_id]);
                } // if
            } // if
        } // foreach

        unset($data_raw);

        return $fieldarray;

    } // _cm_getNodeData

    // ****************************************************************************
    function _cm_updateSelection ($selection, $replace)
    // update multiple records in a single operation
    {
        $replace = str_replace('node_id=', 'node_id_snr=', $replace);

        $count = $this->_dml_updateSelection($selection, $replace);

        // "$count records were updated"
        return getLanguageText('sys0006', $count, $this->tablename);

    } // _cm_updateSelection

// ****************************************************************************
} // end class
// ****************************************************************************

?>

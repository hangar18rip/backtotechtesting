<?php
// *****************************************************************************
// Copyright 2003-2006 by A J Marston <http://www.tonymarston.net>
// *****************************************************************************
require_once 'tree_node.class.inc';
class tree_node_snr extends tree_node
{
    // ****************************************************************************
    function _cm_pre_getData ($where, $where_array, $fieldarray=null)
    // perform custom processing before database record(s) are retrieved.
    // (WHERE is supplied in two formats - string and array)
    // $fieldarray may contain full details of the current record in the parent
    // class, not just its primary key.
    {
        $this->default_orderby = null;

        // convert selection from 'node_id_snr=x' to 'node_id=x'
        $where = str_replace('node_id_snr=', 'node_id=', $where);

        if (empty($this->sql_select)) {
            // include columns from foreign table
            $this->sql_select = 'tree_node.*, tree_type.tree_type_desc, tree_level.tree_level_desc, tree_level.tree_level_seq';
            $this->sql_from   = 'tree_node '
                               .'LEFT JOIN tree_type ON (tree_type.tree_type_id = tree_node.tree_type_id) '
                               .'LEFT JOIN tree_level ON (tree_level.tree_level_id = tree_node.tree_level_id AND tree_level.tree_type_id = tree_node.tree_type_id)';
        } // if

        return $where;

    } // _cm_pre_getData

// ****************************************************************************
} // end class
// ****************************************************************************

?>

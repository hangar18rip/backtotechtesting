<?php
// *****************************************************************************
// Copyright 2003-2006 by A J Marston <http://www.tonymarston.net>
// *****************************************************************************
require_once 'tree_node.class.inc';
class tree_node_jnr_s02 extends tree_node
{
    // ****************************************************************************
    // This subtype is for script: tree_node_jnr_list.php
    // ****************************************************************************
    function _cm_pre_getData ($where, $where_array, $fieldarray=null)
    // perform custom processing before database record(s) are retrieved.
    // (WHERE is supplied in two formats - string and array)
    // $fieldarray may contain full details of the current record in the parent
    // class, not just its primary key.
    {
        // change criteria to look for children of the selected node
        $where = str_replace('node_id=', 'node_id_snr=', $where);

        return $where;

    } // _cm_pre_getData

// ****************************************************************************
} // end class
// ****************************************************************************

?>

<?php
// *****************************************************************************
// Copyright 2003-2006 by A J Marston <http://www.tonymarston.net>
// *****************************************************************************
require_once 'tree_node_snr.class.inc';
class tree_node_snr_s01 extends tree_node_snr
{
    // ****************************************************************************
    // this subtype is for script: tree_node_jnr_list.php
    // ****************************************************************************
    function _cm_post_getData ($rowdata, &$where)
    // perform custom processing after database record(s) are retrieved.
    // NOTE: $where is passed BY REFERENCE so that it may be modified.
    {
        if (!empty($rowdata)) {

            // check that the TREE_LEVEL has another level below it
            $tree_type_id   = $rowdata[0]['tree_type_id'];
            $tree_level_seq = $rowdata[0]['tree_level_seq'];
            $tree_level_seq++;
            $where2 = "tree_type_id='$tree_type_id' AND tree_level_seq='$tree_level_seq'";
            require_once 'classes/tree_level.class.inc';
            $dbobject =& singleton::getInstance('tree_level');
            $tree_level_data = $dbobject->getData($where2);
            if ($dbobject->numrows <> 1) {
                // 'This is the lowest level - no children allowed'
                $this->errors[] = getLanguageText('e0003');
                return $rowdata;
            } // if

        } // if

        return $rowdata;

    } // _cm_post_getData

// ****************************************************************************
} // end class
// ****************************************************************************

?>

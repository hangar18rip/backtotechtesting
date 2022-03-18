<?php
// *****************************************************************************
// Copyright 2003-2017 by A J Marston <http://www.tonymarston.net>
// *****************************************************************************
require_once 'std.table.class.inc';
class pers_opt_xref extends Default_Table
{
    // ****************************************************************************
    function __construct ()
    {
        // save directory name of current script
        $this->dirname   = dirname(__file__);

        $this->dbms_engine = $GLOBALS['dbms'];
        $this->dbname      = 'sample';
        $this->tablename   = 'pers_opt_xref';

        // call this method to get original field specifications
        // (note that they may be modified at runtime)
        $this->fieldspec = $this->getFieldSpec_original();

    } // __construct

    // ****************************************************************************
    function _cm_getExtraData($where, $fieldarray)
    // Perform custom processing for the getExtraData method.
    // $where = a string in SQL 'where' format.
    // $fieldarray = the contents of $where as an array.
    {
        if (preg_match('/star_sign/i', $this->sql_select, $regs)) {
            // add star_sign to field list
            $this->fieldspec['star_sign']   = array('type' => 'string',
                                                    'noedit' => 'y',
                                                    'control' => 'dropdown',
                                                    'optionlist' => 'star_sign');
            // get lookup list for star_sign
            require_once "person.class.inc";
            $dbobject =& singleton::getInstance('person');
            $data = $dbobject->getValRep('star_sign');
            $this->lookup_data['star_sign'] = $data;
        } // if

        return $fieldarray;

    } // _cm_getExtraData

// ****************************************************************************
} // end class
// ****************************************************************************

?>

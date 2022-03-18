<?php
// *****************************************************************************
// Copyright 2003-2017 by A J Marston <http://www.tonymarston.net>
// *****************************************************************************
require_once 'std.table.class.inc';
class pers_type extends Default_Table
{
    // ****************************************************************************
    function __construct ()
    {
        // save directory name of current script
        $this->dirname   = dirname(__file__);

        $this->dbms_engine = $GLOBALS['dbms'];
        $this->dbname      = 'sample';
        $this->tablename   = 'pers_type';

        // call this method to get original field specifications
        // (note that they may be modified at runtime)
        $this->fieldspec = $this->getFieldSpec_original();

    } // __construct

    // ****************************************************************************
    function getValRep ($item='pers_type_id', $where=null)
    // get Value/Representation list from this table
    // custom method to obtain table contents as an associative array
    {
        $array = array();

        if ($item == 'pers_type_id') {
            // get data from the database
            $this->sql_select     = 'pers_type_id, pers_type_desc';
            $this->sql_orderby    = 'pers_type_id';
            $this->sql_ordery_seq = 'asc';
            $data = $this->getData(null);

            // convert each row into 'id=desc' in the output array
            foreach ($data as $row => $rowdata) {
                $rowvalues = array_values($rowdata);
                $array[$rowvalues[0]] = $rowvalues[1];
            } // foreach

            return $array;

        } // if

        return $array;

    } // getValRep

// ****************************************************************************
} // end class
// ****************************************************************************

?>

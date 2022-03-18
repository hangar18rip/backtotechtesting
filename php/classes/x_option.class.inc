<?php
// *****************************************************************************
// Copyright 2003-2017 by A J Marston <http://www.tonymarston.net>
// *****************************************************************************
require_once 'std.table.class.inc';
class x_option extends Default_Table
{
    // ****************************************************************************
    function __construct ()
    {
        // save directory name of current script
        $this->dirname   = dirname(__file__);

        $this->dbms_engine = $GLOBALS['dbms'];
        $this->dbname      = 'sample';
        $this->tablename   = 'x_option';

        // call this method to get original field specifications
        // (note that they may be modified at runtime)
        $this->fieldspec = $this->getFieldSpec_original();

    } // __construct

    // ****************************************************************************
    function getValRep ($item='option_id', $where=null)
    // get Value/Representation list from this table
    // custom method to obtain table contents as an associative array
    {
        $array = array();

        if ($item == 'option_id') {
            // get data from the database
            $this->sql_select     = 'option_id, option_desc';
            $this->sql_orderby    = 'option_id';
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
    function _cm_changeConfig ($where, $fieldarray)
    // Change the table configuration for the duration of this instance.
    // $where = a string in SQL 'where' format.
    // $fieldarray = the contents of $where as an array.
    {
        global $mode;

        if ($mode == 'search') {
            $prev_task = getPreviousTask();
            if ($prev_task == 'pers_opt_xref_link(a).php') {
                // add an extra field to the field list
                $this->fieldspec['selected'] = array('type' => 'boolean',
                                                     'true' => 'Y',
                                                     'false' => 'N');
            } // if
        } // if

        return $fieldarray;

    } // _cm_changeConfig

// ****************************************************************************
} // end class
// ****************************************************************************

?>

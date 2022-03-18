<?php
// *****************************************************************************
// Copyright 2003-2017 by A J Marston <http://www.tonymarston.net>
// *****************************************************************************
require_once 'std.table.class.inc';
class person extends Default_Table
{
    // ****************************************************************************
    function __construct ()
    {
        // save directory name of current script
        $this->dirname   = dirname(__file__);

        $this->dbms_engine = $GLOBALS['dbms'];
        $this->dbname      = 'sample';
        $this->tablename   = 'person';

        // call this method to get original field specifications
        // (note that they may be modified at runtime)
        $this->fieldspec = $this->getFieldSpec_original();

    } // __construct

    // ****************************************************************************
    function _cm_getValRep ($item=null, $where=null)
    // get Value/Representation list from this table
    {
        $array = array();

        if ($item == 'star_sign') {
//            $array['ARI'] = 'Aries';
//            $array['AQU'] = 'Aquarius';
//            $array['CAN'] = 'Cancer';
//            $array['CAP'] = 'Capricorn';
//            $array['GEM'] = 'Gemini';
//            $array['LEO'] = 'Leo';
//            $array['LIB'] = 'Libra';
//            $array['PIS'] = 'Pisces';
//            $array['SAG'] = 'Sagittarius';
//            $array['SCO'] = 'Scorpio';
//            $array['TAU'] = 'Taurus';
//            $array['VIR'] = 'Virgo';
            $array = getLanguageArray('star_sign');
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
            if ($prev_task == 'pers_opt_xref_link(b).php') {
                // add an extra field to the field list
                $this->fieldspec['selected'] = array('type' => 'boolean',
                                                     'true' => 'Y',
                                                     'false' => 'N');
            } // if
        } // if

        return $fieldarray;

    } // _cm_changeConfig

    // ****************************************************************************
    function _cm_commonValidation ($fieldarray, $orignaldata)
    // perform validation that is common to INSERT and UPDATE.
    {
        $start_date = $fieldarray['start_date'];
        $end_date   = $fieldarray['end_date'];

        if ($start_date > $end_date) {
            // 'Start Date cannot be later than End Date'
            $this->errors['start_date'] = getLanguageText('e0001');
            // 'End Date cannot be earlier than Start Date'
            $this->errors['end_date']   = getLanguageText('e0002');
        } // if

        return $fieldarray;

    } // _cm_commonValidation

    // ****************************************************************************
    function _cm_getExtraData ($where, $fieldarray)
    // Perform custom processing for the getExtraData method.
    // $where = a string in SQL 'where' format.
    // $fieldarray = the contents of $where as an array.
    {
        if (!array_key_exists('star_sign', $this->lookup_data)) {
            // get enum list for star_sign and insert into lookup array
            $array = $this->getValRep('star_sign');
            $this->lookup_data['star_sign'] = $array;
        } // if

        if (!array_key_exists('pers_type_id', $this->lookup_data)) {
            // get contents of foreign table PERS_TYPE and add to lookup array
            require_once 'pers_type.class.inc';
            $pers_type =& singleton::getInstance('pers_type');
            $pers_type_array = $pers_type->getValRep('pers_type_id');
            $this->lookup_data['pers_type_id'] = $pers_type_array;
        } // if

        return $fieldarray;

    } // _cm_getExtraData

    // ****************************************************************************
    function _cm_popupCall (&$popupname, $where, $fieldarray, &$settings)
    // if a popup button has been pressed the contents of $where may need to
    // be altered before the popup screen is called.
    // NOTE: $settings is passed BY REFERENCE as it may be altered as well.
    // NOTE: $popupname is passed BY REFERENCE as it may be altered as well.
    {
        if ($popupname == 'tree_structure_popup.php') {
            // structure must be of type 'ORG'
            $where = "tree_type_id='ORG'";
        } // if

        return $where;

    } // _cm_popupCall

    // ****************************************************************************
    function _cm_pre_getData ($where, $where_array, $fieldarray=null)
    // perform custom processing before database record(s) are retrieved.
    // (WHERE is supplied in two formats - string and array)
    // $fieldarray may contain full details of the current record in the parent
    // class, not just its primary key.
    {
//        if (empty($this->sql_select)) {
//            // include columns from foreign table
//            $this->sql_select = 'person.*, tree_node.node_id, tree_node.node_desc';
//            $this->sql_from   = 'person '
//                               .'LEFT JOIN tree_node ON (tree_node.node_id=person.node_id)';
//        } // if

        return $where;

    } // _cm_pre_getData

// ****************************************************************************
} // end class
// ****************************************************************************

?>

<?php
// *****************************************************************************
// Copyright 2003-2006 by A J Marston <http://www.tonymarston.net>
// Distributed under the GNU General Public Licence
// *****************************************************************************

// name = std.search1.inc

// script of type search1

// This will show a blank detail screen and allow the user to specify search criteria
// that will then be returned to the previous screen for action.

require_once 'include.general.inc';

// identify mode for xsl file
$mode = 'search';
$pattern_id = 'srch';

// load session variables
initSession();

if (isset($_POST['quit']) or (isset($_POST['quit_x']))) {
    // cancel this screen, return to previous screen
    scriptPrevious(null, null, 'quit');
} // if

// define action buttons
$act_buttons['clear']  = 'clear';
$act_buttons['submit'] = 'submit';
$act_buttons['quit']   = 'cancel';

// create a class instance for the main database table
require_once "classes/$table_id.class.inc";
if (isset($script_vars['dbobject'])) {
    // use data from previous instance of this script
    $dbobject = unserialize($script_vars['dbobject']);
    // get previous data
    $fieldarray = $dbobject->getFieldArray();
    if (is_long(key($fieldarray))) {
        // indexed by row, so use row zero only
        $fieldarray = $fieldarray[0];
    } // if
} else {
    // create new instance for initial activation of this script
    $dbobject = new $table_id;
    $dbobject->initiated_from_controller = true;
    $null = null;
    $where = $dbobject->initialise($where, $null);
} // if

if (isset($_POST['clear']) or (isset($_POST['clear_x']))) {
    // clear previous search
    unset($_SESSION['search'][$dbobject->tablename]);
    // clear all editable data from current selection
    $fieldarray = $dbobject->clearEditableData($fieldarray);
    $where      = array2where($fieldarray);
    $_SERVER['REQUEST_METHOD'] = 'GET';

    // clear all data from current selection
    //$dbobject->setFieldArray($_POST);
} // if

if ($_SERVER['REQUEST_METHOD'] == 'GET'
    or isset($_POST['clear']) or (isset($_POST['clear_x']))) {
    // check if we are returning from a child form
    if (!empty($return_from)) {
        if ($return_action == 'choose' AND !empty($selection)) {
            // merge previous saved variables with selection from popup form
            $fieldarray = $dbobject->popupReturn($fieldarray, basename($return_from), $selection);
            $errors = array_merge($errors, $dbobject->getErrors());
        } // if
    } else {
        // get any data which may contain LOOKUP options
        $fieldarray = $dbobject->getExtraData($where);
        // get field specifications for current object
        $fieldspec = $dbobject->getFieldSpec();
        // insert any missing fields from $fieldspec
        foreach ($fieldspec as $fieldname => $spec) {
            if (!array_key_exists($fieldname, $fieldarray)) {
                $fieldarray[$fieldname] = null;
            } // if
        } // foreach
        // store updated array inside $dbobject
        $dbobject->setFieldArray($fieldarray);
        // save current settings
        $script_vars['where'] = $where;
    } // if
    $script_vars['dbobject'] = serialize($dbobject);
    $_SESSION[$_SERVER['PHP_SELF']] = $script_vars;
} // if

// look for entered data
if ($_SERVER['REQUEST_METHOD'] == 'POST') {
    // merge original data with user's input (so that fields which were displayed
    // but not POSTed are sent back if any errors are displayed).
    $fieldarray = array_update_associative($fieldarray, $_POST);
    // check to see if a popup form has been called
    // look for an action which is another script
    $errors = childForm($_POST, $dbobject, 'dbobject', $where, $fieldarray);

    if (!$errors) {
        if (isset($_POST['submit']) or (isset($_POST['submit_x']))) {
            // initialise search criteria
            $where = ''; // use empty string (''), not NULL
            // get current field specifications
            $fieldspec = $dbobject->getFieldSpec();
            // format POST data into SQL 'where' string
            $fieldarray = $_POST;
            require_once 'std.datevalidation.class.inc';
            $dateobj =& singleton::getInstance('date_class');
            foreach ($fieldarray as $field => $value) {
                // check that $field exists in $fieldspec array
                if (!array_key_exists($field, $fieldspec)) {
                    // it does not (like the SUBMIT button, for example), so remove it
                    unset ($fieldarray[$field]);
                } else {
                    // strip leading/trailing spaces
                    $value = trim($value);
                    // deal with non-empty fields only
                    if (strlen($value) > 0) {
                        $spec = $fieldspec[$field];

                        $operator = '=';
                        if (is_string($value) AND preg_match('/^(is not null|is null)$/i', $value, $regs )) {
                            $value = strtoupper($regs[0]);
                            $spec['type'] = 'string';
                            $operator = '';
                        } else {
                            switch ($spec['type']) {
                                case 'date':
                                    if (preg_match("/^(<>|<=|<|>=|>|!=|=)/", $value, $regs )) {
                                        $operator = $regs[0];
                                        $value = ltrim($value, $operator);
                                    } // if
                                    // if this is a complete and valid date then replace it
                                    if ($internaldate = $dateobj->getInternalDate($value)) {
                                        // value is a valid date
                                        $value = $internaldate;
                                    } else {
                                        //$errors[$field] = getLanguageText('sys0040');  // this is not a valid date
                                        $errors[$field] = $dateobj->errors;
                                    } // if
                                    break;
                                case 'time':
                                    if (preg_match("/^(<>|<=|<|>=|>|!=|=)/", $value, $regs )) {
                                        $operator = $regs[0];
                                        $value = ltrim($value, $operator);
                                    } // if
                                    // if this is a complete and valid time replace it
                                    if ($internaltime = $dateobj->getInternalTime($value)) {
                                        $value = $internaltime;
                                    } else {
                                        //$errors[$field] = getLanguageText('sys0041');  // this is not a valid TIME
                                        $errors[$field] = $dateobj->errors;
                                    } // if
                                    break;
                                case 'datetime':
                                case 'timestamp':
                                    if (preg_match("/^(<>|<=|<|>=|>|!=|=)/", $value, $regs )) {
                                        $operator = $regs[0];
                                        $value = ltrim($value, $operator);
                                    } // if
                                    // if this is a complete and valid date then replace it
                                    if ($internaldatetime = $dateobj->getInternalDateTime($value)) {
                                        // value is a valid date
                                        $value = $internaldatetime;
                                        if (!empty($_SESSION['timezone_server']) AND !empty($_SESSION['timezone_client'])) {
                                            $value = convertTZ($value, $_SESSION['timezone_client'], $_SESSION['timezone_server']);
                                        } // if
                                    } else {
                                        //$errors[$field] = getLanguageText('sys0048');  // this is not a valid date/time
                                        $errors[$field] = $dateobj->errors;
                                    } // if
                                    break;
                                case 'boolean':
                                    // result from radiogroup/checkbox may be varied, so convert to TRUE or FALSE
                                    // (where actual values are defined within $fieldspec)
                                    if (is_true($value)) {
                                        if (isset($spec['true'])) {
                                            $value = $spec['true'];
                                        } // if
                                    } else {
                                        if (isset($spec['false'])) {
                                            $value = $spec['false'];
                                        } // if
                                    } // if
                                    break;
                                case 'set':
                                case 'array':
                                case 'varray':
                                    // convert array to string with comma separator (MySQL)
                                    $value = $dbobject->array2string($value);
                                    break;
                                case 'decimal':
                                case 'numeric':
                                case 'integer':
                                case 'double':
                                case 'float':
                                case 'real':
                                    if (substr_count($value, '%') > 0) {
                                        $operator = 'LIKE';
                                    } else {
                                        if (preg_match("/^(<>|<=|<|>=|>|!=|=)/", $value, $regs )) {
                                            $operator = $regs[0];
                                            $value = ltrim($value, $operator);
                                        } // if
                                    } // if
                                    // replace foreign decimal point and thousands separator
                                    $value = number_unformat($value);
                                    if (preg_match('/(float|real)/i',$spec['type'])) {
                                        $value = sprintf('%f', $value);
                                        // remove trailing zeroes after any decimal point
                                        $value = rtrim($value,'0');
                                        // remove any trailing decimal point
                                        $value = rtrim($value, '.');
                                    } else {
                                        if (isset($fieldspec[$field]['scale'])) {
                                           $decimal_places = $fieldspec[$field]['scale'];
                                        } else {
                                           $decimal_places = 0;
                                        } // if
                                        $value = number_format((double)$value, $decimal_places, '.', '');
                                    } // if
                                    break;
                                default:  // type = 'string'
                                    if (is_string($value) AND substr_count($value, '%') > 0) {
                                        // value already contains a wildcard character
                                        $operator = 'LIKE';
                                    } else {
                                        if (isset($fieldspec[$field]['control'])) {
                                            if (isset($fieldspec[$field]['allow_input'])) {
                                                $operator = 'LIKE';
                                                if (substr_count($value, '%') == 0) {
                                                    // no wildcard character, so append one by default
                                                    $value .= '%';
                                                } // if
                                            } elseif ($fieldspec[$field]['control'] == 'multidrop' AND is_array($value)) {
                                                foreach ($value as $key => $entry) {
                                                    $value[$key] = addslashes($entry);
                                                } // foreach
                                                $value = "IN ('" .implode("','", $value) ."')";
                                                $operator = '';
                                            } else {
                                                $operator = '=';
                                            } // if
                                        } else {
                                            $operator = 'LIKE';
                                            $value .= '%';  // append wildcard character by default
                                        } // if
                                    } // if
                                    break;
                            } // switch
                        } // if

                        //$value = addslashes($value);
                        if (!empty($search)) {
                            $search .= ' AND ';
                        } // if

                        switch ($spec['type']) {
                            case 'enum':
                                // ignore value 0 as this is same as NULL
                                if ($value > 0) {
                                    // $value is index number, use exact match
                                    $search .= "$field = $value";
                                } else {
                                    $search = rtrim($search, ' AND');
                                } // if
                                break;
                            case 'boolean':
                                if (preg_match('/^(true|false)$/i', $value, $regs )) {
                                    $search .= "$field=$value";
                                } else {
                                    $search .= "$field LIKE '$value'";
                                } // if
                                break;
                            case 'numeric':
                            case 'decimal':
                            case 'integer':
                            case 'double':
                            case 'float':
                            case 'real':
                                // include specified operator (which is variable)
                                if ($operator == 'LIKE') {
                                    $search .= "$field LIKE '$value'";
                                } else {
                                    $search .= $field.$operator.$value;
                                    //$search .= $field.$operator."'$value'";
                                } // if
                                break;
                            default:
                                if (!empty($operator)) {
                                    $search .= "$field $operator '" .addslashes($value) ."'";
                                } else {
                                    $search .= "$field $value";
                                } // if
                                break;
                        } // switch

                    } // if
                } // if
            } // foreach
            // ** new **
            if (empty($search)) {
                // clear saved search criteria
                unset($_SESSION['search'][$dbobject->tablename]);
            } else {
                // save this search criteria
                $_SESSION['search'][$dbobject->tablename] = $search;
            } // if
            // ** new **
            // send search criteria back to the previous script
            $previous = $_SESSION[$_SERVER['PHP_SELF']]['previous'];
            $_SESSION[$previous]['search'] = $search;
            scriptPrevious(null, null, 'OK');
        } // if
    } // if
} // if

// build list of objects for output to XML data
$xml_objects[]['root'] = &$dbobject;

// build XML document and perform XSL transformation
buildXML($xml_objects, $errors, $messages);
exit;

?>

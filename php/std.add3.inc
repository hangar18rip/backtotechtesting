<?php
// *****************************************************************************
// Copyright 2003-2006 by A J Marston <http://www.tonymarston.net>
// Distributed under the GNU General Public Licence
// *****************************************************************************

// name = std.add3.inc
// type = add3

// This will add one or more records to the database using data in $where (supplied by
// the previous screen) plus data selected by a popup screen which will be called next.
// Note that there is no dialog with the user.

require_once 'include.general.inc';

// identify mode for xsl file
$mode = 'insert';
$pattern_id = 'add3';

// load session variables
initSession();

// create a class instance for the main database table
require_once "classes/$table_id.class.inc";
$dbobject = new $table_id;

if ($_SERVER['REQUEST_METHOD'] == 'GET') {
    if (basename($return_from) <> $popup_screen) {
        // have not been to popup screen yet, so go there now
        $script_vars = $_SESSION[$_SERVER['PHP_SELF']][$task_id];
        // may need to adjust contents of $where
        $where       = $dbobject->popupCall($popup_screen, $where, $script_vars);
        scriptNext($popup_screen, $where);
    } else {
        if (empty($selection)) {
            scriptprevious(getLanguageText('sys0083')); // 'Nothing selected from popup screen.'
        } // if
    } // if

    // We now have some data in $where (from the previous screen)
    // and some in $selection (from the popup screen).
    // First, convert from SQL 'where' format to arrays
    $array1 = where2indexedArray($where);
    $array1 = indexed2assoc($array1);

    // split $selection into one or more rows using ' OR ' separator
    $array2 = splitWhereByRow($selection);

    $dbobject->startTransaction();

    foreach ($array2 as $row) {
        // convert row data into an array
        $array3 = where2indexedArray($row);
        $array3 = indexed2assoc($array3);
        // merge into a single array
        $fieldarray = array_merge($array1, $array3);
        // strip operators from field values
        $fieldarray = stripOperators($fieldarray);
        // now add combined values to the database
        $fieldarray = $dbobject->insertRecord($fieldarray);
        if ($dbobject->errors) {
            // reduce array to primary key for error message
            $where2 = array2where($fieldarray, $dbobject->getPkeyNames(), $dbobject);
            $errors[] = getLanguageText('sys0084', $where2); // "Cannot insert where $where2"
        } // if
    } // foreach

    $errors2 = $dbobject->commit();
    $errors  = array_merge($errors, $errors2);

    // return a count of affected rows
    $messages[] = getLanguageText('sys0005', $dbobject->getNumRows(), strtoupper($dbobject->getTableName())); // 'N records were inserted'

    // last, return to previous screen
    scriptPrevious($errors, $messages);
} // if

?>

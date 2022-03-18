<?php
// *****************************************************************************
// Copyright 2003-2011 by A J Marston <http://www.tonymarston.net>
// Distributed under the GNU General Public Licence
// *****************************************************************************

// This file contains generic functions

// set configuration options
;$result = ini_set('register_globals', '0');
;$result = ini_set('magic_quotes_gpc', '0');
$result = ini_set('default_charset', 'UTF-8');
$result = ini_set('session.use_cookies', '1');
$result = ini_set('session.use_only_cookies', '0');
$result = ini_set('session.use_trans_sid', '1');
// remove 'form=' as this makes XHTML forms invalid
$result = ini_set('url_rewriter.tags', 'a=href,area=href,frame=src,input=src,fieldset=');
$result = ini_set('arg_separator.output', '&amp;');

// get session name (may not be PHPSESSID)
global $session_name;
$session_name = session_name();

$GLOBALS['transaction_has_started'] = false;
define('TRANSIX_NO_AUDIT', true);
define('DEBUGBREAK_ON_ERROR', true);
//define('LOGSTUFF', true);
$use_HTTPS = false;
$protocol = 'HTTP://';

require 'menu.inc'; // set variables normally obtained from the MENU database

require 'db.inc';
require 'error.inc';
require 'language_detection.inc';

// are we using PHP 5, or something earlier?
if (version_compare(phpversion(), '5.0.0', '<')) {
    require_once 'include.xml.php4.inc';
} else {
    // PHP 5 uses different code
    require_once 'include.xml.php5.inc';
} // if

// ****************************************************************************
function getLanguageArray ($id)
// get named array from the language file.
{
    static $array1;         // for sys.language_array.inc
    static $array2;         // for language_array.inc
    static $language;

    // if language has changed then reload contents of both arrays
    if (!empty($GLOBALS['party_language'])) {
        if ($GLOBALS['party_language'] != $language) {
            $array1 = false;
            $array2 = false;
            $language = $GLOBALS['party_language'];
        } // if
    } elseif (!empty($_SESSION['user_language'])) {
        if ($_SESSION['user_language'] != $language) {
            $array1 = false;
            $array2 = false;
            $language = $_SESSION['user_language'];
        } // if
    } elseif (!empty($_SESSION['default_language'])) {
        if ($_SESSION['default_language'] != $language) {
            $array1 = false;
            $array2 = false;
            $language = $_SESSION['default_language'];
        } // if
    } // if

    if (!empty($GLOBALS['classdir'])) {
        if (substr($GLOBALS['classdir'], -4, 4) == '.inc') {
            // remove filename to leave a directory name
            $GLOBALS['classdir'] = dirname(dirname($GLOBALS['classdir']));
        } // if
        // compare directories of current class and current script
        if ($GLOBALS['classdir'] != getcwd()) {
            // change to directory of current class to obtain error message
            chdir($GLOBALS['classdir']);
            $array2 = false;  // cause this to be reloaded
        } // if
    } // if

    if (!is_array($array1)) {
        $array1 = array();
        // find file in a language subdirectory
        $fname = getLanguageFile('sys.language_array.inc', './text');
        $array1 = require $fname;  // import contents of disk file
        if (empty($array1)) {
            //trigger_error(getLanguageText('sys0124', $fname), E_USER_ERROR);
            trigger_error("File $fname is empty", E_USER_ERROR);
        } // if
        unset($array);
    } // if

    if (!is_array($array2)) {
        $array2 = array();
        // find file in a language subdirectory
        $fname = getLanguageFile('language_array.inc', './text');
        $array2 = require $fname;  // import contents of disk file
        if (empty($array2)) {
            // 'File $fname is empty'
            trigger_error(getLanguageText('sys0124', $fname), E_USER_ERROR);
        } // if
        unset($array);
    } // if

    // perform lookup for specified $id ($array2 first, then $array1)
    if (isset($array2[$id])) {
        $result = $array2[$id];
    } elseif (isset($array1[$id])) {
        $result = $array1[$id];
    } else {
        $result = null;
    } // if
    if (empty($result)) {
        // nothing found, so return original input as an array
        $result = array($id => $id);
    } // if

    foreach ($result as $key => $value) {
        $value2 = array();
        if (is_array($value)) {
            foreach ($value as $key1 => $value1) {
                $value2[$key1] = convertEncoding($value1, 'UTF-8');
            } // foreach
        } else {
            $value2 = convertEncoding($value, 'UTF-8');
        } // if
        $result[$key] = $value2;
    } // foreach

    $cwd = getcwd();
    if (DIRECTORY_SEPARATOR == '\\') {
         $cwd = str_replace('\\', '/', $cwd);
         $_SERVER['SCRIPT_FILENAME'] = str_replace('\\', '/', $_SERVER['SCRIPT_FILENAME']);
    } // if
    if ($cwd != dirname($_SERVER['SCRIPT_FILENAME'])) {
        // change back to working directory of the current script
        chdir(dirname($_SERVER['SCRIPT_FILENAME']));
        $array2 = false;  // cause this to be reloaded
    } // if

    return $result;

} // getLanguageArray

// ****************************************************************************
function getLanguageText ($id, $arg1=null, $arg2=null, $arg3=null, $arg4=null, $arg5=null)
// get text from the language file and include up to 5 arguments.
{
    static $array1;         // for sys.language_text.inc
    static $array2;         // for language_text.inc
    static $language;

    // if language has changed then reload contents of both arrays
    if (!empty($GLOBALS['party_language'])) {
        if ($GLOBALS['party_language'] != $language) {
            $array1 = false;
            $array2 = false;
            $language = $GLOBALS['party_language'];
        } // if
    } elseif (!empty($_SESSION['user_language'])) {
        if ($_SESSION['user_language'] != $language) {
            $array1 = false;
            $array2 = false;
            $language = $_SESSION['user_language'];
        } // if
    } elseif (!empty($_SESSION['default_language'])) {
        if ($_SESSION['default_language'] != $language) {
            $array1 = false;
            $array2 = false;
            $language = $_SESSION['default_language'];
        } // if
    } // if

    if (!empty($GLOBALS['classdir'])) {
        if (substr($GLOBALS['classdir'], -4, 4) == '.inc') {
            // remove filename to leave a directory name
            $GLOBALS['classdir'] = dirname(dirname($GLOBALS['classdir']));
        } // if
        // compare directories of current class and current script
        if ($GLOBALS['classdir'] != getcwd()) {
            // change to directory of current class to obtain error message
            chdir($GLOBALS['classdir']);
            $array2 = false;  // cause this to be reloaded
        } // if
    } // if

    if (!is_array($array1)) {
        $array1 = array();
        // find file in a language subdirectory
        $dir = './text';
        if (defined('RDC_WITHIN_ERROR_HANDLER')) {
            // do not fail if this file is not found
            $fname = getLanguageFile('sys.language_text.inc', $dir, true);
        } else {
            $fname = getLanguageFile('sys.language_text.inc', $dir);
        } // if
        if ($fname) {
            $array1 = require $fname;  // import contents of disk file
            if (empty($array1)) {
                //trigger_error(getLanguageText('sys0124', $fname), E_USER_ERROR);
                trigger_error("File $fname is empty", E_USER_ERROR);
            } // if
            unset($array);
            // extract identity of language subdirectory
            $language = basename(dirname($fname));
            // use this language in the XSL transformation
            $GLOBALS['output_language'] = $language;
        } else {
            $array1 = array();
        } // if
    } // if

    if (!is_array($array2)) {
        $array2 = array();
        // find file in a language subdirectory
        if (defined('RDC_WITHIN_ERROR_HANDLER')) {
            // do not fail if this file is not found
            $fname = getLanguageFile('language_text.inc', './text', true);
        } else {
            $fname = getLanguageFile('language_text.inc', './text');
        } // if
        if ($fname) {
            $array2 = require $fname;  // import contents of disk file
            if (empty($array2)) {
                // 'File $fname is empty'
                trigger_error(getLanguageText('sys0124', $fname), E_USER_ERROR);
            } // if
            unset($array);
        } else {
            $array2 = array();
        } // if
    } // if

    // perform lookup for specified $id ($array2 first, then $array1)
    if (isset($array2[$id])) {
        $string = $array2[$id];
    } elseif (isset($array1[$id])) {
        $string = $array1[$id];
    } else {
        $string = null;
    } // if
    if (empty($string)) {
        // nothing found, so return original $id
        $string = trim($id ." $arg1 $arg2 $arg3 $arg4 $arg5");
    } // if

    $string = convertEncoding($string, 'UTF-8');

    if (!is_null($arg1)) {
        // insert argument(s) into string
        $string = sprintf($string, $arg1, $arg2, $arg3, $arg4, $arg5);
    } // if

    $cwd = getcwd();
    if (DIRECTORY_SEPARATOR == '\\') {
         $cwd = str_replace('\\', '/', $cwd);
         $_SERVER['SCRIPT_FILENAME'] = str_replace('\\', '/', $_SERVER['SCRIPT_FILENAME']);
    } // if
    if ($cwd != dirname($_SERVER['SCRIPT_FILENAME'])) {
        // change back to working directory of the current script
        chdir(dirname($_SERVER['SCRIPT_FILENAME']));
        $array2 = false;  // cause this to be reloaded
    } // if

    return $string;

} // getLanguageText

// ****************************************************************************
function getParentDIR ($filename=null)
// get name of parent directory.
{
    if (empty($filename)) {
        $dir = dirname(dirname($_SERVER['PHP_SELF']));
    } else {
        $dir = dirname(dirname($filename));
    } // if

    // if result is '\' or '/' (due to PHP bug) then replace with null
    if ($dir == '\\' or $dir == '/') $dir = null;

    if (empty($dir) AND dirname($_SERVER['PHP_SELF']) == '/sample') {
        $dir = '/sample';
    } // if

    return $dir;

} // getParentDIR

// ****************************************************************************
function getPatternId ($script_id=null)
// get the pattern_id of the specified script (default is current script).
{
    if (isset($_SESSION['logon_user_id'])) {
        if (preg_match('/INTERNET|BATCH/i', $_SESSION['logon_user_id'])) {
            return $_SESSION['logon_user_id'];
        } // if
    } // if

    if (empty($script_id)) {
        $script_id = getSelf();
    } // if

    if (isset($GLOBALS['mode']) AND $GLOBALS['mode'] == 'batch') {
        $pattern_id = 'batch';
    } else {
        if (isset($_SESSION[$script_id])) {
            $pattern_id = $_SESSION[$script_id]['pattern_id'];
        } else {
            $pattern_id = 'unknown';
        } // if
    } // if

    return $pattern_id;

} // getPatternId

// ****************************************************************************

require 'include.session.inc';
require 'include.library.inc';

?>

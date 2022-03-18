<?php
// *****************************************************************************
// Copyright 2003-2006 by A J Marston <http://www.tonymarston.net>
// Distributed under the GNU General Public Licence
// *****************************************************************************

// This is my universal error handler.
// It can be called using code such as:
// ..do something.. or trigger_error("message", E_USER_ERROR);

// tell system what function to use as the error handler
set_error_handler('errorHandler');

$xslt_error = null;

if (version_compare(phpversion(), '5.0.0', '<')) {
    // these do not exist in PHP 4, so define them manually
    define('E_STRICT', 2048);
    define('E_RECOVERABLE_ERROR', 4096);
    define('E_DEPRECATED', 8192);
    define('E_USER_DEPRECATED', 16384);
} else {
    // new constants were added in new versions of PHP 5
    if (version_compare(phpversion(), '5.2.0', '<')) {
        // this does not exist before 5.2, so define manually
        define('E_RECOVERABLE_ERROR', 4096);
    } // if
    if (version_compare(phpversion(), '5.3.0', '<')) {
        // these do not exist before 5.3, so define manually
        define('E_DEPRECATED', 8192);
        define('E_USER_DEPRECATED', 16384);
    } // if
} // if

// ****************************************************************************
//function errorHandler ($errno, $errstr, $errfile, $errline, $errcontext)
function errorHandler ($errno, $errstr, $errfile, $errline)
// If the error condition is E_USER_ERROR or above then abort.
{
    if (error_reporting() == 0) {
        return;  // call prepended with '@' symbol, so error reporting has been suppressed
    } // if

    if ($errno != E_STRICT) {
        if (function_exists('debugBreak')) {
            if (defined('DEBUGBREAK_ON_ERROR') AND DEBUGBREAK_ON_ERROR === true) {
                debugBreak();
            } // if
        } // if
    } // if

    $trace = debug_backtrace();
    if (isset($trace[0]['args'][4])) {
        $errcontext = $trace[0]['args'][4];
        if (!empty($errcontext['dmlobject'])) {
            $errcontext['this'] = $errcontext['dmlobject'];  // allow data to be extracted from DML object
        } // if
    } else {
        $errcontext = null;
    } // if

    static $save_errstr;

    switch ($errno) {
        case E_USER_WARNING:
        case E_USER_NOTICE:
        case E_WARNING:
            if (isset($errcontext['this']) AND is_object($errcontext['this'])) {
                // context is an object, but it have a variable called $error_string?
                if (method_exists($errcontext['this'], 'getErrorString')) {
                    if (version_compare(phpversion(), '5.0.0', '<')) {
                        // save this message for later
                        $errcontext['this']->setErrorString($errstr);
                    } else {
                        // previous error message already saved, so stop here
                        $message = $errcontext['this']->getErrorString();
                        if (!empty($message)) {
                            $errstr = $message;
                            break;
                        } // if
                    } // if
                } // if
            } else {
                if (empty($save_errstr)) {
                    // save this for later
                    $save_errstr = $errstr;
                } // if
            } // if
        case E_NOTICE:
        case E_CORE_WARNING:
        case E_COMPILE_WARNING:
        case E_STRICT;
        case E_RECOVERABLE_ERROR;
        case E_DEPRECATED;
        case E_USER_DEPRECATED;
            return;
        case E_USER_ERROR:
            if (!empty($save_errstr)) {
                // previous error message already saved, so stop here
                $errstr = $save_errstr;
                $errno = null;
                break;
            } // if
        case E_ERROR:
        case E_PARSE:
        case E_CORE_ERROR:
        case E_COMPILE_ERROR:
        default:
            break;
    } // switch

    if (!isset($_SESSION)) {
        session_start();
    } // if

//    if (isset($_SESSION['logon_user_id'])) {
//        $logon_user_id = $_SESSION['logon_user_id'];
//    } // if

    if (isset($errcontext['this'])) {
        // retrieve error details from DML object
        if (method_exists($errcontext['this'], 'getQuery')) {
            $query  = $errcontext['this']->getQuery();
        } else {
            $query  = '';
        } // if
        if (method_exists($errcontext['this'], 'getErrorNo')) {
            $errno  = $errcontext['this']->getErrorNo();
        } // if
//        if (version_compare(phpversion(), '5.0.0', '<')) {
            if (method_exists($errcontext['this'], 'getErrorString')) {
                $errstr = $errcontext['this']->getErrorString();
            } // if
//        } // if
        if (method_exists($errcontext['this'], 'getErrorString2')) {
            $errstr2 = $errcontext['this']->getErrorString2();
        } else {
            $errstr2 = '';
        } // if
    } else {
        $query   = null;
        $errstr2 = null;
    } // if

    $errorstring = "<h2>" . date('Y-m-d H:i:s') . "</h2>\n";
    //$errorstring .= "<p>Fatal Error: $errstr (# $errno).</p>\n";
    $errorstring .= "<p>" .getLanguageText('sys0063', $errstr);
    if (!empty($errno)) {
    	$errorstring .= " (# $errno)";
    } // if
    $errorstring .= ".</p>\n";
    //if ($query) $errorstring .= "<p>SQL query: $query</p>\n";
    if ($query) $errorstring .= "<p>" .getLanguageText('sys0064', $query) ."</p>\n";
    //$errorstring .= "<p>Error in line $errline of file '$errfile'.</p>\n";
    $errorstring .= "<p>" .getLanguageText('sys0065', $errline, $errfile) ."</p>\n";
    if (!empty($errstr2)) {
    	$errorstring .= "<p>" .$errstr2 ."</p>\n";
    } // if
    //$errorstring .= "<p>Script: '{$_SERVER['PHP_SELF']}'.</p>\n";
    $errorstring .= "<p>" .getLanguageText('sys0066', $_SERVER['PHP_SELF']) ."</p>\n";

//    if (isset($_SESSION['logon_user_id'])) {
//        $errorstring .= "<p>User Id: {$_SESSION['logon_user_id']}</p>\n";
//    } // if

    //$errorstring .= "<p>Remote Address: {$_SERVER['REMOTE_ADDR']}</p>\n";
    $errorstring .= "<p>" .getLanguageText('sys0068', $_SERVER['REMOTE_ADDR']) ."</p>\n";
    //$errorstring .= "<p>Request URI: {$_SERVER['REQUEST_URI']}</p>\n";
    $errorstring .= "<p>" .getLanguageText('sys0069', $_SERVER['REQUEST_URI']) ."</p>\n";

    global $page_stack;
    //$history = "<p>" .'Page Stack:' ."</p>\n";
    $history = "<p>" .getLanguageText('sys0073') ."</p>\n";
    $history .= "<pre>\n";
    $ix = 0;
    if ($page_stack) {
        foreach ($page_stack as $script => $text) {
        	$history .= '  [' .$ix .'] ' .$script ."\n";
        	$ix++;
        } // foreach
    } // if
    $history .= "\n</pre>\n";

    // retrieve and format debug_backtrace for output
    if (isset($errcontext['exception'])) {
        $trace = $errcontext['exception']->getTrace();
    } else {
        $trace = debug_backtrace();
    } // if
    $result = null;
    foreach ($trace as $level => $string) {
        $result .= "$level: array =\n";
        if (is_array($string)) {
            $result = print_Trace($level, $string, $result);
        } // if
    } // foreach

    $result = "<pre>\n" .$result ."\n</pre>\n";

    if (preg_match('/^(127.0.0.1|localhost|desktop|laptop)$/i', $_SERVER['SERVER_NAME'])) {
        // my development PC does not have 'sendmail', so do nothing
    } else {
        // remove all html tags
        $search = array('<br>', '<p>', '</p>', '<h2>', '</h2>');
        $mailstring = str_replace($search, '', $errorstring);
        // Send the error to the administrator by email
        $headers = "From: {$_SERVER['HTTP_HOST']}\r\n";
        @error_log("$mailstring $result", 1, $_SERVER['SERVER_ADMIN'], $headers);
    } // if

    //echo "<h2>This application has encountered an unrecoverable error</h2>\n";
    echo "<h2>" .getLanguageText('sys0060') ."</h2>\n";
    //echo "<p>The following has been reported to the administrator:</p>\n";
    echo "<p>"  .getLanguageText('sys0061') ."</p>\n";
    echo "<b><font color='red'>\n$errorstring\n</b></font>";

    // remove line breaks
    $errorstring = str_replace("\n", "", $errorstring);
    $errorstring .= "\n"; // except the last one

    // add message to log file
    $logfile = 'errorlog.html';
    error_log("$errorstring $history $result", 3, $logfile);

    // Stop the system
    session_unset();
    session_destroy();
    die();

} // errorHandler

// *****************************************************************************
function print_Trace ($level, $string, $result, $indent=null)
// output a segment of the array produced by debug_backrace()
{
    $indent .= '  ';    // increase indent by 2 spaces
    foreach ($string as $level2 => $string2) {
        if ($level2 === 'GLOBALS') {
            // ignore
        } else {
        	if (is_array($string2)) {
                if (isset($string2['this'])) {
                    // output class name, but no class properties
                    $class = get_class($string2['this']);
                    $result .= $indent ."$level2: object = $class\n";
                } else {
                    $result .= $indent ."$level2: array =\n";
                    $result = print_Trace($level2, $string2, $result, $indent);
                } // if
        	} elseif (is_object($string2)) {
        	    // do nothing
            } else {
                if (is_null($string2)) {
                	$result .= $indent ."$level2: string = null\n";
                } else {
                    $result .= $indent ."$level2: " .gettype($string2) ." = $string2\n";
                } // if
            } // if
        } // if
    } // foreach

    return $result;

} // print_Trace

// *****************************************************************************
function XML_errorHandler ($errno, $errstr, $errfile, $errline, $errcontext)
// deal with errors from XML or XSL functions.
{
    // pass these details to the standard error handler
    errorHandler (E_USER_ERROR, $errstr, $errfile, $errline, $errcontext);

} // XML_errorHandler

// *****************************************************************************
function XSLT_errorHandler ($parser, $errorno, $level, $fields)
// error handler for Sablotron XSLT process
{
    global $xslt_error;

    $xslt_error = "Error Number $errorno, Level $level, Fields:\n";
    if (is_array($fields)) {
        foreach ($fields as $key => $value) {
            $xslt_error .= "<br> $key => $value\n";
        } // while
    } else {
        $xslt_error .= "<br>$fields";
    } // if

    return;

} // XSLT_errorHandler

// ****************************************************************************
if (version_compare(phpversion(), '5.0.0', '>=')) {
    // only valid if PHP version is 5.0.0 or higher
    // ****************************************************************************
    function exception_handler($exception)
    // catch-all for unhandled exceptions.
    {

        $string = 'Uncaught exception fron ' .get_class($exception)
                 .', message = ' .$exception->getMessage();

        trigger_error($string, E_USER_ERROR);

    } // exception_handler

    set_exception_handler('exception_handler');

} // if

// ****************************************************************************
?>

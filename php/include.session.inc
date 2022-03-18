<?php
// *****************************************************************************
// Copyright 2003-2011 by A J Marston <http://www.tonymarston.net>
// *****************************************************************************

// This file contains generic functions related to session management

global $session_name;
if (isset($_REQUEST['session_name'])) {
    // use session name passed via $_GET or $_POST
    $session_name = $_REQUEST['session_name'];
} // if

// ****************************************************************************
function childForm ($post, $dbobject, $objectname, $where=null, $fieldarray=null)
// look for an action which is another script.
// (this may be from a navigation button or a popup button)
{
    logstuff("childForm(): start", __FUNCTION__, __LINE__);

    if (isset($post['task#previous_search'])) {
        // use previous search criteria (from one of two tables)
        if (isset($_SESSION['search'][$dbobject->tablename])) {
            $GLOBALS['search'] = $_SESSION['search'][$dbobject->tablename];
        } elseif (isset($_SESSION['search'][$dbobject->sql_search_table])) {
            $GLOBALS['search'] = $_SESSION['search'][$dbobject->sql_search_table];
        } // if
        // this is a dummy button, so clear it
        unset($_POST);
        return;
    } // if

    if (isset($post['rdc_selection_lock'])) {
    	$_SESSION['selection_lock'] = $post['rdc_selection_lock'];
    } // if

    foreach ($post as $key => $value) {
        // look for a variable beginning with 'task#'
        if (preg_match('/^task#/i', $key, $regs)) {
            // strip pattern prefix
            $next_script = str_replace($regs[0], '', $key);
            // look for a variable ending in '_php' or '_php_x'
            // (note1: html will replace '.' with '_', so we must convert back)
            // (note2: if the button is replaced with an image the key name returned
            // will be appended by '_x' as part of the x/y coordinates of the image)
            $pattern = '/(_php|_php_x)$/i';
            if (preg_match($pattern, $key, $regs)) {
                // replace '_php' with '.php'
                $next_script = preg_replace($pattern, '.php', $next_script);
            } // if
            logstuff("next script: $next_script", __FUNCTION__, __LINE__);
            break;
        } // if
    } // foreach

    global $script_vars;
    global $settings;

    if (isset($next_script)) {
        // check to see if a popup/filepicker form has been called
        if (preg_match('/popup\.|filepicker\./i', $next_script, $regs)) {
            // allow $where to be modified
            $where = $dbobject->popupcall($next_script, $where, $script_vars, $fieldarray, $settings);
            // save current fieldarray inside database object
            $dbobject->setFieldArray($fieldarray);
            $script_vars[$objectname] = serialize($dbobject);
            // call popup script
            scriptNext($next_script, $where, null);
        } // if

        // this must be from a navigation button
        if (isset($post['select'])) {
            // convert selection into SQL where format
            $selection = selection2where($dbobject->getPkeyArray(), $post['select']);
            if (is_True($_SESSION['selection_lock'])) {
            	$dbobject->select_string = $selection;
            	$script_vars[$objectname] = serialize($dbobject);
            } // if
        } else {
            $selection = null;
        } // if
        // pass control to selected script
        scriptNext($next_script, $where, $selection);
    } // if

    // nothing found, so return to calling script
    return;

} // childForm

// ****************************************************************************
function chooseButton ($postarray, $dbobject)
// look to see if the 'choose' button has been selected within a popup form.
{
    // send selected entry back to the previous screen
    if (isset($postarray['select'])) {
        // convert selection into SQL where format
        $selection = selection2where($dbobject->getPkeyArray(), $postarray['select']);
        if (is_True($_SESSION['selection_lock'])) {
            // save this selection for next activation
        	$dbobject->select_string = $selection;
        	// serialise object contents for saving in session array
        	$GLOBALS['script_vars'][$objectname] = serialize($dbobject);
        	$_SESSION[$_SERVER['PHP_SELF']] = $GLOBALS['script_vars'];
        } // if
        // send selection back to the previous script
        $previous = $_SESSION[$_SERVER['PHP_SELF']]['previous'];
        $_SESSION[$previous]['selection'] = $selection;
        scriptPrevious(null, null, 'choose');
    } else {
        $messages[] = getLanguageText('sys0081'); // 'Nothing has been selected yet.'
        return $messages;
    } // if

} // choose button

// ****************************************************************************
function getNewSession ($prefix='menu')
// create a new session name using $prefix + a number.
{
    // step through numbers 0-99
    for ($i = 0; $i <= 99; $i++) {
        $session_name = $prefix .$i;
        if (!array_key_exists($session_name, $_COOKIE)) {
            break;
        } // if
    } // if

    return $session_name;

} // getNewSession

// ****************************************************************************
function getPreviousScript ()
// get the identity of the previous script.
{
    // id of previous script is in $_SESSION array
    if (isset($_SESSION[$_SERVER['PHP_SELF']]['previous'])) {
        $prev_script = $_SESSION[$_SERVER['PHP_SELF']]['previous'];
        return strtolower($prev_script);
    } // if

    return false;

} // getPreviousScript

// ****************************************************************************
function getPreviousTask ()
// get the task identity associated with the previous script.
{
    // id of previous script is in $_SESSION array
    if (isset($_SESSION[$_SERVER['PHP_SELF']]['previous'])) {
        $prev_script = $_SESSION[$_SERVER['PHP_SELF']]['previous'];
        $prev_task = basename($prev_script);
        return strtolower($prev_task);
    } // if

    return false;

} // getPreviousTask

// ****************************************************************************
function getSupportedLanguages ($dir='./text')
// obtain list of languages which are supported in this installation
{
    $array = array();

    $dirh = @opendir($dir);
    while (false !== ($file = readdir($dirh))) {
        if ($file != "." AND $file != "..") {
            if (is_dir($dir.'/'.$file)) {
                $array[] = $file;
            } // if
        } // if
    } // endwhile
    closedir($dirh);
    ksort($array);

    //$array = array('en');

    return $array;

} // getSupportedLanguages

// ****************************************************************************
function initSession()
// initialise session data
{
    global $button_text;        // button text for current task
    global $current_menu;       // currently active menu on menu bar
    global $current_task;       // currently active task on menu bar
    global $errors;             // array of error messages
    global $instruction;        // optional instruction returned by previous script
    global $keep_data;          // keep data in session after exit?
    global $lock_rows;          // lock database rows during transaction? FALSE/SH/EX
    global $lock_tables;        // lock database tables during transaction? TRUE/FALSE
    global $log_sql_query;      // Yes/No switch
    global $lookup;             // array of lookup values
    global $menu_buttons;       // array of menu buttons
    global $messages;           // optional array of messages
    global $nav_buttons_omit;   // tasks to be removed from navigation bar
    global $no_getdata;         // flag to ignore next getData() method
    global $orderby;            // field names for ORDER BY clause of SELECT
    global $orderby_seq;        // sequence ('asc' or 'desc')
    global $page_stack;         // hierarchy of pages used in this session
    global $pagination;         // pagination values
    global $popup_object;       //
    global $popup_offset;       //
    global $report;             // name of file containing report structure
    global $report_structure;   // report structure for PDF document
    global $return_action;      // set when returning to previous screen
    global $return_from;        // set when returning to previous screen
    global $search;             // selection criteria from search screen
    global $screen;             // file containing screen structure
    global $screen_structure;   // stucture of screen for XSL stylesheet
    global $screen_refresh;     // force screen to refresh every 'n' seconds
    global $script_count;       // number of times this script has been called in this cycle
    global $script_start;       // start time
    global $script_vars;        // variables belonging to current script
    global $scrolling;          // scrolling values
    global $search;             // extra selection criteria from search screen
    global $selection;          // a selection of rows made in one screen that is passed back to another
    global $session_name;       // session name, to allow multiple sessions from the same PC
    global $settings;           // optional array of settings
    global $sql_orderby;        // used in ORDER BY in an sql SELECT statement
    global $sql_orderby_seq;    // sequence ('asc' or 'desc')
    global $subsys_dir;         // directory in which subsystem is located
    global $task_id;            // current task identity on menu database
    global $task_orderby;       // ORDER BY defined in task parameters
    global $task_selection;     // selection criteria defined in task parameters
    global $transaction_has_started;    // Yes/No switch
    global $title;              // script title
    global $where;              // selection criteria, used in SQL query
    global $XSLT_client_side;   // on/off switch for client-side XSL transformations

//    global $stdouth;
//    if (isset($stdouth)) {
//        fwrite($stdouth, "<p>include.session.inc line " .__line__ ."</p>");
//    } // if

    $errors   = array();
    $messages = array();

    if ($_SERVER['PHP_SELF'] != $_SERVER['SCRIPT_NAME']) {
        // somebody has added '/something-else' to the URL, so remove it
    	$_SERVER['PHP_SELF'] = $_SERVER['SCRIPT_NAME'];
    } // if

    // continue with existing session, or start a new one
    if (!isset($_SESSION)) {
        if (isset($session_name)) {
            session_name($session_name); // set the session name
        } // if
        session_start(); // open/reopen session
    } // if

    logstuff("session_id: " .session_id(), __FUNCTION__, __LINE__);

    $_SESSION['logon_user_id'] = $_SERVER['REMOTE_ADDR'];

    $PHP_SELF = getSelf();

    if (basename($PHP_SELF) != 'help.php') {
        // record the time at which this script started
        // (end time is determined in function XSLTransform)
        if (!isset($_SESSION['script_start'])) {
            list($usec, $sec) = explode(' ', microtime());
            $_SESSION['script_start'] = (float) $sec + (float) $usec;
        } // if
    } // if

	// look for session variables associated with this script
    if (isset($_SESSION[$_SERVER['PHP_SELF']])) {
        $script_vars = $_SESSION[$_SERVER['PHP_SELF']];
    } else {
        $script_vars = array();
    } // if

    $task_id = basename($_SERVER['PHP_SELF']);
    $script_id = $_SERVER['PHP_SELF'];

    if (!isset($GLOBALS['pattern_id'])) {
        $GLOBALS['pattern_id'] = '*unknown*';
    } // if
    $_SESSION[$script_id]['pattern_id'] = $GLOBALS['pattern_id'];

    if (!isset($GLOBALS['log_sql_query'])) {
        // default settng is OFF
        $GLOBALS['log_sql_query'] = false;
    } // if
    if (isset($_SESSION['log_sql_query'])) {
        // override global setting with that from session data screen
        $GLOBALS['log_sql_query'] = $_SESSION['log_sql_query'];
    } else {
        // save global setting in session array
        $_SESSION['log_sql_query'] = $GLOBALS['log_sql_query'];
    } // if
    if (isset($script_vars['log_sql_query'])) {
        if (is_True($script_vars['log_sql_query'])) {
            // turn this ON for current script
            $GLOBALS['log_sql_query'] = true;
        } // if
    } // if

    // write start details to query log file, if option is turned on
    logSqlQuery (null, null, "\r\n***** " .$PHP_SELF .' ' .date('Y-m-d H:i:s'));

    if (version_compare(phpversion(), '5.2.0', '>=')) {
        $_SESSION['timezone_server'] = date_default_timezone_get();
    	if (!empty($GLOBALS['server_timezone'])) {
    	    // override with value from config.inc file
    		$_SESSION['timezone_server'] = $GLOBALS['server_timezone'];
    	} // if
    	if (empty($_SESSION['timezone_client'])) {
    		if (!empty($_COOKIE['timezone_client'])) {
        	    // this was created when the user last logged on
        		$_SESSION['timezone_client'] = $_COOKIE['timezone_client'];
        	} // if
    	} // if
    } // if

    unset($_SESSION['global_access']); // ensure that data is re-fetched for each page

    // find out if client-side XSL transformations are turned ON or OFF
    if (isset($GLOBALS['XSLT_client_side'])) {
        // this is a permanent setting in the CONFIG.INC file
    	if (is_True($GLOBALS['XSLT_client_side'])) {
        	$_SESSION['XSLT_client_side'] = TRUE;
    	} else {
    	    $_SESSION['XSLT_client_side'] = FALSE;
        } // if
    } // if
    // look for alternate settings
	if (isset($_COOKIE['XSLT_client_side'])) {
        $_SESSION['XSLT_client_side'] = $_COOKIE['XSLT_client_side'];
    } // if
    if (isset($_GET['csxslt'])) {
        // use this setting, and save it in a cookie for the following pages
        if (is_True($_GET['csxslt'])) {
        	$_SESSION['XSLT_client_side'] = TRUE;
        	setcookie("XSLT_client_side", 'on', time()+7776000, '/');
        } else {
            $_SESSION['XSLT_client_side'] = FALSE;
            setcookie("XSLT_client_side", 'off', time()+7776000, '/');
        } // if
    } // if

    if (isset($_COOKIE['theme'])) {
        $_SESSION['css_file'] = $_COOKIE['theme'];
    } // if

    if (!array_key_exists('css_file', $_SESSION)) {
        // not yet defined, so set to default
    	$_SESSION['css_file'] = 'default.css';
    } // if

    $_SESSION['default_language'] = 'en';

    if (empty($_SESSION['user_language_array'])) {
    	// obtain language code from browser settings
        $_SESSION['user_language_array'] = get_languages($_SERVER["HTTP_ACCEPT_LANGUAGE"]);
    } // if

    if (empty($_SESSION['supported_languages'])) {
    	// obtain supported languages from MENU database
        $_SESSION['supported_languages'] = getSupportedLanguages();
    } // if

    if (empty($_SESSION['user_language']) AND !empty($_SESSION['supported_languages'])) {
    	$found_lang = matchBrowserLanguage($_SESSION['user_language_array'], $_SESSION['supported_languages']);
    	if (!empty($found_lang)) {
    		$_SESSION['user_language'] = $found_lang;
    	} // if
    } // if
    if (empty($_SESSION['user_language'])) {
    	$_SESSION['user_language'] = $_SESSION['default_language'];
    } // if

    if (empty($_SESSION['user_language'])) {
        $_SESSION['user_language'] = 'en';
    } // if

    $_SESSION['locale_name'] = saveLocaleFormat('en-gb');
    $_SESSION['localeconv'] = $GLOBALS['localeconv'];

    // set to locale where decimal point is '.' (as used internally)
    $locale = rdc_setLocale("English (United Kingdom) [en_GB]");

    // set default language for database access
    $GLOBALS['party_language'] = strtolower($_SESSION['user_language']);

    if (!empty($_SESSION['localeconv'])) {
    	// set default number formatting based on user's locale
        $GLOBALS['localeconv'] = $_SESSION['localeconv'];
    } // if

    //$use_https = false;
    //$_SERVER['HTTPS'] = 'off';

    if (isset($script_vars['max_execution_time'])) {
    	$result = ini_set('max_execution_time', $script_vars['max_execution_time']);
    } // if

    if (!isset($_SESSION['log_xml_document'])) {
        // ensure there is a value in the $_SESSION array
    	$_SESSION['log_xml_document'] =& $GLOBALS['log_xml_document'];
    } // if

    // keep count of how many times this script has run
    if (!isset($script_vars['script_count'])) {
        $script_vars['script_count'] = 1;
    } else {
        $script_vars['script_count']++;
    } // if

    if (isset($script_vars['page_stack'])) {
        // this is the hierarchy of visited pages
        $page_stack = $script_vars['page_stack'];
    } else {
        $page_stack = array();
    } // if

    if (isset($_GET['selection'])) {
        // a new selection has been made ....
        scriptNext($_GET['selection']);
    } // if

    // update $page_stack with current script
    $page_stack = updatePageStack($_SERVER['PHP_SELF'], $button_text);

    $script_vars['page_stack'] = $page_stack;

    if (basename($_SERVER['PHP_SELF']) != 'help.php') {
        // save values in session data
        $_SESSION[$_SERVER['PHP_SELF']][$task_id] = $script_vars;
    } // if

    if (isset($script_vars['title'])) {
        $title = $script_vars['title'];
    } // if

    if (isset($script_vars['button_text'])) {
        $button_text = $script_vars['button_text'];
    } // if

    if (empty($menu_buttons)) {
    	if (isset($script_vars['menu_buttons'])) {
            // this is the array of menu buttons at the top of each page
            $menu_buttons = $script_vars['menu_buttons'];
        } else {
            $menu_buttons = array();
         } // if
    } // if

    if (isset($script_vars['search'])) {
        $search = $script_vars['search'];
        unset($script_vars['search']);
    } else {
        $search = null;
    } // if

    // do database records need to be sorted into any particular order?
    if (isset($script_vars['orderby'])) {
        $orderby = $script_vars['orderby'];
        if (isset($script_vars['orderby_seq'])) {
            $orderby_seq = $script_vars['orderby_seq'];
        } // if
    } // if
    if (isset($script_vars['task_orderby'])) {
        $task_orderby = $script_vars['task_orderby'];
    } // if

    // check for message(s) returned by previous script
    if (isset($script_vars['messages'])) {
        $messages = array_merge($messages, (array)$script_vars['messages']);
        unset($script_vars['messages']);
    } // if

    // check for error(s) returned by previous script
    if (isset($script_vars['errors'])) {
        if (is_array($script_vars['errors'])) {
            $errors = $script_vars['errors'];
        } else {
            // convert simple string into an array
            $errors[] = $script_vars['errors'];
        } // if
        unset($script_vars['errors']);
    } else {
        if (!isset($errors)) {
            $errors = array();
        } // if
    } // if

    // check for instruction returned by previous script
    if (isset($script_vars['instruction'])) {
        $instruction = $script_vars['instruction'];
        unset($script_vars['instruction']);
    } // if

    // check for SQL 'where' string to be used within this script
    // (this is usually passed down by the parent script)
    if (isset($script_vars['where'])) {
        $where = $script_vars['where'];
    } // if

    // although this string has been merged into $where, it may be filtered out by an
    // outer entity before being passed to an inner entity, so it is defined separately.
    if (isset($script_vars['selection_fixed'])) {
        $task_selection = $script_vars['selection_fixed'];
        unset ($script_vars['selection_fixed']);
    } // if

    // check for details concerned with a popup form.
    if (isset($script_vars['popup_object'])) {
        $popup_object = $script_vars['popup_object'];
        unset ($script_vars['popup_object']);
    } // if
    if (isset($script_vars['popup_offset'])) {
        $popup_offset = $script_vars['popup_offset'];
        unset ($script_vars['popup_offset']);
    } // if

    // check for a selection of one or more rows
    if (isset($script_vars['selection'])) {
        $selection = $script_vars['selection'];
    } else {
        $selection = null;
    } // if

    // check for identity of previous script
    if (isset($script_vars['return_from'])) {
        $return_from = $script_vars['return_from'];
        unset($script_vars['return_from']);
        if ($return_from == 'pdf') {
            // PDF document was displayed in browser window, so return is via BACK button.
            // HTTP requests that have already been processed must be removed.
        	unset($_GET['orderby']);
        } // if
    } // if

    // check action taken within previous script
    if (isset($script_vars['return_action'])) {
        $return_action = $script_vars['return_action'];
        unset($script_vars['return_action']);
    } // if

    // get current scrolling information
    if (isset($script_vars['scrolling'])) {
        $scrolling = $script_vars['scrolling'];
    } // if

    // get current pagination information
    if (isset($script_vars['pagination'])) {
        $pagination = $script_vars['pagination'];
    } // if

    // get any optional settings
    if (isset($script_vars['settings'])) {
        // this is a string of 'name=value' pairs separated by '&', so...
        // convert string into an array with all keys in lower case
        parse_str($script_vars['settings'], $settings);
        $settings = array_change_key_case($settings, CASE_LOWER);
        foreach ($settings as $key => $value) {
            // remove single quotes from each value
        	$settings[$key] = trim($value, "'");
        } // foreach
    } else {
    	$settings = array();
    } // if

    if (!empty($page_stack)) {
        $script_vars['page_stack'] = $page_stack;
        // also save data without association to a particular script
        $_SESSION['page_stack']    = $page_stack;
    } // if

    if (basename($PHP_SELF) != 'help.php') {
        // save values in session data
        $_SESSION[$PHP_SELF]['task_id'] = $task_id;
    } // if

    if (!isset($_SESSION['rowsperpage'])) {
        // set page size to default value (used in list screens)
        $_SESSION['rowsperpage'] = 10;
    } // if

    // get current pagination information
    if (isset($script_vars['screen_refresh'])) {
        $screen_refresh = $script_vars['screen_refresh'];
    } // if

    if (isset($screen)) {
    	// load screen structure from disk file
        $screen_structure = getFileStructure($screen, './screens');
    } // if

    if (isset($report)) {
        // load the structure details for this report.
    	$report_structure = getFileStructure($report, './reports');
    } // if

    logstuff("initSession: end", __FUNCTION__, __LINE__);

    return;

} // initSession

// ****************************************************************************
function reducePageStack ($script_id)
// remove this page (and any following pages) from the page stack.
// (this causes page stack to contain only those pages which are current).
{
    if (isset($GLOBALS['page_stack'])) {
        // retrieve current page stack
        $page_stack = $GLOBALS['page_stack'];
    } else {
        // create an empty page stack
        $page_stack = array();
    } // if

    if (array_key_exists($script_id, $page_stack)) {
        // script is within current stack, so remove anything which follows
        $end = end($page_stack); // get the last value
        while (key($page_stack) != $script_id) {
            // remove this script's variables from session details
            if (isset($_SESSION[key($page_stack)])) {
                unset($_SESSION[key($page_stack)]);
            } // if
            // remove page from page stack
            unset($page_stack[key($page_stack)]);
            $end = end($page_stack); // get the (new) last value
        } // while
    } // if

    return $page_stack;

} // reducePageStack

// ****************************************************************************
function removeFromScriptSequence ($task_id=null)
// remove entries from $_SESSION['script_sequence']
{
    if (empty($_SESSION['script_sequence'])) {
        return;
    } // if

    if (empty($task_id)) {
        // not supplied, so default to current task
        $task_id = $GLOBALS['task_id'];
    } // if

    foreach ($_SESSION['script_sequence'] as $index => $entry) {
        if (array_key_exists('inserted_by', $entry)) {
            if ($entry['inserted_by'] == $task_id) {
                unset($_SESSION['script_sequence'][$index]);
            } // if
        } // if
    } // foreach

    return;

} // removeFromScriptSequence

// ****************************************************************************
function scriptNext($script_id, $where=null, $selection=null)
// proceed to a new script
{
    logstuff("script_id: $script_id", __FUNCTION__, __LINE__);

    if (empty($script_id)) {
        trigger_error(getLanguageText('sys0052'), E_USER_ERROR); // 'script id is not defined'
    } // if

    global $menu_buttons;
    global $messages;
    global $protocol;       // HTTP or HTTPS
    global $query_string;
    global $page_stack;
    global $script_vars;

    // ensure that latest set of script variables is stored in $_SESSION array
    // for the current script
    if (isset($_SESSION[$_SERVER['PHP_SELF']])) {
        $_SESSION[$_SERVER['PHP_SELF']] = $script_vars;
    } // if

    if ($script_id == basename($script_id)) {
        // script name is not qualified, so insert directory name
        $script_id = dirname($_SERVER['PHP_SELF']) . '/' . $script_id;
    } // if

    // put menu buttons into session array
    if (!empty($menu_buttons)) {
        $_SESSION[$script_id]['menu_buttons'] = $menu_buttons;
    } // if

    if (!empty($page_stack)) {
        $_SESSION[$script_id]['page_stack'] = $page_stack;
    } // if

    // put any message into session array
    if (!empty($messages)) {
        $_SESSION[$script_id]['messages'] = $messages;
    } // if

    // put any profile into session array
    if (!empty($selection)) {
        $_SESSION[$script_id]['selection'] = $selection;
    } // if

    if (!empty($where)) {
        $_SESSION[$script_id]['where'] = $where;
    } // if

    // identify this script as previous to the next script
    $_SESSION[$script_id]['previous'] = $_SERVER['PHP_SELF'];

    $location = $protocol . $_SERVER['HTTP_HOST'] . $script_id;
    if (isset($query_string)) {
        $location .= "?$query_string";
    } // if

    logstuff("location: $location", __FUNCTION__, __LINE__);

    header('Location: ' . $location);
    exit;

} // scriptNext

// ****************************************************************************
function scriptPrevious($errors=null, $messages=null, $action=null, $instruction=null)
// go back to the previous script (as defined in page_stack)
{
    global $protocol;       // HTTP or HTTPS
    $script_id = $_SERVER['PHP_SELF'];

    // retrieve task_id for current script
    if (isset($_SESSION[$script_id]['task_id'])) {
        $task_id = $_SESSION[$script_id]['task_id'];
    } // if

    // retrieve identity of previous script (the one which called this one)
    if (isset($_SESSION[$script_id]['previous'])) {
        $previous = $_SESSION[$script_id]['previous'];
    } // if

    // remove this script's variables from session details
    unset($_SESSION[$script_id]);

    // remove ths script's id from the program stack
    if (isset($_SESSION['page_stack'])) {
        $page_stack = $_SESSION['page_stack'];
        unset($page_stack[$script_id]);
    } // if

    if (isset($previous)) {
        // put any messages into session array
        if (!empty($messages)) {
            $_SESSION[$previous]['messages'] = $messages;
        } // if
        // put any errors into session array
        if (!empty($errors)) {
            $_SESSION[$previous]['errors'] = $errors;
        } // if
        // show which script we are leaving, and how ('ok' or 'quit')
        if (isset($action)) {
            $_SESSION[$previous]['return_action'] = $action;
        } // if
        // pass optional instruction back to the previous script
        if (isset($instruction)) {
            $_SESSION[$previous]['instruction'] = $instruction;
        } // if
        // identify where we are coming from
        $_SESSION[$previous]['return_from'] = $script_id;

        $location = $protocol . $_SERVER['HTTP_HOST'] . $previous;
        header('Location: ' . $location);
        exit;
    } else {
        // no previous script, so go back to index page
        $location = $protocol . $_SERVER['HTTP_HOST'] . dirname($_SERVER['PHP_SELF']) . '/index.php';
        header('Location: ' . $location);
        exit;
    } // if

    return;

} // scriptPrevious

// ****************************************************************************
function updatePageStack ($script_id, $button_text)
// update prog stack with current selection.
{
    // remove redundant entries from page stack
    $page_stack = reducePageStack($script_id);

    if (empty($button_text)) {
        $button_text = 'undefined';
    } // if

    // add current selection to stack
    $page_stack[$script_id] = $button_text;

    // save data in global area
    $GLOBALS['page_stack'] = $page_stack;

    return $page_stack;

} // updatePageStack

// ****************************************************************************
?>

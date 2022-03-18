<?php
// *****************************************************************************
// Copyright 2003-2006 by A J Marston <http://www.tonymarston.net>
// Distributed under the GNU General Public Licence
// *****************************************************************************

// Display help text for the specified task.

// Each page has three parts:
// header - contents of file 'help-header.txt'
// body - from database table 'help-text' for the given task_id
// footer - contents of file 'help-footer.txt'

require_once 'include.general.inc';

if (isset($_GET['taskid'])) {
    $help_id = $_GET['taskid'];
} else {
    $help_id = 'unknown';
} // if

// identify mode for XSL file
$mode = 'read';

initSession(); // load session variables

$title = getLanguageText('sys0099', $help_id); // "Help text for '$help_id'"

if (!isset($root)) {
    // not set, so use default value
    $root = 'HTTP://' . $_SERVER['HTTP_HOST'];
} // if

if (isset($_SESSION['user_language'])) {
	$lang = $_SESSION['user_language'];
} else {
    $lang = 'en';
} // if

$errors = array();

$help_text = getHelpText("$help_id.help.txt", './help');
if (empty($help_text)) {
	$help_text = getLanguageText('sys0056', $help_id); // 'File $help cannot be found'
} // if

$search_array  = array("\n"    , "%root%", "%lang%");
$replace_array = array("<br />", $root   , $lang);

// perform replacement in $help_text
$help_text = str_replace($search_array, $replace_array, $help_text);

$search_array  = array(">\n"    , "%root%", "%lang%");
$replace_array = array("<br />", $root   , $lang);

// perform replacement in optional header and footer
$header = str_replace($search_array, $replace_array, file_get_contents('help-header.txt'));
$footer = str_replace($search_array, $replace_array, file_get_contents('help-footer.txt'));

echo "<!DOCTYPE html PUBLIC '-//W3C//DTD XHTML 1.0 Strict//EN' 'http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd'>\n";
echo "<html xmlns='http://www.w3.org/1999/xhtml' xml:lang='$lang' lang='$lang'>\n";
echo "<head>\n";
echo "  <title>$title</title>\n";
echo "  <link rel='stylesheet' type='text/css' href='help.css' />\n";
echo "  <meta http-equiv='Content-type' content='text/html; charset=UTF-8' />\n";
echo "</head>\n";
echo "<body>\n";
echo "$header\n";
echo "<div class='body'>\n";
echo "<h1>$title</h1>\n";
echo $help_text . "\n";
echo "</div>\n";
echo "$footer\n";
echo "</body>\n";
echo "</html>\n";

exit;

?>

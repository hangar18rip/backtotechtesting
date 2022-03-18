<?php
// *****************************************************************************
// Copyright 2003-2006 by A J Marston <http://www.tonymarston.net>
// Distributed under the GNU General Public Licence
// *****************************************************************************

// name = std.filepicker1.inc

// type = filepicker1

// This will list files in a directory and allow the user to choose one

require_once 'include.general.inc';

$mode = 'filepicker';
$pattern_id = 'filepicker1';

// load session variables
initSession();

if (isset($_POST['quit']) or (isset($_POST['quit_x']))) {
    // the 'quit' button has been pressed, so ...
    // clear this script from session details and return to previous page
    scriptPrevious('Nothing selected from filepicker screen.');
} // if

// define action buttons
$act_buttons['quit'] = 'cancel';

if (isset($_GET['select'])) {
    // send selection back to the previous script
    $prev_script = getPreviousScript();
    $_SESSION[$prev_script]['selection'] = $_GET['select'];
    scriptPrevious(null, null, 'choose');
} // if

$errors = array();

switch ($filetype) {
    case 'image':
        $filemask = "/(\.gif|\.jpg|\.png|\.bmp)$/i";
        break;
    default:
        $errors[] = getLanguageText('sys0059', $filetype); // "Unknown filetype ($filetype)"
} // switch

$this_dir = @opendir($subdir);
$file_list = array();
while (false !== ($file = readdir($this_dir))) {
    // only files of right type are appended to array
    if (preg_match($filemask, $file, $regs)) {
        $file_list[]['file'] = "$subdir/$file";
    } // if
} // endwhile

closedir($this_dir);
sort($file_list);

// copy data into a dummy object
require_once 'std.table.class.inc';
class FilePicker extends Default_Table {} ;
$fileobj = new FilePicker;
$fileobj->setFieldArray($file_list);

// build list of objects for output to XML data
$xml_objects[]['root'] = &$fileobj;

// build XML document and perform XSL transformation
buildXML($xml_objects, $errors, $messages);
exit;

?>

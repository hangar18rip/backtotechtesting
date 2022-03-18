<?php

if (preg_match('/^HTTPS/i', $_SERVER['SERVER_PROTOCOL'])) {
    $protocol = 'HTTPS://';
} else {
    $protocol = 'HTTP://';
} // if

$location = $protocol .$_SERVER['HTTP_HOST'] .dirname($_SERVER['PHP_SELF']) .'/person_list.php';
header('Location: ' .$location); 
exit;
?>

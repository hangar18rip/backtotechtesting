<?php
// *****************************************************************************
// Copyright 2003-2005 by A J Marston <http://www.tonymarston.net>
// Copyright 2006-2010 by Radicore Software Limited <http://www.radicore.org>
// *****************************************************************************

class singleton
// ensure that only a single instance exists for each class.
{
    static function &getInstance ($class, $arg1=null)
    // implements the 'singleton' design pattern.
    {
        static $instances = array();  // array of instance names

        if (substr_count($class, '/')) {
	        // strip leading directory names
	        $pos = strrpos($class, '/');
	    	$classname = substr($class, $pos+1);
	    	$filename  = "classes/$class.class.inc";
        } else {
            $classname = $class;
            $filename  = "classes/$class.class.inc";
	    } // if

        if (array_key_exists($class, $instances)) {
            // instance exists in array, so use it
            $instance =& $instances[$class];
        } else {
            // load the class file (if not already loaded)
            if (!class_exists($classname)) {
            	switch ($classname) {
                	case 'date_class':
                		require_once 'std.datevalidation.class.inc';
                		break;

                	case 'encryption_class':
                		require_once 'std.encryption.class.inc';
                		break;

                	case 'validation_class':
                		require_once 'std.validation.class.inc';
                		break;

                	default:
                	    require_once $filename;
                		break;
                } // switch
            } // if
            // instance does not exist, so create it
            $instances[$class] = new $class($arg1);
            $instance =& $instances[$class];
        } // if

        return $instance;

    } // getInstance

} // singleton

?>

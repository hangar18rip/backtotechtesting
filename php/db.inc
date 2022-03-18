<?php
// *****************************************************************************
// Copyright 2003-2019 by A J Marston <http://www.tonymarston.net>
// Distributed under the GNU General Public Licence
// *****************************************************************************

// This file contains database access details and the standard connection function
$dbms   = "mysql";      // database engine is MySQL
//$dbms   = 'pgsql';      // database engine is PostgreSQL
//$dbms   = "oracle";     // database engine is Oracle
//$dbms   = "sqlsrv";     // database engine is Oracle

if ($dbms == "oracle") {
	$dbhost = '//localhost/xe';

} elseif ($dbms == 'sqlsrv') {
    // JOIN clauses in SQL Server require 'dbname.<schema>.tblname'
    $serverName     = 'localhost\SQLEXPRESS';
    $SQLSRV_schema = 'dbo';

} elseif ($dbms == 'pgsql') {
    // NOTE: with MYSQL there are tables withing databases, and within a single connection
    // it is possible to access tables in any database.
    // But with PostgreSQL there are tables within schemas within databases, and within
    // a single connection it is only possible to access a single database, but any number
    // of schemas within that database.
    // When using PostgreSQL you must supply a value for $PGSQL_dbname for the single database
    // connection, and what is known as 'dbname' to MySQL becomes 'schema' to PostgreSQL.
    $dbhost       = 'localhost';
    $PGSQL_dbname = 'sample';

} else {
    $dbhost = 'localhost';
} // if

// NOTE: $dbprefiix is for my web host (shared) where my databases are prefixed
// with my account name to keep them separate from other accounts.

if (preg_match('/^(127.0.0.1|localhost|desktop|laptop)$/i', $_SERVER['SERVER_NAME'])) {
    // this is for my PC
    $dbusername = 'sample';
    $dbuserpass = 'sample';
    $dbprefix   = null;
} else {
    // this is for my web host
    $dbusername = 'tonymars_sample';
    $dbuserpass = 'sample';
    $dbprefix   = 'tonymars_';
} // if

?>
//*********************************************************************************
// Copyright 2003-2006 by A J Marston <http://www.tonymarston.net/>
//
// Distributed under the GNU General Public Licence
//
//*********************************************************************************


The zip file contains the following:

- A CLASSES folder containing all the database table classes.
- A CSS folder containing all CSS files and images.
- An IMAGES folder containing all images.
- A SCREENS folder containing all screen specifications.
- An SQL folder (with MySQL and PostgreSQL subfolders) containing sql scripts which load the SAMPLE database with data.
- An XSL folder which contains all the necessary XSL templates:
-- STD.DETAIL1.XSL, STD.LIST1.XSL, STD.LIST2.XSL, STD.LINK1.XSL which are generic XSL stylesheets.
-- STD.???.XSL which contain the generic XSL templates.
 
- DB.INC contains the username and password to connect to the database.
- DML.MYSQL.CLASS.INC is the class which issues all DML/SQL statements. This version is for MySQL versions before 4.1.x.
- DML.MYSQL.CLASS.INC is the class which issues all DML/SQL statements. This version is for MySQL version 4.1.x and above.
- DML.PGSQL.CLASS.INC is the class which issues all DML/SQL statements. This version is for PostgreSQL version 8 and above.
- DML.ORACLE.PHP4.CLASS.INC is the class which issues all DML/SQL statements. This version is for PHP4 and Oracle version 10g and above.
- DML.ORACLE.PHP5.CLASS.INC is the class which issues all DML/SQL statements. This version is for PHP5 and Oracle version 10g and above.
- DML.SQLSRV.CLASS.INC is the class which issues all DML/SQL statements. This version is for Microsoft SQL Server version 2008 R2 and above.
- ERROR.INC contains standard code for dealing with errors.
- INCLUDE.GENERAL.INC contains my library of standard functions.
- INCLUDE.XML.PHPx.INC contains my library of standard XML/XSL functions. There are separate versions for PHP 4 and PHP 5.
- INDEX.HTML is the main index page.
- MENU.INC contains settings for the menu and navigation bars.
- STD.TABLE.CLASS.INC is my abstract database class.
- *.CLASS.INC extend the abstract class to contain the specfic code for dealing with actual tables within the application database.
- STD.DATEVALIDATION.CLASS.INC is the standard class which I use when I want to check tha the user has input a valid date.
- STD.VALIDATION.CLASS.INC is the class which performs all basic validation before rows are inserted or updated. It uses the contents of the $fieldspec array within each class to determine how to validate each field.

- A collection of component scripts:
-- PERS_TYPE_*.PHP which deal with the PERS_TYPE table.
-- PERSON_*.PHP which deal with the PERSON table.
-- OPTION_*.PHP which deal with the OPTION table.
-- PERS_OPT_XREF_LINK(A).PHP which will maintain PERS_OPT_XREF by PERSON.
-- PERS_OPT_XREF_LINK(B).PHP which will maintain PERS_OPT_XREF by OPTION.
-- HELP.PHP for online help.
-- TREE_LEVEL_*.PHP which deal with the TREE_LEVEL table.
-- TREE_TYPE_*.PHP which will deal with the TREE_TYPE table.
-- TREE_NODE_*.PHP which deal with the TREE_NODE table.

- A collection of reusable dialog type scripts:
-- STD.ADD1.INC which will add a single row.
-- STD.ADD3.INC which will add several rows.
-- STD.DELETE1.INC which will delete a single row.
-- STD.ENQUIRE1.INC which will display a single row.
-- STD.FILEPICKER.INC will display filenames from which one can be selected.
-- STD.LIST1.INC which will display multiple rows for a table.
-- STD.LIST2.INC which will display multiple rows for a table in a ONE-to-MANY relationship.
-- STD.LINK1.INC which will deal with a MANY-to-MANY relationship.
-- STD.MULTI2.INC which will allow several occurrences in a ONE-to-MANY relationship to be modified.
-- STD.SEARCH1.INC which will accept new selection criteria before re-retrieving records from the database.
-- STD.UPDATE1.INC which will update a single row.
-- STD.UPDATE2.INC which will update several rows.

- README.TXT is this document.
- DEFAULT.CSS contains the cascading style sheet info for this software.
- CUSTOM.CSS contains the cascading style sheet info for this software.
- HELP.CSS is the cascading style sheet for all help screens.

- HTACCESS.TXT contains some Apache directives. This can be renamed to .htaccess in a *nix environment, or for Windows you can insert the following lines into your httpd.conf (Apache configuration) file:

  #AccessFileName .htaccess
  AccessFileName htaccess.txt
  #
  # The following lines prevent .htaccess and .htpasswd files from being 
  # viewed by Web clients. 
  #
  #<Files ~ "^\.ht">
  <Files ~ "^htaccess\.">
      Order allow,deny
      Deny from all
  </Files>

By default all XSL transformations are performed by the server, but if you have a web browser that supports XSLT then you can switch to client-side XSL transformations by adding "csxslt=on" to the URL. This will stay on until is is turned off wih "csxslt=off".

Enjoy!

Tony Marston
http://www.tonymarston.net
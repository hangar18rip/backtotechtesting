-- phpMyAdmin SQL Dump
-- version 2.6.3-pl1
-- http://www.phpmyadmin.net
-- 
-- Host: localhost
-- Generation Time: Aug 20, 2005 at 01:55 PM
-- Server version: 4.0.23
-- PHP Version: 4.3.11
-- 
-- Database: sample
-- 

-- --------------------------------------------------------

-- 
-- Table structure for table pers_opt_xref
-- 

CREATE TABLE pers_opt_xref (
  person_id varchar(8) NOT NULL default '',
  option_id varchar(8) NOT NULL default '',
  created_date datetime NOT NULL default '2003-01-01 12:00:00',
  created_user varchar(16) default NULL,
  revised_date datetime default NULL,
  revised_user varchar(16) default NULL,
  PRIMARY KEY  (person_id,option_id)
) ;
CREATE INDEX pers_opt_xref_index ON pers_opt_xref (option_id);

-- --------------------------------------------------------

-- 
-- Table structure for table pers_type
-- 

CREATE TABLE pers_type (
  pers_type_id varchar(6) NOT NULL default '',
  pers_type_desc varchar(40) default NULL,
  created_date datetime NOT NULL default '2003-01-01 12:00:00',
  created_user varchar(16) default NULL,
  revised_date datetime default NULL,
  revised_user varchar(16) default NULL,
  PRIMARY KEY  (pers_type_id)
) ;

-- --------------------------------------------------------

-- 
-- Table structure for table person
-- 

CREATE TABLE person (
  person_id varchar(8) NOT NULL default '',
  pers_type_id varchar(6) default NULL,
  node_id smallint default NULL,
  nat_ins_no varchar(10) default NULL,
  first_name varchar(20) default NULL,
  last_name varchar(30) default NULL,
  initials varchar(6) default NULL,
  star_sign char(3) default NULL,
  email_addr varchar(50) default NULL,
  value1 smallint default NULL,
  value2 decimal(10,2) default NULL,
  start_date date NOT NULL default '2000-01-01',
  end_date date NOT NULL default '9999-12-31',
  picture varchar(40) default NULL,
  created_date datetime NOT NULL default '2003-01-01 12:00:00',
  created_user varchar(16) default NULL,
  revised_date datetime default NULL,
  revised_user varchar(16) default NULL,
  PRIMARY KEY  (person_id),
  UNIQUE (nat_ins_no)
) ;
CREATE INDEX person_index ON person (pers_type_id);

-- --------------------------------------------------------

-- 
-- Table structure for table tree_level
-- 

CREATE TABLE tree_level (
  tree_type_id varchar(8) NOT NULL default '',
  tree_level_id smallint NOT NULL default '0',
  tree_level_seq smallint NOT NULL default '0',
  tree_level_desc varchar(40) default NULL,
  created_date datetime NOT NULL default '2000-01-01 00:00:00',
  created_user varchar(16) default NULL,
  revised_date datetime default NULL,
  revised_user varchar(16) default NULL,
  PRIMARY KEY  (tree_type_id,tree_level_id)
) ;
-- --------------------------------------------------------

-- 
-- Table structure for table tree_node
-- 

CREATE TABLE tree_node (
  node_id smallint NOT NULL default '0',
  tree_type_id varchar(8) default NULL,
  tree_level_id smallint NOT NULL default '0',
  node_desc varchar(40) default NULL,
  node_id_snr smallint default NULL,
  external_code varchar(255) default NULL,
  created_date datetime NOT NULL default '2000-01-01 00:00:00',
  created_user varchar(16) default NULL,
  revised_date datetime default NULL,
  revised_user varchar(16) default NULL,
  PRIMARY KEY  (node_id)
) ;
CREATE INDEX tree_node_index1 ON tree_node (tree_type_id,tree_level_id);
CREATE INDEX tree_node_index2 ON tree_node (node_id_snr);

-- --------------------------------------------------------

-- 
-- Table structure for table tree_type
-- 

CREATE TABLE tree_type (
  tree_type_id varchar(8) NOT NULL default '',
  tree_type_desc varchar(40) default NULL,
  created_date datetime NOT NULL default '2000-01-01 00:00:00',
  created_user varchar(16) default NULL,
  revised_date datetime default NULL,
  revised_user varchar(16) default NULL,
  PRIMARY KEY  (tree_type_id)
) ;

-- --------------------------------------------------------

-- 
-- Table structure for table x_option
-- 

CREATE TABLE x_option (
  option_id varchar(8) NOT NULL default '',
  option_desc varchar(40) default NULL,
  created_date datetime NOT NULL default '2000-01-01 00:00:00',
  created_user varchar(16) default NULL,
  revised_date datetime default NULL,
  revised_user varchar(16) default NULL,
  PRIMARY KEY  (option_id)
) ;

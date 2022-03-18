CREATE USER "SAMPLE" IDENTIFIED BY "sample";
GRANT CONNECT, RESOURCE TO "SAMPLE";
GRANT CREATE DATABASE LINK TO "SAMPLE";
GRANT CREATE MATERIALIZED VIEW TO "SAMPLE";
GRANT CREATE PROCEDURE TO "SAMPLE";
GRANT CREATE PUBLIC SYNONYM TO "SAMPLE";
GRANT CREATE ROLE TO "SAMPLE";
GRANT CREATE SEQUENCE TO "SAMPLE";
GRANT CREATE SYNONYM TO "SAMPLE";
GRANT CREATE TABLE TO "SAMPLE";
GRANT CREATE TRIGGER TO "SAMPLE";
GRANT CREATE TYPE TO "SAMPLE";
GRANT CREATE VIEW TO "SAMPLE";

ALTER SESSION SET NLS_DATE_FORMAT = 'YYYY-MM-DD HH24:MI:SS';
ALTER SESSION SET NLS_TIMESTAMP_FORMAT = 'YYYY-MM-DD HH24:MI:SS';

ALTER SESSION SET CURRENT_SCHEMA = "SAMPLE";

CREATE TABLE  person (
	person_id varchar2(8) NOT NULL, 
	pers_type_id varchar2(6) NOT NULL, 
	node_id number(4), 
	nat_ins_no varchar2(10) NOT NULL, 
	first_name varchar2(20) NOT NULL, 
	last_name varchar2(30) NOT NULL, 
	initials varchar2(6), 
	star_sign varchar2(3), 
	email_addr varchar2(50), 
	value1 number(6), 
	value2 number(10,2), 
	start_date date NOT NULL, 
	end_date date NOT NULL, 
	picture varchar2(40), 
	created_date timestamp default '2000-01-01' NOT NULL, 
	created_user varchar2(16) default 'UNKNOWN' NOT NULL, 
	revised_date timestamp, 
	revised_user varchar2(16), 
	PRIMARY KEY (person_id)
);
CREATE UNIQUE INDEX person_idx1 ON person (nat_ins_no);
CREATE INDEX  person_idx2 ON  person (pers_type_id);

CREATE TABLE  pers_opt_xref (
	person_id varchar2(8) NOT NULL, 
	option_id varchar2(8) NOT NULL, 
	created_date timestamp default '2000-01-01' NOT NULL, 
	created_user varchar2(16) default 'UNKNOWN' NOT NULL, 
	revised_date timestamp, 
	revised_user varchar2(16), 
	PRIMARY KEY (person_id, option_id)
);
CREATE INDEX  pers_opt_xref_idx1 ON  pers_opt_xref (option_id);

CREATE TABLE  pers_type (
	pers_type_id varchar2(6) NOT NULL, 
	pers_type_desc varchar2(40) NOT NULL, 
	created_date timestamp default '2000-01-01' NOT NULL, 
	created_user varchar2(16) default 'UNKNOWN' NOT NULL, 
	revised_date timestamp, 
	revised_user varchar2(16), 
	PRIMARY KEY (pers_type_id)
);

CREATE TABLE  tree_level (
	tree_type_id varchar2(8) NOT NULL, 
	tree_level_id number(4) NOT NULL, 
	tree_level_seq number(4) NOT NULL, 
	tree_level_desc varchar2(40) NOT NULL, 
	created_date timestamp default '2000-01-01' NOT NULL, 
	created_user varchar2(16) default 'UNKNOWN' NOT NULL, 
	revised_date timestamp, 
	revised_user varchar2(16), 
	PRIMARY KEY (tree_type_id, tree_level_id)
);

CREATE TABLE  tree_node (
	node_id number(4) NOT NULL, 
	tree_type_id varchar2(8) NOT NULL, 
	tree_level_id number(4) NOT NULL, 
	node_desc varchar2(40), 
	node_id_snr number(4), 
	external_code varchar2(255), 
	created_date timestamp default '2000-01-01' NOT NULL, 
	created_user varchar2(16) default 'UNKNOWN' NOT NULL, 
	revised_date timestamp, 
	revised_user varchar2(16), 
	PRIMARY KEY (node_id)
);
CREATE INDEX  tree_node_idx1 ON  tree_node (tree_type_id, tree_level_id);
CREATE INDEX  tree_node_idx2 ON  tree_node (node_id_snr);

CREATE TABLE  tree_type (
	tree_type_id varchar2(8) NOT NULL, 
	tree_type_desc varchar2(40) NOT NULL, 
	created_date timestamp default '2000-01-01' NOT NULL, 
	created_user varchar2(16) default 'UNKNOWN' NOT NULL, 
	revised_date timestamp, 
	revised_user varchar2(16), 
	PRIMARY KEY (tree_type_id)
);

CREATE TABLE  x_option (
	option_id varchar2(8) NOT NULL, 
	option_desc varchar2(40) NOT NULL, 
	created_date timestamp default '2000-01-01' NOT NULL, 
	created_user varchar2(16) default 'UNKNOWN' NOT NULL, 
	revised_date timestamp, 
	revised_user varchar2(16), 
	PRIMARY KEY (option_id)
);


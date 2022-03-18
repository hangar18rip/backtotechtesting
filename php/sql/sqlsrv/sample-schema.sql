CREATE DATABASE [sample];
GO
ALTER DATABASE [sample] SET COMPATIBILITY_LEVEL = 100;
GO
IF (1 = FULLTEXTSERVICEPROPERTY('IsFullTextInstalled'))
 begin
 EXEC [sample].[sys].[sp_fulltext_database] @action = 'enable'
 end;
GO
ALTER DATABASE [sample] SET ANSI_NULL_DEFAULT OFF;
GO
ALTER DATABASE [sample] SET ANSI_NULLS OFF;
GO
ALTER DATABASE [sample] SET ANSI_PADDING OFF;
GO
ALTER DATABASE [sample] SET ANSI_WARNINGS OFF;
GO
ALTER DATABASE [sample] SET ARITHABORT OFF;
GO
ALTER DATABASE [sample] SET AUTO_CLOSE ON;
GO
ALTER DATABASE [sample] SET AUTO_CREATE_STATISTICS ON;
GO
ALTER DATABASE [sample] SET AUTO_SHRINK OFF;
GO
ALTER DATABASE [sample] SET AUTO_UPDATE_STATISTICS ON;
GO
ALTER DATABASE [sample] SET CURSOR_CLOSE_ON_COMMIT OFF;
GO
ALTER DATABASE [sample] SET CURSOR_DEFAULT GLOBAL;
GO
ALTER DATABASE [sample] SET CONCAT_NULL_YIELDS_NULL OFF;
GO
ALTER DATABASE [sample] SET NUMERIC_ROUNDABORT OFF;
GO
ALTER DATABASE [sample] SET QUOTED_IDENTIFIER OFF;
GO
ALTER DATABASE [sample] SET RECURSIVE_TRIGGERS OFF;
GO
ALTER DATABASE [sample] SET DISABLE_BROKER;
GO
ALTER DATABASE [sample] SET AUTO_UPDATE_STATISTICS_ASYNC OFF;
GO
ALTER DATABASE [sample] SET DATE_CORRELATION_OPTIMIZATION OFF;
GO
ALTER DATABASE [sample] SET TRUSTWORTHY OFF;
GO
ALTER DATABASE [sample] SET ALLOW_SNAPSHOT_ISOLATION OFF;
GO
ALTER DATABASE [sample] SET READ_COMMITTED_SNAPSHOT OFF;
GO
ALTER DATABASE [sample] SET PARAMETERIZATION SIMPLE;
GO
ALTER DATABASE [sample] SET READ_WRITE;
GO
ALTER DATABASE [sample] SET RECOVERY SIMPLE;
GO
ALTER DATABASE [sample] SET MULTI_USER;
GO
ALTER DATABASE [sample] SET PAGE_VERIFY CHECKSUM;
GO
ALTER DATABASE [sample] SET DB_CHAINING OFF;
GO
USE [sample];
GO

--
-- Table structure for table x_option
--

CREATE TABLE x_option (
  option_id nvarchar(8) NOT NULL default '',
  option_desc nvarchar(40) NOT NULL default '',
  created_date datetime NOT NULL default '2000-01-01 00:00:00',
  created_user nvarchar(16) NOT NULL default 'UNKNOWN',
  revised_date datetime default NULL,
  revised_user nvarchar(16) default NULL,
  PRIMARY KEY  (option_id)
);
go

-- --------------------------------------------------------

--
-- Table structure for table person
--

CREATE TABLE person (
  person_id nvarchar(8) NOT NULL default '',
  pers_type_id nvarchar(6) NOT NULL default '',
  node_id smallint NOT NULL default '0',
  nat_ins_no nvarchar(10) NOT NULL default '',
  first_name nvarchar(20) NOT NULL default '',
  last_name nvarchar(30) NOT NULL default '',
  initials nvarchar(6) default NULL,
  star_sign nvarchar(3) NOT NULL default '',
  email_addr nvarchar(50) default NULL,
  value1 smallint default NULL,
  value2 decimal(10,2) default NULL,
  start_date date NOT NULL default '2000-01-01',
  end_date date default '9999-12-31',
  picture nvarchar(40) default NULL,
  created_date datetime NOT NULL default '2000-01-01 00:00:00',
  created_user nvarchar(16) NOT NULL default 'UNKNOWN',
  revised_date datetime default NULL,
  revised_user nvarchar(16) default NULL,
  PRIMARY KEY  (person_id),
  UNIQUE (nat_ins_no)
);
CREATE INDEX person_pers_type_id ON person (pers_type_id);
go

-- --------------------------------------------------------

--
-- Table structure for table pers_opt_xref
--

CREATE TABLE pers_opt_xref (
  person_id nvarchar(8) NOT NULL default '',
  option_id nvarchar(8) NOT NULL default '',
  created_date datetime NOT NULL default '2000-01-01 00:00:00',
  created_user nvarchar(16) NOT NULL default 'UNKNOWN',
  revised_date datetime default NULL,
  revised_user nvarchar(16) default NULL,
  PRIMARY KEY  (person_id,option_id)
);
CREATE INDEX pers_opt_xref_option_id ON pers_opt_xref (option_id);
go

-- --------------------------------------------------------

--
-- Table structure for table pers_type
--

CREATE TABLE pers_type (
  pers_type_id nvarchar(6) NOT NULL default '',
  pers_type_desc nvarchar(40) NOT NULL default '',
  created_date datetime NOT NULL default '2000-01-01 00:00:00',
  created_user nvarchar(16) NOT NULL default 'UNKNOWN',
  revised_date datetime default NULL,
  revised_user nvarchar(16) default NULL,
  PRIMARY KEY  (pers_type_id)
);
go

-- --------------------------------------------------------

--
-- Table structure for table tree_level
--

CREATE TABLE tree_level (
  tree_type_id nvarchar(8) NOT NULL default '',
  tree_level_id tinyint NOT NULL default '0',
  tree_level_seq tinyint NOT NULL default '0',
  tree_level_desc nvarchar(40) NOT NULL default '',
  created_date datetime NOT NULL default '2000-01-01 00:00:00',
  created_user nvarchar(16) NOT NULL default 'UKNOWN',
  revised_date datetime default NULL,
  revised_user nvarchar(16) default NULL,
  PRIMARY KEY  (tree_type_id,tree_level_id)
);
go

-- --------------------------------------------------------

--
-- Table structure for table tree_node
--

CREATE TABLE tree_node (
  node_id smallint NOT NULL default '0',
  tree_type_id nvarchar(8) NOT NULL default '',
  tree_level_id tinyint NOT NULL default '0',
  node_desc nvarchar(40) NOT NULL default '',
  node_id_snr smallint default NULL,
  external_code nvarchar(255) default NULL,
  created_date datetime NOT NULL default '2000-01-01 00:00:00',
  created_user nvarchar(16) NOT NULL default 'UNKNOWN',
  revised_date datetime default NULL,
  revised_user nvarchar(16) default NULL,
  PRIMARY KEY  (node_id)
);
CREATE INDEX tree_node_tree_type_id ON tree_node (tree_type_id,tree_level_id);
CREATE INDEX tree_node_node_id_snr ON tree_node (node_id_snr);
go

-- --------------------------------------------------------

--
-- Table structure for table tree_type
--

CREATE TABLE tree_type (
  tree_type_id nvarchar(8) NOT NULL default '',
  tree_type_desc nvarchar(40) NOT NULL default '',
  created_date datetime NOT NULL default '2000-01-01 00:00:00',
  created_user nvarchar(16) NOT NULL default 'UNKNOWN',
  revised_date datetime default NULL,
  revised_user nvarchar(16) default NULL,
  PRIMARY KEY  (tree_type_id)
);
go

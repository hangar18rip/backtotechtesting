--
-- PostgreSQL database dump
--

-- Started on 2006-02-23 10:30:14 GMT Standard Time

SET client_encoding = 'utf-8';
SET check_function_bodies = false;
SET client_min_messages = warning;

--
-- TOC entry 6 (class 2615 OID 16599)
-- Name: sample; Type: SCHEMA; Schema: -; Owner: postgres
--

CREATE SCHEMA sample;


ALTER SCHEMA sample OWNER TO postgres;

SET search_path = sample, pg_catalog;

SET default_tablespace = '';

SET default_with_oids = false;

--
-- TOC entry 1193 (class 1259 OID 16600)
-- Dependencies: 1521 1522 1523 6
-- Name: pers_opt_xref; Type: TABLE; Schema: sample; Owner: postgres; Tablespace: 
--

CREATE TABLE pers_opt_xref (
    person_id character varying(8) DEFAULT ''::character varying NOT NULL,
    option_id character varying(8) DEFAULT ''::character varying NOT NULL,
    created_date timestamp without time zone DEFAULT '2003-01-01 12:00:00'::timestamp without time zone NOT NULL,
    created_user character varying(16),
    revised_date timestamp without time zone,
    revised_user character varying(16)
);


ALTER TABLE sample.pers_opt_xref OWNER TO postgres;

--
-- TOC entry 1194 (class 1259 OID 16605)
-- Dependencies: 1524 1525 6
-- Name: pers_type; Type: TABLE; Schema: sample; Owner: postgres; Tablespace: 
--

CREATE TABLE pers_type (
    pers_type_id character varying(6) DEFAULT ''::character varying NOT NULL,
    pers_type_desc character varying(40),
    created_date timestamp without time zone DEFAULT '2003-01-01 12:00:00'::timestamp without time zone NOT NULL,
    created_user character varying(16),
    revised_date timestamp without time zone,
    revised_user character varying(16)
);


ALTER TABLE sample.pers_type OWNER TO postgres;

--
-- TOC entry 1195 (class 1259 OID 16609)
-- Dependencies: 1526 1527 1528 1529 6
-- Name: person; Type: TABLE; Schema: sample; Owner: postgres; Tablespace: 
--

CREATE TABLE person (
    person_id character varying(8) DEFAULT ''::character varying NOT NULL,
    pers_type_id character varying(6),
    node_id smallint,
    nat_ins_no character varying(10),
    first_name character varying(20),
    last_name character varying(30),
    initials character varying(6),
    star_sign character(3),
    email_addr character varying(50),
    value1 smallint,
    value2 numeric(10,2),
    start_date date DEFAULT '2000-01-01'::date NOT NULL,
    end_date date DEFAULT '9999-12-31'::date NOT NULL,
    picture character varying(40),
    created_date timestamp without time zone DEFAULT '2003-01-01 12:00:00'::timestamp without time zone NOT NULL,
    created_user character varying(16),
    revised_date timestamp without time zone,
    revised_user character varying(16)
);


ALTER TABLE sample.person OWNER TO postgres;

--
-- TOC entry 1196 (class 1259 OID 16615)
-- Dependencies: 1530 1531 1532 1533 6
-- Name: tree_level; Type: TABLE; Schema: sample; Owner: postgres; Tablespace: 
--

CREATE TABLE tree_level (
    tree_type_id character varying(8) DEFAULT ''::character varying NOT NULL,
    tree_level_id smallint DEFAULT (0)::smallint NOT NULL,
    tree_level_seq smallint DEFAULT (0)::smallint NOT NULL,
    tree_level_desc character varying(40),
    created_date timestamp without time zone DEFAULT '2000-01-01 00:00:00'::timestamp without time zone NOT NULL,
    created_user character varying(16),
    revised_date timestamp without time zone,
    revised_user character varying(16)
);


ALTER TABLE sample.tree_level OWNER TO postgres;

--
-- TOC entry 1197 (class 1259 OID 16621)
-- Dependencies: 1534 1535 1536 6
-- Name: tree_node; Type: TABLE; Schema: sample; Owner: postgres; Tablespace: 
--

CREATE TABLE tree_node (
    node_id smallint DEFAULT (0)::smallint NOT NULL,
    tree_type_id character varying(8),
    tree_level_id smallint DEFAULT (0)::smallint NOT NULL,
    node_desc character varying(40),
    node_id_snr smallint,
    external_code character varying(255),
    created_date timestamp without time zone DEFAULT '2000-01-01 00:00:00'::timestamp without time zone NOT NULL,
    created_user character varying(16),
    revised_date timestamp without time zone,
    revised_user character varying(16)
);


ALTER TABLE sample.tree_node OWNER TO postgres;

--
-- TOC entry 1198 (class 1259 OID 16626)
-- Dependencies: 1537 1538 6
-- Name: tree_type; Type: TABLE; Schema: sample; Owner: postgres; Tablespace: 
--

CREATE TABLE tree_type (
    tree_type_id character varying(8) DEFAULT ''::character varying NOT NULL,
    tree_type_desc character varying(40),
    created_date timestamp without time zone DEFAULT '2000-01-01 00:00:00'::timestamp without time zone NOT NULL,
    created_user character varying(16),
    revised_date timestamp without time zone,
    revised_user character varying(16)
);


ALTER TABLE sample.tree_type OWNER TO postgres;

--
-- TOC entry 1199 (class 1259 OID 16630)
-- Dependencies: 1539 1540 6
-- Name: x_option; Type: TABLE; Schema: sample; Owner: postgres; Tablespace: 
--

CREATE TABLE x_option (
    option_id character varying(8) DEFAULT ''::character varying NOT NULL,
    option_desc character varying(40),
    created_date timestamp without time zone DEFAULT '2000-01-01 00:00:00'::timestamp without time zone NOT NULL,
    created_user character varying(16),
    revised_date timestamp without time zone,
    revised_user character varying(16)
);


ALTER TABLE sample.x_option OWNER TO postgres;

--
-- TOC entry 1543 (class 2606 OID 16635)
-- Dependencies: 1193 1193 1193
-- Name: pers_opt_xref_pkey; Type: CONSTRAINT; Schema: sample; Owner: postgres; Tablespace: 
--

ALTER TABLE ONLY pers_opt_xref
    ADD CONSTRAINT pers_opt_xref_pkey PRIMARY KEY (person_id, option_id);


--
-- TOC entry 1545 (class 2606 OID 16637)
-- Dependencies: 1194 1194
-- Name: pers_type_pkey; Type: CONSTRAINT; Schema: sample; Owner: postgres; Tablespace: 
--

ALTER TABLE ONLY pers_type
    ADD CONSTRAINT pers_type_pkey PRIMARY KEY (pers_type_id);


--
-- TOC entry 1548 (class 2606 OID 16639)
-- Dependencies: 1195 1195
-- Name: person_nat_ins_no_key; Type: CONSTRAINT; Schema: sample; Owner: postgres; Tablespace: 
--

ALTER TABLE ONLY person
    ADD CONSTRAINT person_nat_ins_no_key UNIQUE (nat_ins_no);


--
-- TOC entry 1550 (class 2606 OID 16641)
-- Dependencies: 1195 1195
-- Name: person_pkey; Type: CONSTRAINT; Schema: sample; Owner: postgres; Tablespace: 
--

ALTER TABLE ONLY person
    ADD CONSTRAINT person_pkey PRIMARY KEY (person_id);


--
-- TOC entry 1552 (class 2606 OID 16643)
-- Dependencies: 1196 1196 1196
-- Name: tree_level_pkey; Type: CONSTRAINT; Schema: sample; Owner: postgres; Tablespace: 
--

ALTER TABLE ONLY tree_level
    ADD CONSTRAINT tree_level_pkey PRIMARY KEY (tree_type_id, tree_level_id);


--
-- TOC entry 1556 (class 2606 OID 16645)
-- Dependencies: 1197 1197
-- Name: tree_node_pkey; Type: CONSTRAINT; Schema: sample; Owner: postgres; Tablespace: 
--

ALTER TABLE ONLY tree_node
    ADD CONSTRAINT tree_node_pkey PRIMARY KEY (node_id);


--
-- TOC entry 1558 (class 2606 OID 16647)
-- Dependencies: 1198 1198
-- Name: tree_type_pkey; Type: CONSTRAINT; Schema: sample; Owner: postgres; Tablespace: 
--

ALTER TABLE ONLY tree_type
    ADD CONSTRAINT tree_type_pkey PRIMARY KEY (tree_type_id);


--
-- TOC entry 1560 (class 2606 OID 16649)
-- Dependencies: 1199 1199
-- Name: x_option_pkey; Type: CONSTRAINT; Schema: sample; Owner: postgres; Tablespace: 
--

ALTER TABLE ONLY x_option
    ADD CONSTRAINT x_option_pkey PRIMARY KEY (option_id);


--
-- TOC entry 1541 (class 1259 OID 16650)
-- Dependencies: 1193
-- Name: pers_opt_xref_index; Type: INDEX; Schema: sample; Owner: postgres; Tablespace: 
--

CREATE INDEX pers_opt_xref_index ON pers_opt_xref USING btree (option_id);


--
-- TOC entry 1546 (class 1259 OID 16651)
-- Dependencies: 1195
-- Name: person_index; Type: INDEX; Schema: sample; Owner: postgres; Tablespace: 
--

CREATE INDEX person_index ON person USING btree (pers_type_id);


--
-- TOC entry 1553 (class 1259 OID 16652)
-- Dependencies: 1197 1197
-- Name: tree_node_index1; Type: INDEX; Schema: sample; Owner: postgres; Tablespace: 
--

CREATE INDEX tree_node_index1 ON tree_node USING btree (tree_type_id, tree_level_id);


--
-- TOC entry 1554 (class 1259 OID 16653)
-- Dependencies: 1197
-- Name: tree_node_index2; Type: INDEX; Schema: sample; Owner: postgres; Tablespace: 
--

CREATE INDEX tree_node_index2 ON tree_node USING btree (node_id_snr);


--
-- TOC entry 1562 (class 0 OID 0)
-- Dependencies: 6
-- Name: sample; Type: ACL; Schema: -; Owner: postgres
--

REVOKE ALL ON SCHEMA sample FROM PUBLIC;
GRANT ALL ON SCHEMA sample TO PUBLIC;
GRANT ALL ON SCHEMA sample TO tony;
GRANT USAGE ON SCHEMA sample TO PUBLIC;

REVOKE ALL ON TABLE pers_opt_xref FROM PUBLIC;
REVOKE ALL ON TABLE pers_opt_xref FROM postgres;
GRANT ALL ON TABLE pers_opt_xref TO postgres;
GRANT SELECT,INSERT,DELETE,UPDATE ON TABLE pers_opt_xref TO PUBLIC;

REVOKE ALL ON TABLE pers_type FROM PUBLIC;
REVOKE ALL ON TABLE pers_type FROM postgres;
GRANT ALL ON TABLE pers_type TO postgres;
GRANT SELECT,INSERT,DELETE,UPDATE ON TABLE pers_type TO PUBLIC;

REVOKE ALL ON TABLE person FROM PUBLIC;
REVOKE ALL ON TABLE person FROM postgres;
GRANT ALL ON TABLE person TO postgres;
GRANT SELECT,INSERT,DELETE,UPDATE ON TABLE person TO PUBLIC;

REVOKE ALL ON TABLE tree_level FROM PUBLIC;
REVOKE ALL ON TABLE tree_level FROM postgres;
GRANT ALL ON TABLE tree_level TO postgres;
GRANT SELECT,INSERT,DELETE,UPDATE ON TABLE tree_level TO PUBLIC;

REVOKE ALL ON TABLE tree_node FROM PUBLIC;
REVOKE ALL ON TABLE tree_node FROM postgres;
GRANT ALL ON TABLE tree_node TO postgres;
GRANT SELECT,INSERT,DELETE,UPDATE ON TABLE tree_node TO PUBLIC;

REVOKE ALL ON TABLE tree_type FROM PUBLIC;
REVOKE ALL ON TABLE tree_type FROM postgres;
GRANT ALL ON TABLE tree_type TO postgres;
GRANT SELECT,INSERT,DELETE,UPDATE ON TABLE tree_type TO PUBLIC;

REVOKE ALL ON TABLE x_option FROM PUBLIC;
REVOKE ALL ON TABLE x_option FROM postgres;
GRANT ALL ON TABLE x_option TO postgres;
GRANT SELECT,INSERT,DELETE,UPDATE ON TABLE x_option TO PUBLIC;

-- Completed on 2006-02-23 10:30:15 GMT Standard Time

--
-- PostgreSQL database dump complete
--


--
-- PostgreSQL database dump
--

SET statement_timeout = 0;
SET lock_timeout = 0;
SET client_encoding = 'UTF8';
SET standard_conforming_strings = on;
SET check_function_bodies = false;
SET client_min_messages = warning;

--
-- Name: plpgsql; Type: EXTENSION; Schema: -; Owner: 
--

CREATE EXTENSION IF NOT EXISTS plpgsql WITH SCHEMA pg_catalog;


--
-- Name: EXTENSION plpgsql; Type: COMMENT; Schema: -; Owner: 
--

COMMENT ON EXTENSION plpgsql IS 'PL/pgSQL procedural language';


SET search_path = public, pg_catalog;

--
-- Name: job_status; Type: TYPE; Schema: public; Owner: mateuszstarzycki
--

CREATE TYPE job_status AS ENUM (
    'new',
    'scheduled',
    'running',
    'error',
    'done'
);


ALTER TYPE job_status OWNER TO mateuszstarzycki;

--
-- Name: worker_status; Type: TYPE; Schema: public; Owner: mateuszstarzycki
--

CREATE TYPE worker_status AS ENUM (
    'busy',
    'idle',
    'error',
    'not_responding'
);


ALTER TYPE worker_status OWNER TO mateuszstarzycki;

--
-- Name: add_job(); Type: FUNCTION; Schema: public; Owner: mateuszstarzycki
--

CREATE FUNCTION add_job() RETURNS trigger
    LANGUAGE plpgsql
    AS $$
    BEGIN
        IF NEW.status = 'new' THEN
          INSERT INTO queue (job) VALUES (NEW.id);
          UPDATE jobs SET status = 'scheduled' WHERE jobs.id = NEW.id;
          RETURN NEW;
        END IF;
        RETURN NEW;
    END
$$;


ALTER FUNCTION public.add_job() OWNER TO mateuszstarzycki;

--
-- Name: add_results(); Type: FUNCTION; Schema: public; Owner: mateuszstarzycki
--

CREATE FUNCTION add_results() RETURNS trigger
    LANGUAGE plpgsql
    AS $$
BEGIN
  UPDATE jobs SET status = 'done' WHERE jobs.id = NEW.job;
  UPDATE workers SET status = 'idle' WHERE id = NEW.worker;
  DELETE FROM queue WHERE queue.job = NEW.job;
  RETURN NULL;
END
$$;


ALTER FUNCTION public.add_results() OWNER TO mateuszstarzycki;

--
-- Name: schedule(); Type: FUNCTION; Schema: public; Owner: mateuszstarzycki
--

CREATE FUNCTION schedule() RETURNS trigger
    LANGUAGE plpgsql
    AS $$
DECLARE j record;
BEGIN
  FOR j IN SELECT id FROM workers WHERE status = 'idle' LIMIT (SELECT count(*) FROM full_queue WHERE status = 'scheduled') 
    LOOP
      
      UPDATE jobs SET status = 'running' WHERE id = (SELECT job FROM queue INNER JOIN jobs ON queue.job = jobs.id WHERE jobs.status = 'scheduled' LIMIT 1);
      UPDATE workers SET status = 'busy' WHERE id = j.id;
    END LOOP;
  RETURN NULL;
  
END
$$;


ALTER FUNCTION public.schedule() OWNER TO mateuszstarzycki;

SET default_tablespace = '';

SET default_with_oids = false;

--
-- Name: jobs; Type: TABLE; Schema: public; Owner: mateuszstarzycki; Tablespace: 
--

CREATE TABLE jobs (
    id integer NOT NULL,
    description text NOT NULL,
    status job_status NOT NULL,
    param integer
);


ALTER TABLE jobs OWNER TO mateuszstarzycki;

--
-- Name: queue; Type: TABLE; Schema: public; Owner: mateuszstarzycki; Tablespace: 
--

CREATE TABLE queue (
    id integer NOT NULL,
    job integer NOT NULL
);


ALTER TABLE queue OWNER TO mateuszstarzycki;

--
-- Name: full_queue; Type: VIEW; Schema: public; Owner: mateuszstarzycki
--

CREATE VIEW full_queue AS
 SELECT queue.id AS q_id,
    jobs.id,
    jobs.description,
    jobs.status,
    jobs.param
   FROM (queue
     LEFT JOIN jobs ON ((queue.job = jobs.id)));


ALTER TABLE full_queue OWNER TO mateuszstarzycki;

--
-- Name: jobs_id_seq; Type: SEQUENCE; Schema: public; Owner: mateuszstarzycki
--

CREATE SEQUENCE jobs_id_seq
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE jobs_id_seq OWNER TO mateuszstarzycki;

--
-- Name: jobs_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: mateuszstarzycki
--

ALTER SEQUENCE jobs_id_seq OWNED BY jobs.id;


--
-- Name: queue_id_seq; Type: SEQUENCE; Schema: public; Owner: mateuszstarzycki
--

CREATE SEQUENCE queue_id_seq
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE queue_id_seq OWNER TO mateuszstarzycki;

--
-- Name: queue_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: mateuszstarzycki
--

ALTER SEQUENCE queue_id_seq OWNED BY queue.id;


--
-- Name: results; Type: TABLE; Schema: public; Owner: mateuszstarzycki; Tablespace: 
--

CREATE TABLE results (
    id integer NOT NULL,
    job integer NOT NULL,
    worker integer NOT NULL,
    result integer
);


ALTER TABLE results OWNER TO mateuszstarzycki;

--
-- Name: results_id_seq; Type: SEQUENCE; Schema: public; Owner: mateuszstarzycki
--

CREATE SEQUENCE results_id_seq
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE results_id_seq OWNER TO mateuszstarzycki;

--
-- Name: results_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: mateuszstarzycki
--

ALTER SEQUENCE results_id_seq OWNED BY results.id;


--
-- Name: workers; Type: TABLE; Schema: public; Owner: mateuszstarzycki; Tablespace: 
--

CREATE TABLE workers (
    id integer NOT NULL,
    status worker_status,
    addr inet
);


ALTER TABLE workers OWNER TO mateuszstarzycki;

--
-- Name: workers_id_seq; Type: SEQUENCE; Schema: public; Owner: mateuszstarzycki
--

CREATE SEQUENCE workers_id_seq
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE workers_id_seq OWNER TO mateuszstarzycki;

--
-- Name: workers_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: mateuszstarzycki
--

ALTER SEQUENCE workers_id_seq OWNED BY workers.id;


--
-- Name: id; Type: DEFAULT; Schema: public; Owner: mateuszstarzycki
--

ALTER TABLE ONLY jobs ALTER COLUMN id SET DEFAULT nextval('jobs_id_seq'::regclass);


--
-- Name: id; Type: DEFAULT; Schema: public; Owner: mateuszstarzycki
--

ALTER TABLE ONLY queue ALTER COLUMN id SET DEFAULT nextval('queue_id_seq'::regclass);


--
-- Name: id; Type: DEFAULT; Schema: public; Owner: mateuszstarzycki
--

ALTER TABLE ONLY results ALTER COLUMN id SET DEFAULT nextval('results_id_seq'::regclass);


--
-- Name: id; Type: DEFAULT; Schema: public; Owner: mateuszstarzycki
--

ALTER TABLE ONLY workers ALTER COLUMN id SET DEFAULT nextval('workers_id_seq'::regclass);


--
-- Data for Name: jobs; Type: TABLE DATA; Schema: public; Owner: mateuszstarzycki
--

COPY jobs (id, description, status, param) FROM stdin;
8	bad	running	11
7	sdsdfdsdsf	done	21
9	sdsdfasdff	done	31
10	sdsdfasdff	done	31
\.


--
-- Name: jobs_id_seq; Type: SEQUENCE SET; Schema: public; Owner: mateuszstarzycki
--

SELECT pg_catalog.setval('jobs_id_seq', 10, true);


--
-- Data for Name: queue; Type: TABLE DATA; Schema: public; Owner: mateuszstarzycki
--

COPY queue (id, job) FROM stdin;
13	8
\.


--
-- Name: queue_id_seq; Type: SEQUENCE SET; Schema: public; Owner: mateuszstarzycki
--

SELECT pg_catalog.setval('queue_id_seq', 15, true);


--
-- Data for Name: results; Type: TABLE DATA; Schema: public; Owner: mateuszstarzycki
--

COPY results (id, job, worker, result) FROM stdin;
1	7	1	3
2	9	1	3
3	10	1	3
\.


--
-- Name: results_id_seq; Type: SEQUENCE SET; Schema: public; Owner: mateuszstarzycki
--

SELECT pg_catalog.setval('results_id_seq', 3, true);


--
-- Data for Name: workers; Type: TABLE DATA; Schema: public; Owner: mateuszstarzycki
--

COPY workers (id, status, addr) FROM stdin;
2	busy	0.0.0.2
1	idle	0.0.0.0
\.


--
-- Name: workers_id_seq; Type: SEQUENCE SET; Schema: public; Owner: mateuszstarzycki
--

SELECT pg_catalog.setval('workers_id_seq', 2, true);


--
-- Name: jobs_pkey; Type: CONSTRAINT; Schema: public; Owner: mateuszstarzycki; Tablespace: 
--

ALTER TABLE ONLY jobs
    ADD CONSTRAINT jobs_pkey PRIMARY KEY (id);


--
-- Name: queue_pkey; Type: CONSTRAINT; Schema: public; Owner: mateuszstarzycki; Tablespace: 
--

ALTER TABLE ONLY queue
    ADD CONSTRAINT queue_pkey PRIMARY KEY (id);


--
-- Name: results_pkey; Type: CONSTRAINT; Schema: public; Owner: mateuszstarzycki; Tablespace: 
--

ALTER TABLE ONLY results
    ADD CONSTRAINT results_pkey PRIMARY KEY (id);


--
-- Name: workers_pkey; Type: CONSTRAINT; Schema: public; Owner: mateuszstarzycki; Tablespace: 
--

ALTER TABLE ONLY workers
    ADD CONSTRAINT workers_pkey PRIMARY KEY (id);


--
-- Name: job_add; Type: TRIGGER; Schema: public; Owner: mateuszstarzycki
--

CREATE TRIGGER job_add AFTER INSERT OR UPDATE ON jobs FOR EACH ROW EXECUTE PROCEDURE add_job();


--
-- Name: job_schedule; Type: TRIGGER; Schema: public; Owner: mateuszstarzycki
--

CREATE TRIGGER job_schedule AFTER INSERT OR DELETE OR UPDATE ON queue FOR EACH ROW EXECUTE PROCEDURE schedule();


--
-- Name: results_add; Type: TRIGGER; Schema: public; Owner: mateuszstarzycki
--

CREATE TRIGGER results_add AFTER INSERT ON results FOR EACH ROW EXECUTE PROCEDURE add_results();


--
-- Name: queue_job_fkey; Type: FK CONSTRAINT; Schema: public; Owner: mateuszstarzycki
--

ALTER TABLE ONLY queue
    ADD CONSTRAINT queue_job_fkey FOREIGN KEY (job) REFERENCES jobs(id);


--
-- Name: results_job_fk_fkey; Type: FK CONSTRAINT; Schema: public; Owner: mateuszstarzycki
--

ALTER TABLE ONLY results
    ADD CONSTRAINT results_job_fk_fkey FOREIGN KEY (job) REFERENCES jobs(id);


--
-- Name: results_woreker_fkey; Type: FK CONSTRAINT; Schema: public; Owner: mateuszstarzycki
--

ALTER TABLE ONLY results
    ADD CONSTRAINT results_woreker_fkey FOREIGN KEY (worker) REFERENCES workers(id);


--
-- Name: public; Type: ACL; Schema: -; Owner: mateuszstarzycki
--

REVOKE ALL ON SCHEMA public FROM PUBLIC;
REVOKE ALL ON SCHEMA public FROM mateuszstarzycki;
GRANT ALL ON SCHEMA public TO mateuszstarzycki;
GRANT ALL ON SCHEMA public TO PUBLIC;


--
-- PostgreSQL database dump complete
--


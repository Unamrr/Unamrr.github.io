324=# \d employees
Did not find any relation named "employees".
324=# -- Best used for learning purposes. Original developer also has an ER diag
ram available at https://dbseminar.r61.net/node/32--create tablesBEGIN; CREATE T
ABLE regions    ( region_id      SERIAL primary key,             region_name
VARCHAR(25)     );CREATE TABLE countries     ( country_id      CHAR(2) not null
PRIMARY KEY           , country_name    VARCHAR(40)     , region_id       INTEGE
R  REFERENCES regions(region_id)    ); CREATE TABLE locations    ( location_id
  SERIAL PRIMARY KEY    , street_address VARCHAR(40)    , postal_code    VARCHAR
(12)    , city       VARCHAR(30) NOT NULL            , state_province VARCHAR(25
)    , country_id     CHAR(2) REFERENCES countries (country_id)    ) ;CREATE TAB
LE departments    ( department_id    SERIAL PRIMARY KEY    , department_name  VA
RCHAR(30) NOT NULL            , manager_id       INTEGER    , location_id      I
NTEGER references locations (location_id)    ) ;CREATE TABLE jobs    ( job_id
      VARCHAR(10) PRIMARY KEY    , job_title      VARCHAR(35) NOT NULL    , min_
salary     NUMERIC(6)    , max_salary     NUMERIC(6)    ) ;CREATE TABLE employee
s    ( employee_id    SERIAL PRIMARY KEY    , first_name     VARCHAR(20)    , la
st_name      VARCHAR(25) NOT NULL    , email          VARCHAR(25) NOT NULL    ,
phone_number   VARCHAR(20)    , hire_date      TIMESTAMP  NOT NULL    , job_id
       VARCHAR(10) NOT NULL REFERENCES jobs(job_id)    , salary         NUMERIC(
8,2)    , commission_pct NUMERIC(2,2)    , manager_id     INTEGER REFERENCES emp
loyees(employee_id)    , department_id  INTEGER REFERENCES departments(departmen
t_id)    , CONSTRAINT     emp_salary_min                     CHECK (salary > 0)
    , CONSTRAINT     emp_email_uk                     UNIQUE (email)    ) ;ALTER
 TABLE DEPARTMENTS ADD CONSTRAINT dept_mgr_fk                 FOREIGN KEY (manag
er_id)                  REFERENCES employees (employee_id);CREATE TABLE job_hist
ory    ( employee_id   INTEGER NOT NULL REFERENCES employees(employee_id)    , s
tart_date    TIMESTAMP NOT NULL    , end_date      TIMESTAMP NOT NULL
 , job_id        VARCHAR(10) NOT NULL REFERENCES jobs(job_id)    , department_id
 INTEGER REFERENCES departments(department_id)    , CONSTRAINT    jhist_date_int
erval                    CHECK (end_date > start_date)    , PRIMARY KEY (employe
e_id, start_date)    ) ;
324=#

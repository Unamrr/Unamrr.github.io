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
324=# --populate tablesINSERT INTO regions VALUES         ( 1        , 'Europe'
        );INSERT INTO regions VALUES         ( 2        , 'Americas'         );I
NSERT INTO regions VALUES         ( 3        , 'Asia'         );INSERT INTO regi
ons VALUES         ( 4        , 'Middle East and Africa'         );INSERT INTO c
ountries VALUES         ( 'IT'        , 'Italy'        , 1         );INSERT INTO
 countries VALUES         ( 'JP'        , 'Japan'        , 3         );INSERT IN
TO countries VALUES         ( 'US'        , 'United States of America'        ,
2         );INSERT INTO countries VALUES         ( 'CA'        , 'Canada'
 , 2         );INSERT INTO countries VALUES         ( 'CN'        , 'China'
   , 3         );INSERT INTO countries VALUES         ( 'IN'        , 'India'
     , 3         );INSERT INTO countries VALUES         ( 'AU'        , 'Austral
ia'        , 3         );INSERT INTO countries VALUES         ( 'ZW'        , 'Z
imbabwe'        , 4         );INSERT INTO countries VALUES         ( 'SG'
 , 'Singapore'        , 3         );INSERT INTO countries VALUES         ( 'UK'
       , 'United Kingdom'        , 1         );INSERT INTO countries VALUES
    ( 'FR'        , 'France'        , 1         );INSERT INTO countries VALUES
       ( 'DE'        , 'Germany'        , 1         );INSERT INTO countries VALU
ES         ( 'ZM'        , 'Zambia'        , 4         );INSERT INTO countries V
ALUES         ( 'EG'        , 'Egypt'        , 4         );INSERT INTO countries
 VALUES         ( 'BR'        , 'Brazil'        , 2         );INSERT INTO countr
ies VALUES         ( 'CH'        , 'Switzerland'        , 1         );INSERT INT
O countries VALUES         ( 'NL'        , 'Netherlands'        , 1         );IN
SERT INTO countries VALUES         ( 'MX'        , 'Mexico'        , 2         )
;INSERT INTO countries VALUES         ( 'KW'        , 'Kuwait'        , 4
  );INSERT INTO countries VALUES         ( 'IL'        , 'Israel'        , 4
     );INSERT INTO countries VALUES         ( 'DK'        , 'Denmark'        , 1
         );INSERT INTO countries VALUES         ( 'HK'        , 'HongKong'
  , 3         );INSERT INTO countries VALUES         ( 'NG'        , 'Nigeria'
      , 4         );INSERT INTO countries VALUES         ( 'AR'        , 'Argent
ina'        , 2         );INSERT INTO countries VALUES         ( 'BE'        , '
Belgium'        , 1         );
324=#
324=#

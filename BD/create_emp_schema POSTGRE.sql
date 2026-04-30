
drop table IF EXISTS emp;
drop table IF EXISTS dept;
drop table IF EXISTS salgrade;
drop table IF EXISTS bonus;

CREATE TABLE dept (
    deptno    NUMERIC CONSTRAINT PK_DEPT PRIMARY KEY,
    dname    VARCHAR(14) ,
    loc        VARCHAR(13) 
) ;
CREATE TABLE emp (
    empno    NUMERIC CONSTRAINT PK_EMP PRIMARY KEY,
    ename    VARCHAR(10),
    job        VARCHAR(9),
    mgr        NUMERIC,
    hiredate    DATE,
    sal        NUMERIC(7,2),
    comm    NUMERIC(7,2),
    deptno    NUMERIC(2) CONSTRAINT FK_DEPTNO REFERENCES DEPT 
);
CREATE TABLE bonus (
    enamE    VARCHAR(10)    ,
    job        VARCHAR(9)  ,
    sal        NUMERIC,
    comm    NUMERIC 
) ;

CREATE TABLE salgrade ( 
    grade        NUMERIC,
    losal        NUMERIC,
    hisal        NUMERIC 
);
-- Insert test data - dept
INSERT INTO dept VALUES    (10,'ACCOUNTING','NEW YORK');
INSERT INTO dept VALUES (20,'RESEARCH','DALLAS');
INSERT INTO dept VALUES    (30,'SALES','CHICAGO');
INSERT INTO dept VALUES    (40,'OPERATIONS','BOSTON');
-- Insert test data - emp
INSERT INTO emp VALUES (7369,'SMITH','CLERK',7902,to_date('17-12-1980','dd-mm-yyyy'),800,NULL,20);
INSERT INTO emp VALUES (7499,'ALLEN','SALESMAN',7698,to_date('20-2-1981','dd-mm-yyyy'),1600,300,30);
INSERT INTO emp VALUES (7521,'WARD','SALESMAN',7698,to_date('22-2-1981','dd-mm-yyyy'),1250,500,30);
INSERT INTO emp VALUES (7566,'JONES','MANAGER',7839,to_date('2-4-1981','dd-mm-yyyy'),2975,NULL,20);
INSERT INTO emp VALUES (7654,'MARTIN','SALESMAN',7698,to_date('28-9-1981','dd-mm-yyyy'),1250,1400,30);
INSERT INTO emp VALUES (7698,'BLAKE','MANAGER',7839,to_date('1-5-1981','dd-mm-yyyy'),2850,NULL,30);
INSERT INTO emp VALUES (7782,'CLARK','MANAGER',7839,to_date('9-6-1981','dd-mm-yyyy'),2450,NULL,10);
INSERT INTO emp VALUES (7788,'SCOTT','ANALYST',7566,to_date('13-07-87','dd-mm-yyyy')-85,3000,NULL,20);
INSERT INTO emp VALUES (7839,'KING','PRESIDENT',NULL,to_date('17-11-1981','dd-mm-yyyy'),5000,NULL,10);
INSERT INTO emp VALUES (7844,'TURNER','SALESMAN',7698,to_date('8-9-1981','dd-mm-yyyy'),1500,0,30);
INSERT INTO emp VALUES (7876,'ADAMS','CLERK',7788,to_date('13-07-87','dd-mm-yyyy')-51,1100,NULL,20);
INSERT INTO emp VALUES (7900,'JAMES','CLERK',7698,to_date('3-12-1981','dd-mm-yyyy'),950,NULL,30);
INSERT INTO emp VALUES (7902,'FORD','ANALYST',7566,to_date('3-12-1981','dd-mm-yyyy'),3000,NULL,20);
INSERT INTO emp VALUES (7934,'MILLER','CLERK',7782,to_date('23-1-1982','dd-mm-yyyy'),1300,NULL,10);
-- Insert test data - salgrade
INSERT INTO salgrade VALUES (1,700,1200);
INSERT INTO salgrade VALUES (2,1201,1400);
INSERT INTO salgrade VALUES (3,1401,2000);
INSERT INTO salgrade VALUES (4,2001,3000);
INSERT INTO salgrade VALUES (5,3001,9999);
-- Transaction commit
COMMIT;



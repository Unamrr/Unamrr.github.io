CREATE TABLE employees (
    employee_id INTEGER PRIMARY KEY,
    first_name VARCHAR(20),
    last_name VARCHAR(25),
    salary REAL
);INSERT INTO employees VALUES (120, 'Matthew', 'Weiss', 8000);INSERT INTO employees VALUES (122, 'Payam', 'Kaufling', 7900);CREATE OR REPLACE FUNCTION a_function() RETURNS VOID AS $$
DECLARE v_salary_120 REAL;
BEGIN
    SELECT salary INTO v_salary_120 FROM employees WHERE employee_id = 120;
    UPDATE employees SET salary = (SELECT salary FROM employees WHERE employee_id = 122) WHERE employee_id = 120;
    UPDATE employees SET salary = v_salary_120 WHERE employee_id = 122;
END;
$$ LANGUAGE plpgsql;SELECT a_function();SELECT * FROM employees WHERE employee_id IN (120, 122);

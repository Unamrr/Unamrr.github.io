DO $$
DECLARE
    v_name employees.first_name%TYPE;
    v_deptname departments.department_name%TYPE;
BEGIN
    SELECT e.first_name, d.department_name INTO v_name, v_deptname
    FROM employees e
    JOIN departments d ON e.department_id = d.department_id
    WHERE e.employee_id = (SELECT manager_id FROM employees WHERE employee_id = 103);
    
    RAISE NOTICE 'Сотрудник: %', v_name;
    RAISE NOTICE 'Отдел: %', v_deptname;
END;
$$;DO $$
DECLARE
    v_min INTEGER;
    v_max INTEGER;
    v_c INTEGER;
BEGIN
    SELECT MIN(employee_id), MAX(employee_id) INTO v_min, v_max FROM employees;
    
    FOR i IN v_min + 1 .. v_max - 1 LOOP
        SELECT COUNT(*) INTO v_c FROM employees WHERE employee_id = i;
        IF v_c = 0 THEN
            RAISE NOTICE 'Пропущен ID: %', i;
        END IF;
    END LOOP;
END;
$$;DO $$
DECLARE
    v_year TEXT;
    v_c INTEGER;
BEGIN
    SELECT TO_CHAR(hire_date, 'YYYY') INTO v_year
    FROM employees
    GROUP BY TO_CHAR(hire_date, 'YYYY')
    ORDER BY COUNT(*) DESC
    LIMIT 1;
    
    RAISE NOTICE 'Год: %', v_year;
    
    FOR month IN 1..12 LOOP
        SELECT COUNT(*) INTO v_c
        FROM employees
        WHERE EXTRACT(MONTH FROM hire_date) = month
          AND EXTRACT(YEAR FROM hire_date) = v_year::INTEGER;
        
        RAISE NOTICE 'Месяц: %, сотрудников: %', month, v_c;
    END LOOP;
END;
$$;DO $$
DECLARE
    v_salary employees.salary%TYPE;
BEGIN
    SELECT salary INTO v_salary FROM employees WHERE first_name = 'Joe' LIMIT 1;
    UPDATE employees SET salary = v_salary WHERE employee_id = 130;
EXCEPTION
    WHEN NO_DATA_FOUND THEN
        UPDATE employees SET salary = (SELECT AVG(salary) FROM employees)
        WHERE employee_id = 130;
END;
$$;

SELECT employee_id, first_name, salary FROM employees WHERE employee_id = 130;DO $$
DECLARE
    rec RECORD;
    v_name employees.first_name%TYPE;
BEGIN
    FOR rec IN SELECT job_id, job_title FROM jobs LOOP
        SELECT first_name INTO v_name
        FROM employees
        WHERE hire_date = (SELECT MIN(hire_date) FROM employees WHERE job_id = rec.job_id)
          AND job_id = rec.job_id
        LIMIT 1;
        
        RAISE NOTICE '% - %', rec.job_title, v_name;
    END LOOP;
END;
$$;DO $$
DECLARE
    rec RECORD;
    cnt INTEGER := 0;
BEGIN
    FOR rec IN SELECT employee_id, first_name FROM employees ORDER BY employee_id LOOP
        cnt := cnt + 1;
        IF cnt > 4 AND cnt <= 10 THEN
            RAISE NOTICE '№%: %', cnt, rec.first_name;
        END IF;
    END LOOP;
END;
$$;DO $$
DECLARE
    rec RECORD;
    v_hike INTEGER;
BEGIN
    FOR rec IN SELECT employee_id, department_id, commission_pct FROM employees LOOP
        IF rec.department_id = 40 THEN
            v_hike := 10;
        ELSIF rec.department_id = 70 THEN
            v_hike := 15;
        ELSIF COALESCE(rec.commission_pct, 0) > 0.30 THEN
            v_hike := 5;
        ELSE
            v_hike := 10;
        END IF;
        
        UPDATE employees SET salary = salary + (salary * v_hike / 100)
        WHERE employee_id = rec.employee_id;
    END LOOP;
END;
$$;CREATE OR REPLACE FUNCTION get_dept_manager_name(deptid INTEGER)
RETURNS VARCHAR AS $$
DECLARE
    v_name employees.first_name%TYPE;
BEGIN
    SELECT e.first_name INTO v_name
    FROM employees e
    JOIN departments d ON e.employee_id = d.manager_id
    WHERE d.department_id = deptid;
    
    RETURN v_name;
END;
$$ LANGUAGE plpgsql;

SELECT get_dept_manager_name(10);CREATE OR REPLACE FUNCTION get_no_of_jobs_done(empid INTEGER)
RETURNS INTEGER AS $$
DECLARE
    v_count INTEGER;
BEGIN
    SELECT COUNT(*) INTO v_count FROM job_history WHERE employee_id = empid;
    RETURN v_count;
END;
$$ LANGUAGE plpgsql;

SELECT get_no_of_jobs_done(101);CREATE OR REPLACE PROCEDURE change_dept_manager(deptid INTEGER)
AS $$
DECLARE
    v_empid employees.employee_id%TYPE;
BEGIN
    SELECT employee_id INTO v_empid
    FROM employees
    WHERE department_id = deptid
    ORDER BY salary DESC
    LIMIT 1;
    
    UPDATE departments SET manager_id = v_empid WHERE department_id = deptid;
    RAISE NOTICE 'Новый менеджер ID: %', v_empid;
END;
$$ LANGUAGE plpgsql;

CALL change_dept_manager(10);
SELECT department_id, manager_id FROM departments WHERE department_id = 10;

324=#
324=# CREATE FUNCTION a_function () RETURNS void AS $$
324$# DECLARE
324$#     v_salary_120 real;
324$# BEGIN
324$#   Select  salary
324$#   From employees into v_salary_120 where  employee_id = 120;
324$#
324$#   Update employees set salary  = ( select salary from employees where empl
oyee_id = 122)
324$#   Where employee_id = 120;
324$#
324$#   Update employees set salary  =  v_salary_120  Where employee_id = 122;
324$#
324$# END;
324$# $$ LANGUAGE plpgsql;
CREATE FUNCTION
324=# SELECT a_function() AS output;
ОШИБКА:  отношение "employees" не существует
LINE 2:   From employees                   where  employee_id = 120
               ^
QUERY:  Select  salary
  From employees                   where  employee_id = 120
CONTEXT:  функция PL/pgSQL a_function(), строка 5, оператор SQL-оператор
324=# Select  salary From employees where employee_id = 120 or employee_id = 122
;
ОШИБКА:  отношение "employees" не существует
LINE 1: Select  salary From employees where employee_id = 120 or emp...
                            ^
324=#

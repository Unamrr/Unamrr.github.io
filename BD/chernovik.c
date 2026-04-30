2321313=# CREATE or replace FUNCTION b_function () RETURNS void AS $$
2321313$# DECLARE
2321313$#     v_exp  integer;
2321313$#     v_hike real;
2321313$# BEGIN
2321313$#     select EXTRACT(DAY FROM (NOW() - hire_date) / 365 ) into v_exp
2321313$#     from employees where employee_id = 115;
2321313$#
2321313$#     v_hike := 1.05;
2321313$#
2321313$#     case
2321313$#       when  v_exp > 10 then
2321313$#             v_hike := 1.20;
2321313$#       when  v_exp > 5  then
2321313$#             v_hike := 1.10;
2321313$#     end case;
2321313$#
2321313$#     update employees set salary = salary * v_hike
2321313$#     where employee_id = 115;
2321313$# END;
2321313$#
2321313$# $$ LANGUAGE plpgsql;
CREATE FUNCTION
2321313=#
2321313=#
2321313=#
2321313=# SELECT b_function() AS output;
ОШИБКА:  столбец "hire_date" не существует
LINE 1: select EXTRACT(DAY FROM (NOW() - hire_date) / 365 )         ...
                                         ^
QUERY:  select EXTRACT(DAY FROM (NOW() - hire_date) / 365 )                from
employees where employee_id = 115
CONTEXT:  функция PL/pgSQL b_function(), строка 6, оператор SQL-оператор
2321313=# Select  salary From employees where  employee_id = 115;
 salary
--------
(0 rows)

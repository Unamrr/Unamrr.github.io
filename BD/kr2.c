--Пухликова Диана МО21/1 вариант 1

-- ЗАДАЧА 1. создаем таблицы
CREATE TABLE Article (
    id_art NUMBER PRIMARY KEY,
    name VARCHAR2(100) NOT NULL,
    type VARCHAR2(10) NOT NULL CHECK (type IN ('кг', 'шт')),
    hire_date DATE
);

CREATE TABLE Producer (
    id_producer NUMBER PRIMARY KEY,
    fullname VARCHAR2(200) NOT NULL,
    address VARCHAR2(300) NOT NULL,
    website VARCHAR2(100)
);
CREATE TABLE Seller (
    id_seller NUMBER PRIMARY KEY,
    fullname VARCHAR2(200) NOT NULL,
    address VARCHAR2(300) NOT NULL,
    phone VARCHAR2(15) CHECK (
        phone LIKE '+%' 
        AND LENGTH(phone) BETWEEN 12 AND 15
    ),
    website VARCHAR2(100)
);
CREATE TABLE price_list (
    id_price_list NUMBER PRIMARY KEY,
    id_seller NUMBER NOT NULL,
    id_producer NUMBER NOT NULL,
    id_art NUMBER NOT NULL,
    price NUMBER(10, 2) NOT NULL,
    
    FOREIGN KEY (id_seller) REFERENCES Seller(id_seller),
    FOREIGN KEY (id_producer) REFERENCES Producer(id_producer),
    FOREIGN KEY (id_art) REFERENCES Article(id_art)
);


-- заполняем таблицы
INSERT INTO Article (id_art, name, type, hire_date) VALUES (1, 'Яблоки', 'кг', DATE '2024-01-15');
INSERT INTO Article (id_art, name, type, hire_date) VALUES (2, 'Молоко', 'шт', DATE '2024-02-20');
INSERT INTO Article (id_art, name, type, hire_date) VALUES (3, 'Хлеб', 'шт', DATE '2024-03-10');

INSERT INTO Producer (id_producer, fullname, address, website) VALUES (1, 'ООО Ферма', 'г. Москва, ул. Полевая, 1', 'www.farma.ru');
INSERT INTO Producer (id_producer, fullname, address, website) VALUES (2, 'Завод Молоко', 'г. Санкт-Петербург, пр. Молочный, 5', 'www.moloko.com');
INSERT INTO Producer (id_producer, fullname, address, website) VALUES (3, 'Пекарня №1', 'г. Казань, ул. Зерновая, 10', 'www.bake.ru');

INSERT INTO Seller (id_seller, fullname, address, phone, website) VALUES (1, 'ИП Иванов', 'г. Москва, ул. Торговая, 3', '+791612345678', 'www.ivanov.shop');
INSERT INTO Seller (id_seller, fullname, address, phone, website) VALUES (2, 'ООО Продукты', 'г. Санкт-Петербург, пр. Продовольственный, 7', '+781255566777', 'www.prod.ru');
INSERT INTO Seller (id_seller, fullname, address, phone, website) VALUES (3, 'Магазин У дома', 'г. Екатеринбург, ул. Домашняя, 15', '+734329876543', 'www.dom.shop');

INSERT INTO price_list (id_price_list, id_seller, id_producer, id_art, price) VALUES (1, 1, 1, 1, 89.50);
INSERT INTO price_list (id_price_list, id_seller, id_producer, id_art, price) VALUES (2, 2, 2, 2, 75.00);
INSERT INTO price_list (id_price_list, id_seller, id_producer, id_art, price) VALUES (3, 3, 3, 3, 45.30);
-- проверяем что заполнили 
SELECT * FROM Article;
SELECT * FROM Producer;
SELECT * FROM Seller;
SELECT * FROM price_list;
-- удаление
DELETE FROM price_list;
DELETE FROM Seller;
DELETE FROM Producer;
DELETE FROM Article;
-- проверяем что удалили
SELECT COUNT(*) as Article_rows FROM Article;
SELECT COUNT(*) as Producer_rows FROM Producer;
SELECT COUNT(*) as Seller_rows FROM Seller;
SELECT COUNT(*) as price_list_rows FROM price_list;


-- 2 ЗАДАЧА 1)
SELECT city, street_address, postal_code
FROM locations
WHERE country_id = 'US'
ORDER BY city;

-- 2)
SELECT 
    e.employee_id,
    e.first_name,
    e.last_name,
    e.hire_date,
    d.department_name
FROM employees e
JOIN departments d ON e.department_id = d.department_id
JOIN locations l ON d.location_id = l.location_id
JOIN countries c ON l.country_id = c.country_id
WHERE c.country_name = 'Canada';

-- 3)
SELECT 
    j.job_title,
    ROUND(AVG(e.salary), 2) as avg_salary,
    COUNT(e.employee_id) as employee_count
FROM employees e
JOIN jobs j ON e.job_id = j.job_id
GROUP BY j.job_title
HAVING COUNT(e.employee_id) > 1
ORDER BY avg_salary DESC;

--4)
SELECT e.*
FROM employees e
WHERE e.employee_id IN (
    SELECT manager_id
    FROM employees
    GROUP BY manager_id
    HAVING COUNT(*) > 5
);


-- ЗАДАЧА 3 
-- создаем таблицы
CREATE TABLE Stock (
    product_id NUMBER,   
    warehouse_id NUMBER, 
    quantity NUMBER,        
    PRIMARY KEY (product_id, warehouse_id)
);
CREATE TABLE Operations (
    operation_id NUMBER PRIMARY KEY,
    product_id NUMBER,     
    warehouse_id NUMBER,  
    operation_type NUMBER,  
    quantity NUMBER,        
    operation_date DATE DEFAULT SYSDATE
);
-- создаем триггер
CREATE OR REPLACE TRIGGER update_stock_trigger
AFTER 
INSERT OR UPDATE OF quantity, operation_type 
ON Operations
FOR EACH ROW
WHEN (NEW.operation_type IN (1, 2))  
DECLARE
    v_current_quantity NUMBER;
    v_error_message VARCHAR2(200);
BEGIN
    -- Получаем текущий остаток
    BEGIN
        SELECT quantity INTO v_current_quantity
        FROM Stock
        WHERE product_id = :NEW.product_id
          AND warehouse_id = :NEW.warehouse_id;
    EXCEPTION
        WHEN NO_DATA_FOUND THEN
            v_current_quantity := 0;
    END;
    
   
    IF :NEW.operation_type = 1 THEN
        IF v_current_quantity = 0 THEN
            
            INSERT INTO Stock (product_id, warehouse_id, quantity)
            VALUES (:NEW.product_id, :NEW.warehouse_id, :NEW.quantity);
        ELSE
            
            UPDATE Stock
            SET quantity = quantity + :NEW.quantity
            WHERE product_id = :NEW.product_id
              AND warehouse_id = :NEW.warehouse_id;
        END IF;
        
    
    ELSIF :NEW.operation_type = 2 THEN
        IF v_current_quantity >= :NEW.quantity THEN
          
            UPDATE Stock
            SET quantity = quantity - :NEW.quantity
            WHERE product_id = :NEW.product_id
              AND warehouse_id = :NEW.warehouse_id;
        ELSE
            
            v_error_message := 'Недостаточно товара на складе. Доступно: ' 
                               || v_current_quantity 
                               || ', требуется: ' || :NEW.quantity;
            RAISE_APPLICATION_ERROR(-20001, v_error_message);
        END IF;
    END IF;
    
EXCEPTION
    WHEN OTHERS THEN
        --  обрабатываем ошибки
        RAISE_APPLICATION_ERROR(-20002, 
            'Ошибка в триггере update_stock_trigger: ' || SQLERRM);
END update_stock_trigger;
/

--  Вставим операцию 
INSERT INTO Operations (operation_id, product_id, warehouse_id, operation_type, quantity)
VALUES (1, 101, 1, 1, 100);

--  Проверяем, что триггер сработал
SELECT * FROM Stock;
SELECT * FROM Operations;

-- Сначала создайте базу
CREATE DATABASE web_form_db;-- Переключитесь на неё
USE web_form_db;-- Создайте таблицу users
CREATE TABLE users (
    id INT AUTO_INCREMENT PRIMARY KEY,
    full_name VARCHAR(255) NOT NULL,
    phone VARCHAR(20) NOT NULL,
    email VARCHAR(255) NOT NULL,
    birth_date DATE NOT NULL,
    gender ENUM('male', 'female', 'other') NOT NULL,
    biography TEXT,
    contract TEXT,
    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP
);-- Создайте таблицу языков
CREATE TABLE programming_languages (
    id INT AUTO_INCREMENT PRIMARY KEY,
    name VARCHAR(50) NOT NULL UNIQUE
);-- Создайте таблицу связей
CREATE TABLE user_languages (
    user_id INT NOT NULL,
    language_id INT NOT NULL,
    PRIMARY KEY (user_id, language_id),
    FOREIGN KEY (user_id) REFERENCES users(id) ON DELETE CASCADE,
    FOREIGN KEY (language_id) REFERENCES programming_languages(id) ON DELETE CASCADE
);-- Добавьте языки
INSERT INTO programming_languages (name) VALUES 
    ('Pascal'), ('C'), ('C++'), ('JavaScript'), ('PHP'),
    ('Python'), ('Java'), ('Haskell'), ('Clojure'),
    ('Prolog'), ('Scala'), ('Go');

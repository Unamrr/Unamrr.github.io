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




config.php
    <?php
$host = 'localhost';     // или ваш хост
$dbname = 'web_form_db'; // имя базы
$username = 'root';      // ваш логин
$password = '';          // ваш пароль (часто пустой)

try {
    $pdo = new PDO("mysql:host=$host;dbname=$dbname;charset=utf8mb4", $username, $password);
    $pdo->setAttribute(PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION);
} catch(PDOException $e) {
    die("Ошибка подключения: " . $e->getMessage());
}
?>
    
save.php
<?php
require_once 'config.php';

if ($_SERVER['REQUEST_METHOD'] === 'POST') {
    // Получаем данные из формы
    $full_name = $_POST['full_name'];
    $phone = $_POST['phone'];
    $email = $_POST['email'];
    $birth_date = $_POST['birth_date'];
    $gender = $_POST['gender'];
    $biography = $_POST['biography'];
    $contract = $_POST['contract'];
    $languages = $_POST['languages'] ?? [];
    
    // Валидация (проверка)
    $errors = [];
    
    if (!preg_match('/^[a-zA-Zа-яА-ЯёЁ\s\-]+$/u', $full_name)) {
        $errors[] = 'ФИО должно содержать только буквы и пробелы';
    }
    
    if (!filter_var($email, FILTER_VALIDATE_EMAIL)) {
        $errors[] = 'Некорректный email';
    }
    
    // Если есть ошибки
    if (!empty($errors)) {
        session_start();
        $_SESSION['message'] = [
            'type' => 'error',
            'text' => implode('<br>', $errors)
        ];
        header('Location: index.html');
        exit;
    }
    
    // Сохраняем в базу
    try {
        // Начинаем транзакцию
        $pdo->beginTransaction();
        
        // 1. Сохраняем пользователя
        $sql = "INSERT INTO users (full_name, phone, email, birth_date, gender, biography, contract) 
                VALUES (?, ?, ?, ?, ?, ?, ?)";
        $stmt = $pdo->prepare($sql);
        $stmt->execute([$full_name, $phone, $email, $birth_date, $gender, $biography, $contract]);
        
        $user_id = $pdo->lastInsertId();
        
        // 2. Сохраняем языки программирования
        if (!empty($languages)) {
            $sql = "INSERT INTO user_languages (user_id, language_id) 
                    SELECT ?, id FROM programming_languages WHERE name = ?";
            $stmt = $pdo->prepare($sql);
            
            foreach ($languages as $lang) {
                $stmt->execute([$user_id, $lang]);
            }
        }
        
        // Подтверждаем транзакцию
        $pdo->commit();
        
        // Сообщение об успехе
        session_start();
        $_SESSION['message'] = [
            'type' => 'success',
            'text' => 'Данные успешно сохранены!'
        ];
        
    } catch (Exception $e) {
        // Отменяем транзакцию при ошибке
        $pdo->rollBack();
        
        session_start();
        $_SESSION['message'] = [
            'type' => 'error',
            'text' => 'Ошибка сохранения: ' . $e->getMessage()
        ];
    }
    
    header('Location: index.html');
    exit;
}
?>USE web_form_db;
SELECT * FROM users;
SELECT * FROM user_languages;

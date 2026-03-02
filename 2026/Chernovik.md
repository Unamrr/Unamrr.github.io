ALTER TABLE application 
ADD COLUMN phone VARCHAR(20) NOT NULL DEFAULT '',
ADD COLUMN email VARCHAR(100) NOT NULL DEFAULT '',
ADD COLUMN birth_date DATE,
ADD COLUMN gender ENUM('male', 'female', 'other') NOT NULL,
ADD COLUMN biography TEXT NOT NULL,
ADD COLUMN contract_accepted TINYINT(1) NOT NULL DEFAULT 0; 




-- Таблица языков
CREATE TABLE programming_languages (
    id INT UNSIGNED NOT NULL AUTO_INCREMENT,
    name VARCHAR(50) NOT NULL UNIQUE,
    PRIMARY KEY (id)
);

-- Заполняем языками
INSERT INTO programming_languages (name) VALUES 
('Pascal'), ('C'), ('C++'), ('JavaScript'), ('PHP'), 
('Python'), ('Java'), ('Haskell'), ('Clojure'), 
('Prolog'), ('Scala'), ('Go');

-- Таблица связи
CREATE TABLE application_languages (
    application_id INT UNSIGNED NOT NULL,
    language_id INT UNSIGNED NOT NULL,
    PRIMARY KEY (application_id, language_id),
    FOREIGN KEY (application_id) REFERENCES application(id) ON DELETE CASCADE,
    FOREIGN KEY (language_id) REFERENCES programming_languages(id) ON DELETE CASCADE
);$stmt = $db->prepare("
    INSERT INTO application 
    (fio, year, phone, email, birth_date, gender, biography, contract_accepted) 
    VALUES (?, ?, ?, ?, ?, ?, ?, ?)
");
$stmt->execute([
    $_POST['fio'], 
    $_POST['year'],
    $_POST['phone'],
    $_POST['email'],
    $_POST['birth_date'],
    $_POST['gender'],
    $_POST['biography'],
    isset($_POST['contract_accepted']) ? 1 : 0
]);$application_id = $db->lastInsertId();
$stmt = $db->prepare("INSERT INTO application_languages (application_id, language_id) VALUES (?, ?)");
foreach ($_POST['languages'] as $lang_id) {
    $stmt->execute([$application_id, $lang_id]);
}

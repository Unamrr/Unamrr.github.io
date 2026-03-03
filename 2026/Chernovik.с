try {
  // 1. СНАЧАЛА вставляем основную заявку
  $stmt = $db->prepare("INSERT INTO application (fio, year, phone, email, birth_date, gender, biography, contract_accepted) VALUES (?, ?, ?, ?, ?, ?, ?, ?)");
  $stmt->execute([
    $_POST['fio'], 
    $_POST['year'],
    $_POST['phone'],
    $_POST['email'],
    $_POST['birth_date'],
    $_POST['gender'],
    $_POST['biography'],
    isset($_POST['contract_accepted']) ? 1 : 0
  ]);
  
  // 2. ПОТОМ получаем ID только что вставленной записи
  $application_id = $db->lastInsertId();
  
  // 3. ЗАТЕМ вставляем языки (ВОТ СЮДА!)
  $stmt = $db->prepare("INSERT INTO application_languages (application_id, language_id) VALUES (?, ?)");
  foreach ($_POST['languages'] as $lang_id) {
    $stmt->execute([$application_id, $lang_id]);
  }
  
  // 4. И ТОЛЬКО ПОТОМ редирект
  header('Location: ?save=1');
  exit();
  
}
catch(PDOException $e){
  print('Error : ' . $e->getMessage());
  exit();
}




CREATE TABLE application (
    id INT UNSIGNED NOT NULL AUTO_INCREMENT,
    fio VARCHAR(150) NOT NULL DEFAULT '',
    phone VARCHAR(20) NOT NULL DEFAULT '',
    email VARCHAR(100) NOT NULL DEFAULT '',
    birth_date DATE NOT NULL,
    gender ENUM('male', 'female', 'other') NOT NULL,
    biography TEXT NOT NULL,
    contract_accepted TINYINT(1) NOT NULL DEFAULT 0,
    PRIMARY KEY (id)
);


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










header('Content-Type: text/html; charset=UTF-8');

// 🔥 НОВОЕ: функция для проверки полей
function validate_field($value, $pattern, $field_name, &$errors, &$error_fields) {
    if (empty($value)) {
        $errors[] = "Поле $field_name обязательно";
        $error_fields[] = $field_name;
        return false;
    }
    if (!preg_match($pattern, $value)) {
        $errors[] = "Поле $field_name содержит недопустимые символы";
        $error_fields[] = $field_name;
        return false;
    }
    return true;
}

if ($_SERVER['REQUEST_METHOD'] == 'GET') {
    // 🔥 НОВОЕ: читаем cookies
    $saved_data = [];
    $errors = [];
    $error_fields = [];

    if (!empty($_COOKIE['form_data'])) {
        $saved_data = unserialize($_COOKIE['form_data']);
        setcookie('form_data', '', time() - 3600, '/'); // удаляем после прочтения
    }

    if (!empty($_COOKIE['errors'])) {
        $errors = unserialize($_COOKIE['errors']);
        setcookie('errors', '', time() - 3600, '/');
    }

    if (!empty($_COOKIE['error_fields'])) {
        $error_fields = unserialize($_COOKIE['error_fields']);
        setcookie('error_fields', '', time() - 3600, '/');
    }

    if (!empty($_GET['save'])) {
        print('Спасибо, результаты сохранены.');
    }
    
    include('form.php');
    exit();
}


// Вместо старого кода с $errors = [] вставляем ЭТО:

$errors = [];
$error_fields = []; // для подсветки

// ФИО
validate_field($_POST['fio'], '/^[а-яА-ЯёЁa-zA-Z\s\-]+$/u', 'ФИО', $errors, $error_fields);

// Телефон
validate_field($_POST['phone'], '/^[\d\s\+\-\(\)]+$/', 'Телефон', $errors, $error_fields);

// Email
if (empty($_POST['email'])) {
    $errors[] = 'Email обязателен';
    $error_fields[] = 'email';
} elseif (!filter_var($_POST['email'], FILTER_VALIDATE_EMAIL)) {
    $errors[] = 'Некорректный email';
    $error_fields[] = 'email';
}

// Дата рождения
if (empty($_POST['birth_date'])) {
    $errors[] = 'Дата рождения обязательна';
    $error_fields[] = 'birth_date';
}

// Пол
if (empty($_POST['gender']) || !in_array($_POST['gender'], ['male', 'female'])) {
    $errors[] = 'Выберите пол';
    $error_fields[] = 'gender';
}

// Языки
if (empty($_POST['languages']) || !is_array($_POST['languages'])) {
    $errors[] = 'Выберите языки';
    $error_fields[] = 'languages';
}

// Биография
if (empty($_POST['biography'])) {
    $errors[] = 'Заполните биографию';
    $error_fields[] = 'biography';
}

// Чекбокс
if (empty($_POST['contract_accepted'])) {
    $errors[] = 'Подтвердите контракт';
    $error_fields[] = 'contract_accepted';
}



if (!empty($errors)) {
    setcookie('errors', serialize($errors), time() + 3600, '/');
    setcookie('error_fields', serialize($error_fields), time() + 3600, '/');
    setcookie('form_data', serialize($_POST), time() + 3600, '/');
    header('Location: index.php');
    exit();
}


try {
    // Вставка в основную таблицу
    $stmt = $db->prepare("INSERT INTO application (fio, phone, email, birth_date, gender, biography, contract_accepted) VALUES (?, ?, ?, ?, ?, ?, ?)");
    $stmt->execute([
        $_POST['fio'],
        $_POST['phone'],
        $_POST['email'],
        $_POST['birth_date'],
        $_POST['gender'],
        $_POST['biography'],
        isset($_POST['contract_accepted']) ? 1 : 0
    ]);

    $application_id = $db->lastInsertId();

    // Вставка языков
    $stmt = $db->prepare("INSERT INTO application_languages (application_id, language_id) VALUES (?, ?)");
    foreach ($_POST['languages'] as $lang_id) {
        $stmt->execute([$application_id, $lang_id]);
    }

    // 🔥 🔥 🔥 ВОТ ЗДЕСЬ - ПОСЛЕ ВСТАВКИ В БД, ДО РЕДИРЕКТА 🔥 🔥 🔥
    setcookie('saved_fio', $_POST['fio'], time() + 365*24*3600, '/');
    setcookie('saved_phone', $_POST['phone'], time() + 365*24*3600, '/');
    setcookie('saved_email', $_POST['email'], time() + 365*24*3600, '/');
    setcookie('saved_birth_date', $_POST['birth_date'], time() + 365*24*3600, '/');
    setcookie('saved_gender', $_POST['gender'], time() + 365*24*3600, '/');
    setcookie('saved_biography', $_POST['biography'], time() + 365*24*3600, '/');
    setcookie('saved_contract', isset($_POST['contract_accepted']) ? 'checked' : '', time() + 365*24*3600, '/');

    header('Location: ?save=1');
    exit();

} catch(PDOException $e) {
    print('Error : ' . $e->getMessage());
    exit();
}

в form.php

<?php
// Значения для полей (приоритет: POST > cookies от ошибок > сохраненные cookies)
$fio = $_POST['fio'] ?? $saved_data['fio'] ?? $_COOKIE['saved_fio'] ?? '';
$phone = $_POST['phone'] ?? $saved_data['phone'] ?? $_COOKIE['saved_phone'] ?? '';
$email = $_POST['email'] ?? $saved_data['email'] ?? $_COOKIE['saved_email'] ?? '';
$birth_date = $_POST['birth_date'] ?? $saved_data['birth_date'] ?? $_COOKIE['saved_birth_date'] ?? '';
$gender = $_POST['gender'] ?? $saved_data['gender'] ?? $_COOKIE['saved_gender'] ?? '';
$biography = $_POST['biography'] ?? $saved_data['biography'] ?? $_COOKIE['saved_biography'] ?? '';
$contract = isset($_POST['contract_accepted']) ? 'checked' : ($saved_data['contract_accepted'] ?? $_COOKIE['saved_contract'] ?? '');
$selected_langs = $_POST['languages'] ?? $saved_data['languages'] ?? [];
?>

<?php if (!empty($errors)): ?>
    <div style="color: red; border: 2px solid red; padding: 10px; margin-bottom: 20px;">
        <strong>Исправьте ошибки:</strong>
        <?php foreach ($errors as $error): ?>
            <p><?= htmlspecialchars($error) ?></p>
        <?php endforeach; ?>
    </div>
<?php endif; ?>

<!-- ФИО -->
<input type="text" name="fio" 
       value="<?= htmlspecialchars($fio) ?>"
       class="<?= in_array('fio', $error_fields) ? 'error' : '' ?>">

<!-- Телефон -->
<input type="tel" name="phone" 
       value="<?= htmlspecialchars($phone) ?>"
       class="<?= in_array('phone', $error_fields) ? 'error' : '' ?>">

<!-- Аналогично для всех полей... -->


<style>
    .error {
        border: 2px solid red !important;
        background-color: #fff0f0;
    }
</style>
полный индекс 
<?php
header('Content-Type: text/html; charset=UTF-8');

// Функция для валидации
function validate_field($value, $pattern, $field_name, &$errors, &$error_fields) {
    if (empty($value)) {
        $errors[] = "Поле $field_name обязательно";
        $error_fields[] = $field_name;
        return false;
    }
    if (!preg_match($pattern, $value)) {
        $errors[] = "Поле $field_name содержит недопустимые символы";
        $error_fields[] = $field_name;
        return false;
    }
    return true;
}

// GET запрос
if ($_SERVER['REQUEST_METHOD'] == 'GET') {
    $saved_data = [];
    $errors = [];
    $error_fields = [];

    if (!empty($_COOKIE['form_data'])) {
        $saved_data = unserialize($_COOKIE['form_data']);
        setcookie('form_data', '', time() - 3600, '/');
    }
    if (!empty($_COOKIE['errors'])) {
        $errors = unserialize($_COOKIE['errors']);
        setcookie('errors', '', time() - 3600, '/');
    }
    if (!empty($_COOKIE['error_fields'])) {
        $error_fields = unserialize($_COOKIE['error_fields']);
        setcookie('error_fields', '', time() - 3600, '/');
    }

    if (!empty($_GET['save'])) {
        print('Спасибо, результаты сохранены.');
    }
    
    include('form.php');
    exit();
}

// POST запрос - валидация
$errors = [];
$error_fields = [];

validate_field($_POST['fio'], '/^[а-яА-ЯёЁa-zA-Z\s\-]+$/u', 'ФИО', $errors, $error_fields);
validate_field($_POST['phone'], '/^[\d\s\+\-\(\)]+$/', 'Телефон', $errors, $error_fields);

if (empty($_POST['email'])) {
    $errors[] = 'Email обязателен';
    $error_fields[] = 'email';
} elseif (!filter_var($_POST['email'], FILTER_VALIDATE_EMAIL)) {
    $errors[] = 'Некорректный email';
    $error_fields[] = 'email';
}

if (empty($_POST['birth_date'])) {
    $errors[] = 'Дата рождения обязательна';
    $error_fields[] = 'birth_date';
}

if (empty($_POST['gender']) || !in_array($_POST['gender'], ['male', 'female'])) {
    $errors[] = 'Выберите пол';
    $error_fields[] = 'gender';
}

if (empty($_POST['languages']) || !is_array($_POST['languages'])) {
    $errors[] = 'Выберите хотя бы один язык';
    $error_fields[] = 'languages';
}

if (empty($_POST['biography'])) {
    $errors[] = 'Заполните биографию';
    $error_fields[] = 'biography';
}

if (empty($_POST['contract_accepted'])) {
    $errors[] = 'Подтвердите контракт';
    $error_fields[] = 'contract_accepted';
}

// Если есть ошибки
if (!empty($errors)) {
    setcookie('errors', serialize($errors), time() + 3600, '/');
    setcookie('error_fields', serialize($error_fields), time() + 3600, '/');
    setcookie('form_data', serialize($_POST), time() + 3600, '/');
    header('Location: index.php');
    exit();
}

// Сохранение в БД
$user = 'u82379';
$pass = '8400862';
$db = new PDO('mysql:host=localhost;dbname=u82379', $user, $pass,
    [PDO::ATTR_PERSISTENT => true, PDO::ATTR_ERRMODE => PDO::ERRMODE_EXCEPTION]);

try {
    $stmt = $db->prepare("INSERT INTO application (fio, phone, email, birth_date, gender, biography, contract_accepted) VALUES (?, ?, ?, ?, ?, ?, ?)");
    $stmt->execute([
        $_POST['fio'],
        $_POST['phone'],
        $_POST['email'],
        $_POST['birth_date'],
        $_POST['gender'],
        $_POST['biography'],
        isset($_POST['contract_accepted']) ? 1 : 0
    ]);

    $application_id = $db->lastInsertId();
    
    $stmt = $db->prepare("INSERT INTO application_languages (application_id, language_id) VALUES (?, ?)");
    foreach ($_POST['languages'] as $lang_id) {
        $stmt->execute([$application_id, $lang_id]);
    }

    // Cookies на год
    setcookie('saved_fio', $_POST['fio'], time() + 365*24*3600, '/');
    setcookie('saved_phone', $_POST['phone'], time() + 365*24*3600, '/');
    setcookie('saved_email', $_POST['email'], time() + 365*24*3600, '/');
    setcookie('saved_birth_date', $_POST['birth_date'], time() + 365*24*3600, '/');
    setcookie('saved_gender', $_POST['gender'], time() + 365*24*3600, '/');
    setcookie('saved_biography', $_POST['biography'], time() + 365*24*3600, '/');
    setcookie('saved_contract', isset($_POST['contract_accepted']) ? 'checked' : '', time() + 365*24*3600, '/');

    header('Location: ?save=1');
    exit();

} catch(PDOException $e) {
    print('Error : ' . $e->getMessage());
    exit();
}
?>


полный форм 
<?php
// Значения для полей
$fio = $_POST['fio'] ?? $saved_data['fio'] ?? $_COOKIE['saved_fio'] ?? '';
$phone = $_POST['phone'] ?? $saved_data['phone'] ?? $_COOKIE['saved_phone'] ?? '';
$email = $_POST['email'] ?? $saved_data['email'] ?? $_COOKIE['saved_email'] ?? '';
$birth_date = $_POST['birth_date'] ?? $saved_data['birth_date'] ?? $_COOKIE['saved_birth_date'] ?? '';
$gender = $_POST['gender'] ?? $saved_data['gender'] ?? $_COOKIE['saved_gender'] ?? '';
$biography = $_POST['biography'] ?? $saved_data['biography'] ?? $_COOKIE['saved_biography'] ?? '';
$contract = isset($_POST['contract_accepted']) ? 'checked' : ($saved_data['contract_accepted'] ?? $_COOKIE['saved_contract'] ?? '');
$selected_langs = $_POST['languages'] ?? $saved_data['languages'] ?? [];
?>

<!-- Вывод ошибок -->
<?php if (!empty($errors)): ?>
    <div style="color: red; border: 2px solid red; padding: 10px; margin-bottom: 20px;">
        <strong>Исправьте ошибки:</strong>
        <?php foreach ($errors as $error): ?>
            <p><?= htmlspecialchars($error) ?></p>
        <?php endforeach; ?>
    </div>
<?php endif; ?>

<form action="" method="POST">
    <!-- 1. ФИО -->
    <label>ФИО:</label><br>
    <input type="text" name="fio" value="<?= htmlspecialchars($fio) ?>" 
           style="<?= in_array('fio', $error_fields) ? 'border: 2px solid red;' : '' ?>">
    <br><br>

    <!-- 2. Телефон -->
    <label>Телефон:</label><br>
    <input type="tel" name="phone" value="<?= htmlspecialchars($phone) ?>"
           style="<?= in_array('phone', $error_fields) ? 'border: 2px solid red;' : '' ?>">
    <br><br>

    <!-- 3. E-mail -->
    <label>E-mail:</label><br>
    <input type="email" name="email" value="<?= htmlspecialchars($email) ?>"
           style="<?= in_array('email', $error_fields) ? 'border: 2px solid red;' : '' ?>">
    <br><br>

    <!-- 4. Дата рождения -->
    <label>Дата рождения:</label><br>
    <input type="date" name="birth_date" value="<?= htmlspecialchars($birth_date) ?>"
           style="<?= in_array('birth_date', $error_fields) ? 'border: 2px solid red;' : '' ?>">
    <br><br>

    <!-- 5. Пол -->
    <label>Пол:</label><br>
    <input type="radio" name="gender" value="male" <?= $gender == 'male' ? 'checked' : '' ?>
           style="<?= in_array('gender', $error_fields) ? 'outline: 2px solid red;' : '' ?>"> Мужской
    <input type="radio" name="gender" value="female" <?= $gender == 'female' ? 'checked' : '' ?>
           style="<?= in_array('gender', $error_fields) ? 'outline: 2px solid red;' : '' ?>"> Женский
    <br><br>

    <!-- 6. Языки программирования -->
    <label>Любимые языки программирования:</label><br>
    <select name="languages[]" multiple size="6"
            style="<?= in_array('languages', $error_fields) ? 'border: 2px solid red;' : '' ?>">
        <?php
        $langs = [
            1 => 'Pascal', 2 => 'C', 3 => 'C++', 4 => 'JavaScript',
            5 => 'PHP', 6 => 'Python', 7 => 'Java', 8 => 'Haskell',
            9 => 'Clojure', 10 => 'Prolog', 11 => 'Scala', 12 => 'Go'
        ];
        foreach ($langs as $id => $name):
            $selected = in_array($id, $selected_langs) ? 'selected' : '';
        ?>
            <option value="<?= $id ?>" <?= $selected ?>><?= $name ?></option>
        <?php endforeach; ?>
    </select>
    <br><small>(Зажми Ctrl чтобы выбрать несколько)</small>
    <br><br>

    <!-- 7. Биография -->
    <label>Биография:</label><br>
    <textarea name="biography" rows="5" cols="40"
              style="<?= in_array('biography', $error_fields) ? 'border: 2px solid red;' : '' ?>"><?= htmlspecialchars($biography) ?></textarea>
    <br><br>

    <!-- 8. Чекбокс -->
    <input type="checkbox" name="contract_accepted" <?= $contract ?>
           style="<?= in_array('contract_accepted', $error_fields) ? 'outline: 2px solid red;' : '' ?>">
    <label>С контрактом ознакомлен(а)</label>
    <br><br>

    <!-- 9. Кнопка -->
    <input type="submit" value="Сохранить">
</form>

<?php
header('Content-Type: text/html; charset=UTF-8');

// Настройки БД
$db_user = 'u82379';
$db_pass = '8400862';
$db = new PDO('mysql:host=localhost;dbname=u82379', $db_user, $db_pass);
$db->setAttribute(PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION);

// GET запрос — показываем форму
if ($_SERVER['REQUEST_METHOD'] == 'GET') {
    $errors = [];
    $error_fields = [];
    $saved_data = [];
    $messages = [];

    // Читаем cookies если были ошибки
    if (!empty($_COOKIE['errors'])) {
        $errors = unserialize($_COOKIE['errors']);
        $error_fields = unserialize($_COOKIE['error_fields']);
        $saved_data = unserialize($_COOKIE['saved_data']);

        setcookie('errors', '', time() - 3600, '/');
        setcookie('error_fields', '', time() - 3600, '/');
        setcookie('saved_data', '', time() - 3600, '/');
    }

    // Проверяем авторизацию через сессию
    if (!empty($_COOKIE[session_name()])) {
        session_start();
        if (!empty($_SESSION['login']) && !empty($_SESSION['user_id'])) {
            try {
                $stmt = $db->prepare("SELECT * FROM application WHERE id = ?");
                $stmt->execute([$_SESSION['user_id']]);
                $user_data = $stmt->fetch(PDO::FETCH_ASSOC);

                if ($user_data) {
                    $saved_data = [
                        'fio' => $user_data['fio'],
                        'phone' => $user_data['phone'],
                        'email' => $user_data['email'],
                        'birth_date' => $user_data['birth_date'],
                        'gender' => $user_data['gender'],
                        'biography' => $user_data['biography'],
                        'contract_accepted' => $user_data['contract_accepted']
                    ];

                    $stmt_lang = $db->prepare("SELECT language_id FROM application_languages WHERE application_id = ?");
                    $stmt_lang->execute([$_SESSION['user_id']]);
                    $saved_data['languages'] = $stmt_lang->fetchAll(PDO::FETCH_COLUMN);
                }
            } catch (PDOException $e) {
                $messages[] = 'Ошибка загрузки данных';
            }
        }
    }

    if (!empty($_GET['save'])) {
        $messages[] = 'Спасибо, результаты сохранены.';

        if (!empty($_COOKIE['generated_login']) && !empty($_COOKIE['generated_pass'])) {
            $messages[] = sprintf('Вы можете <a href="login.php">войти</a> с логином <strong>%s</strong>
                и паролем <strong>%s</strong> для изменения данных.',
                htmlspecialchars($_COOKIE['generated_login']),
                htmlspecialchars($_COOKIE['generated_pass']));

            setcookie('generated_login', '', time() - 3600, '/');
            setcookie('generated_pass', '', time() - 3600, '/');
        }
    }

    include('form.php'); exit();
}

// POST запрос — проверяем и сохраняем
$errors = [];
$error_fields = [];

// Проверка ФИО
if (empty($_POST['fio'])) {
    $errors[] = 'Заполните ФИО';
    $error_fields[] = 'fio';
}

// Проверка телефона
if (empty($_POST['phone'])) {
    $errors[] = 'Заполните телефон';
    $error_fields[] = 'phone';
}

// Проверка email
if (empty($_POST['email'])) {
    $errors[] = 'Заполните email';
    $error_fields[] = 'email';
}

// Проверка даты
if (empty($_POST['birth_date'])) {
    $errors[] = 'Заполните дату рождения';
    $error_fields[] = 'birth_date';
}

// Проверка пола
if (empty($_POST['gender'])) {
    $errors[] = 'Выберите пол';
    $error_fields[] = 'gender';
}
// Проверка языков
if (empty($_POST['languages'])) {
    $errors[] = 'Выберите языки';
    $error_fields[] = 'languages';
}

// Проверка биографии
if (empty($_POST['biography'])) {
    $errors[] = 'Заполните биографию';
    $error_fields[] = 'biography';
}

// Проверка чекбокса
if (empty($_POST['contract_accepted'])) {
    $errors[] = 'Подтвердите контракт';
    $error_fields[] = 'contract_accepted';
}

// Если есть ошибки — сохраняем в cookies и возвращаем
if (!empty($errors)) {
    setcookie('errors', serialize($errors), time() + 3600, '/');
    setcookie('error_fields', serialize($error_fields), time() + 3600, '/');
    setcookie('saved_data', serialize($_POST), time() + 3600, '/');
    header('Location: index.php');
    exit();
}

// Проверяем, авторизован ли пользователь
$is_authorized = false;
$user_id = null;
if (!empty($_COOKIE[session_name()])) {
    session_start();
    if (!empty($_SESSION['login']) && !empty($_SESSION['user_id'])) {
        $is_authorized = true;
        $user_id = $_SESSION['user_id'];
    }
}

try {
    if ($is_authorized && $user_id) {
        // Обновляем данные авторизованного пользователя
        $stmt = $db->prepare("UPDATE application SET
            fio = ?, phone = ?, email = ?, birth_date = ?,
            gender = ?, biography = ?, contract_accepted = ?
            WHERE id = ?");
        $stmt->execute([
            $_POST['fio'],
            $_POST['phone'],
            $_POST['email'],
            $_POST['birth_date'],
            $_POST['gender'],
            $_POST['biography'],
            1,
            $user_id
        ]);

        // Обновляем языки
        $stmt_del = $db->prepare("DELETE FROM application_languages WHERE application_id = ?");
        $stmt_del->execute([$user_id]);

        $stmt_lang = $db->prepare("INSERT INTO application_languages (application_id, language_id) VALUES (?, ?)");
        foreach ($_POST['languages'] as $lang_id) {
            $stmt_lang->execute([$user_id, $lang_id]);
        }  } else {
        // Новый пользователь — вставляем данные
        $stmt = $db->prepare("INSERT INTO application (fio, phone, email, birth_date, gender, biography, contract_accepted)
            VALUES (?, ?, ?, ?, ?, ?, ?)");
        $stmt->execute([
            $_POST['fio'],
            $_POST['phone'],
            $_POST['email'],
            $_POST['birth_date'],
            $_POST['gender'],
            $_POST['biography'],
            1
        ]);

        $app_id = $db->lastInsertId();

        // Вставляем языки
        $stmt_lang = $db->prepare("INSERT INTO application_languages (application_id, language_id) VALUES (?, ?)");
        foreach ($_POST['languages'] as $lang_id) {
            $stmt_lang->execute([$app_id, $lang_id]);
        }

        // Генерируем логин и пароль
        $login = 'user_' . substr(md5(uniqid($app_id, true)), 0, 8);
        $pass = substr(md5(uniqid(mt_rand(), true)), 0, 8);
        $pass_hash = password_hash($pass, PASSWORD_DEFAULT);

        $stmt_user = $db->prepare("INSERT INTO users (login, password_hash, application_id) VALUES (?, ?, ?)");
        $stmt_user->execute([$login, $pass_hash, $app_id]);

        setcookie('generated_login', $login, time() + 3600, '/');
        setcookie('generated_pass', $pass, time() + 3600, '/');
    }

    // Сохраняем куки для неавторизованных
    setcookie('saved_fio', $_POST['fio'], time() + 365*24*3600, '/');
    setcookie('saved_phone', $_POST['phone'], time() + 365*24*3600, '/');
    setcookie('saved_email', $_POST['email'], time() + 365*24*3600, '/');

    header('Location: ?save=1');
    exit();

} catch (PDOException $e) {
    print('Ошибка БД: ' . $e->getMessage());
    exit();
}
?>



                if ($user_data) {

<?php
error_reporting(0);
ini_set('display_errors', 0);

header('Content-Type: text/html; charset=UTF-8');

$db_user = 'u82379';
$db_pass = '8400862';
$db = new PDO('mysql:host=localhost;dbname=u82379', $db_user, $db_pass);
$db->setAttribute(PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION);

session_start();

// CSRF токен
if (empty($_SESSION['csrf_token'])) {
    $_SESSION['csrf_token'] = bin2hex(random_bytes(32));
}

$session_started = false;
if (!empty($_COOKIE[session_name()])) {
    if (!empty($_SESSION['login'])) {
        header('Location: ./');
        exit();
    }
}

if ($_SERVER['REQUEST_METHOD'] == 'GET') {
    ?>
    <!DOCTYPE html>
    <html>
    <head>
        <meta charset="UTF-8">
        <title>Вход</title>
        <style>
            .error { color: red; border: 1px solid red; padding: 10px; margin-bottom: 10px; }
            form { margin: 20px; }
            input { margin: 5px; }
        </style>
    </head>
    <body>
        <?php if (!empty($_GET['error'])): ?>
            <div class="error">Неверный логин или пароль</div>
        <?php endif; ?>
        
        <form action="" method="post">
            <input type="hidden" name="csrf_token" value="<?= $_SESSION['csrf_token'] ?>">
            <label>Логин:</label><br>
            <input type="text" name="login" required><br>
            <label>Пароль:</label><br>
            <input type="password" name="pass" required><br><br>
            <input type="submit" value="Войти">
        </form>
        <p><a href="./">На главную</a></p>
    </body>
    </html>
    <?php
    exit();
}

if ($_SERVER['REQUEST_METHOD'] == 'POST') {
    // Проверка CSRF
    if (empty($_POST['csrf_token']) || !hash_equals($_SESSION['csrf_token'], $_POST['csrf_token'])) {
        die('CSRF атака!');
    }
    
    $login = $_POST['login'] ?? '';
    $pass = $_POST['pass'] ?? '';
    
    if (empty($login) || empty($pass)) {
        header('Location: login.php?error=1');
        exit();
    }
    
    try {
        $stmt = $db->prepare("SELECT u.id, u.login, u.password_hash, u.application_id 
                               FROM users u 
                               WHERE u.login = ?");
        $stmt->execute([$login]);
        $user = $stmt->fetch(PDO::FETCH_ASSOC);
        
        if ($user && password_verify($pass, $user['password_hash'])) {
            $_SESSION['login'] = $user['login'];
            $_SESSION['user_id'] = $user['application_id'];
            $_SESSION['uid'] = $user['id'];
            
            header('Location: ./');
            exit();
        } else {
            header('Location: login.php?error=1');
            exit();
        }
    } catch (PDOException $e) {
        header('Location: login.php?error=1');
        exit();
    }
}
?>

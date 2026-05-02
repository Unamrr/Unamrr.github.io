<?php
header('Content-Type: text/html; charset=UTF-8');

$db_user = 'u82379';
$db_pass = '8400862';
$db = new PDO('mysql:host=localhost;dbname=u82379', $db_user, $db_pass);
$db->setAttribute(PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION);

// ПРОСТАЯ ПРОВЕРКА (как в test.php, но потом заменим на БД)
if (empty($_SERVER['PHP_AUTH_USER']) || 
    empty($_SERVER['PHP_AUTH_PW']) || 
    $_SERVER['PHP_AUTH_USER'] != 'admin' || 
    $_SERVER['PHP_AUTH_PW'] != '123') {
    
    header('HTTP/1.1 401 Unauthorized');
    header('WWW-Authenticate: Basic realm="Admin Panel"');
    print('<h1>401 Требуется авторизация</h1>');
    exit();
}

// ВСЁ, ЧТО НИЖЕ - ТОЛЬКО ПОСЛЕ УСПЕШНОГО ВХОДА

// Получаем всех пользователей
$users = $db->query("SELECT * FROM application ORDER BY id DESC")->fetchAll(PDO::FETCH_ASSOC);

// Статистика по языкам
$lang_stats = $db->query("
    SELECT pl.name, COUNT(al.language_id) as count 
    FROM programming_languages pl
    LEFT JOIN application_languages al ON pl.id = al.language_id
    GROUP BY pl.id
    ORDER BY count DESC
")->fetchAll(PDO::FETCH_ASSOC);

// Обработка удаления
if (isset($_POST['delete']) && isset($_POST['id'])) {
    $stmt = $db->prepare("DELETE FROM application WHERE id = ?");
    $stmt->execute([$_POST['id']]);
    header('Location: admin.php');
    exit();
}

// Обработка редактирования
if (isset($_POST['edit']) && isset($_POST['id'])) {
    $stmt = $db->prepare("UPDATE application SET 
        fio = ?, phone = ?, email = ?, birth_date = ?, 
        gender = ?, biography = ? 
        WHERE id = ?");
    $stmt->execute([
        $_POST['fio'],
        $_POST['phone'],
        $_POST['email'],
        $_POST['birth_date'],
        $_POST['gender'],
        $_POST['biography'],
        $_POST['id']
    ]);
    header('Location: admin.php');
    exit();
}

// Получаем данные для редактирования
$edit_data = null;
if (isset($_GET['edit_id'])) {
    $stmt = $db->prepare("SELECT * FROM application WHERE id = ?");
    $stmt->execute([$_GET['edit_id']]);
    $edit_data = $stmt->fetch(PDO::FETCH_ASSOC);
}

?>
<!DOCTYPE html>
<html>
<head>
    <meta charset="UTF-8">
    <title>Панель администратора</title>
    <style>
        body { font-family: Arial, sans-serif; margin: 20px; }
        table { border-collapse: collapse; width: 100%; margin-top: 20px; }
        th, td { border: 1px solid #ddd; padding: 8px; text-align: left; }
        th { background-color: #4CAF50; color: white; }
        .delete-btn { background-color: #f44336; color: white; border: none; padding: 5px 10px; cursor: pointer; }
        .edit-btn { background-color: #2196F3; color: white; border: none; padding: 5px 10px; cursor: pointer; }
        .stats { background-color: #e7f3fe; padding: 15px; margin: 20px 0; border-radius: 5px; }
        .edit-form { background-color: #fff3cd; padding: 15px; margin: 20px 0; border: 1px solid #ffc107; border-radius: 5px; }
    </style>
</head>
<body>

<h1>Панель администратора</h1>

<div class="stats">
    <h3>Статистика по языкам программирования</h3>
    <ul>
        <?php foreach ($lang_stats as $lang): ?>
            <li><strong><?= htmlspecialchars($lang['name']) ?>:</strong> <?= $lang['count'] ?> пользователей</li>
        <?php endforeach; ?>
    </ul>
</div>

<?php if ($edit_data): ?>
<div class="edit-form">
    <h3>Редактирование записи #<?= $edit_data['id'] ?></h3>
    <form method="post">
        <input type="hidden" name="id" value="<?= $edit_data['id'] ?>">
        <label>ФИО:</label><br>
        <input type="text" name="fio" value="<?= htmlspecialchars($edit_data['fio']) ?>" required><br>
        <label>Телефон:</label><br>
        <input type="text" name="phone" value="<?= htmlspecialchars($edit_data['phone']) ?>" required><br>
        <label>Email:</label><br>
        <input type="email" name="email" value="<?= htmlspecialchars($edit_data['email']) ?>" required><br>
        <label>Дата рождения:</label><br>
        <input type="date" name="birth_date" value="<?= $edit_data['birth_date'] ?>" required><br>
        <label>Пол:</label><br>
        <select name="gender">
            <option value="male" <?= $edit_data['gender'] == 'male' ? 'selected' : '' ?>>Мужской</option>
            <option value="female" <?= $edit_data['gender'] == 'female' ? 'selected' : '' ?>>Женский</option>
        </select><br><br>
        <label>Биография:</label><br>
        <textarea name="biography" rows="3" cols="40"><?= htmlspecialchars($edit_data['biography']) ?></textarea><br><br>
        <button type="submit" name="edit">Сохранить</button>
        <a href="admin.php">Отмена</a>
    </form>
</div>
<?php endif; ?>

<h2>Все пользователи</h2>
<table>
    <thead>
        <tr>
            <th>ID</th><th>ФИО</th><th>Телефон</th><th>Email</th><th>Дата рождения</th><th>Пол</th><th>Биография</th><th>Действия</th>
        </tr>
    </thead>
    <tbody>
        <?php foreach ($users as $user): ?>
        <tr>
            <td><?= $user['id'] ?></td>
            <td><?= htmlspecialchars($user['fio']) ?></td>
            <td><?= htmlspecialchars($user['phone']) ?></td>
            <td><?= htmlspecialchars($user['email']) ?></td>
            <td><?= $user['birth_date'] ?></td>
            <td><?= $user['gender'] == 'male' ? 'Мужской' : 'Женский' ?></td>
            <td><?= htmlspecialchars(substr($user['biography'], 0, 50)) ?>...</td>
            <td>
                <a href="?edit_id=<?= $user['id'] ?>" class="edit-btn">Редактировать</a>
                <form method="post" style="display:inline;" onsubmit="return confirm('Удалить?')">
                    <input type="hidden" name="id" value="<?= $user['id'] ?>">
                    <button type="submit" name="delete" class="delete-btn">Удалить</button>
                </form>
            </td>
        </tr>
        <?php endforeach; ?>
    </tbody>
</table>

<p><a href="index.php">На главную</a></p>

</body>
</html>

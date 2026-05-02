<?php
$fio = $_POST['fio'] ?? $saved_data['fio'] ?? $_COOKIE['saved_fio'] ?? '';
$phone = $_POST['phone'] ?? $saved_data['phone'] ?? $_COOKIE['saved_phone'] ?? '';
$email = $_POST['email'] ?? $saved_data['email'] ?? $_COOKIE['saved_email'] ?? '';
$birth_date = $_POST['birth_date'] ?? $saved_data['birth_date'] ?? '';
$gender = $_POST['gender'] ?? $saved_data['gender'] ?? '';
$biography = $_POST['biography'] ?? $saved_data['biography'] ?? '';
$selected_langs = $_POST['languages'] ?? $saved_data['languages'] ?? [];
?>

<!DOCTYPE html>
<html>
<head>
    <meta charset="UTF-8">
    <title>Анкета</title>
    <style>
        .error-field { border: 2px solid red; }
        .error-message { color: red; border: 2px solid red; padding: 10px; margin-bottom: 20px; }
        .message { border: 1px solid green; padding: 10px; margin-bottom: 20px; background-color: #e8f5e9; }
    </style>
</head>
<body>

<?php if (!empty($messages)): ?>
    <div class="message">
        <?php foreach ($messages as $message): ?>
            <p><?= $message ?></p>
        <?php endforeach; ?>
    </div>
<?php endif; ?>

<?php if (!empty($errors)): ?>
    <div class="error-message">
        <?php foreach ($errors as $error): ?>
            <p><?= htmlspecialchars($error) ?></p>
        <?php endforeach; ?>
    </div>
    </div>
<?php endif; ?>

<form action="" method="POST">
    <label>ФИО:</label><br>
    <input type="text" name="fio" value="<?= htmlspecialchars($fio) ?>"
           class="<?= in_array('fio', $error_fields) ? 'error-field' : '' ?>">
    <br><br>

    <label>Телефон:</label><br>
    <input type="tel" name="phone" value="<?= htmlspecialchars($phone) ?>"
           class="<?= in_array('phone', $error_fields) ? 'error-field' : '' ?>">
    <br><br>

    <label>Email:</label><br>
    <input type="email" name="email" value="<?= htmlspecialchars($email) ?>"
           class="<?= in_array('email', $error_fields) ? 'error-field' : '' ?>">
    <br><br>

    <label>Дата рождения:</label><br>
    <input type="date" name="birth_date" value="<?= htmlspecialchars($birth_date) ?>"
           class="<?= in_array('birth_date', $error_fields) ? 'error-field' : '' ?>">
    <br><br>

    <label>Пол:</label><br>
    <input type="radio" name="gender" value="male" <?= $gender == 'male' ? 'checked' : '' ?>> Мужской
    <input type="radio" name="gender" value="female" <?= $gender == 'female' ? 'checked' : '' ?>> Женский
    <?php if (in_array('gender', $error_fields)) echo '<span style="color:red"> (выберите пол)</span>'; ?>
    <br><br>

    <label>Языки программирования:</label><br>
    <select name="languages[]" multiple size="6"
            class="<?= in_array('languages', $error_fields) ? 'error-field' : '' ?>">
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
    <br><small>(Зажмите Ctrl для выбора нескольких)</small>
    <br><br>

    <label>Биография:</label><br>
    <textarea name="biography" rows="5" cols="40"
              class="<?= in_array('biography', $error_fields) ? 'error-field' : '' ?>"><?= htmlspecialchars($biography) ?></textarea>
    <br><br>

    <input type="checkbox" name="contract_accepted" value="1" <?= !empty($saved_data['contract_accepted']) ? 'checked' : '' ?>>
    <label>С контрактом ознакомлен(а)</label>
    <?php if (in_array('contract_accepted', $error_fields)) echo '<span style="color:red"> (обязательно)</span>'; ?>
    <br><br>

    <input type="submit" value="Сохранить">
</form>

</body>
</html>

<h2>Анкета</h2>

<form action="" method="POST">
    <!-- 1. ФИО -->
    <label>ФИО:</label><br>
    <input type="text" name="fio" required>
    <br><br>

    <!-- 2. Телефон -->
    <label>Телефон:</label><br>
    <input type="tel" name="phone" required>
    <br><br>

    <!-- 3. E-mail -->
    <label>E-mail:</label><br>
    <input type="email" name="email" required>
    <br><br>

    <!-- 4. Дата рождения -->
    <label>Дата рождения:</label><br>
    <input type="date" name="birth_date" required>
    <br><br>

    <!-- 5. Пол (радиокнопки) -->
    <label>Пол:</label><br>
    <input type="radio" name="gender" value="male" required> Мужской
    <input type="radio" name="gender" value="female" required> Женский
    <input type="radio" name="gender" value="other" required> Другой
    <br><br>

    <!-- 6. Любимые языки программирования -->
    <label>Любимые языки программирования:</label><br>
    <select name="languages[]" multiple size="6" required>
        <option value="1">Pascal</option>
        <option value="2">C</option>
        <option value="3">C++</option>
        <option value="4">JavaScript</option>
        <option value="5">PHP</option>
        <option value="6">Python</option>
        <option value="7">Java</option>
        <option value="8">Haskell</option>
        <option value="9">Clojure</option>
        <option value="10">Prolog</option>
        <option value="11">Scala</option>
        <option value="12">Go</option>
    </select>
    <br><small>(Зажми Ctrl чтобы выбрать несколько)</small>
    <br><br>

    <!-- 7. Биография -->
    <label>Биография:</label><br>
    <textarea name="biography" rows="5" cols="40" required></textarea>
    <br><br>

    <!-- 8. Чекбокс -->
    <input type="checkbox" name="contract_accepted" required>
    <label>С контрактом ознакомлен(а)</label>
    <br><br>

    <!-- 9. Кнопка -->
    <input type="submit" value="Сохранить">
</form>

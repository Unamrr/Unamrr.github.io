// Инициализация после загрузки DOM
window.addEventListener('DOMContentLoaded', function() {
    console.log("DOM fully loaded and parsed");
    
    // Находим элементы
    const quantityInput = document.getElementById('quantity');
    const productSelect = document.getElementById('product');
    const calculateBtn = document.getElementById('calculate-btn');
    const resultSpan = document.getElementById('result');
    const errorSpan = document.getElementById('error-message');
    
    // Вешаем обработчик на кнопку
    calculateBtn.addEventListener('click', calculatePrice);
    
    function calculatePrice() {
        // Сбрасываем сообщение об ошибке
        errorSpan.textContent = '';
        
        const quantity = quantityInput.value;
        const productPrice = parseFloat(productSelect.value);
        
        // ПРОВЕРКА РЕГУЛЯРНЫМ ВЫРАЖЕНИЕМ
        const numberRegex = /^\d+$/;
        
        if (!numberRegex.test(quantity)) {
            errorSpan.textContent = 'Ошибка! Введите только цифры.';
            resultSpan.textContent = '0';
            return;
        }
        
        // ПРЕОБРАЗОВАНИЕ СТРОКИ В ЧИСЛО С ПОМОЩЬЮ parseInt()
        const quantityNum = parseInt(quantity, 10);
        const totalPrice = productPrice * quantityNum;
        
        // Выводим результат
        resultSpan.textContent = totalPrice;
    }
});

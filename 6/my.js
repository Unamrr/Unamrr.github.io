"use strict";

function getPrices() {
  return {
    prodTypes: [800, 300, 100],  // Пицца:800, Обувь:300, Мармелад:100
    prodOptions: {
      option1: 200,  // Пляжная обувь
      option2: 500,  // Спортивная обувь  
      option3: 150   // Домашняя обувь
    },
    prodProperties: {
      prop1: 10,  // Кислый мармелад
      prop2: 20   // С остринкой
    }
  };
}

// Главная функция пересчёта стоимости
function updatePrice() {
  const prices = getPrices();
  const select = document.querySelector("select[name='prodType']");
  const quantityInput = document.querySelector("input[name='quantity']");
  const radiosDiv = document.getElementById("radios");
  const checkboxesDiv = document.getElementById("checkboxes");
  let price = 0;

  // Определяем базовую цену по типу
  const typeIndex = parseInt(select.value, 10) - 1;
  if (typeIndex >= 0) {
    price = prices.prodTypes[typeIndex];
  }

  // Отображаем нужные блоки в зависимости от типа
  radiosDiv.style.display = (select.value === "2") ? "block" : "none";
  checkboxesDiv.style.display = (select.value === "3") ? "block" : "none";

  // Если тип 2 — прибавляем цену выбранной опции
  if (select.value === "2") {
    const radios = document.querySelectorAll("input[name='prodOptions']");
    radios.forEach(radio => {
      if (radio.checked) {
        price += prices.prodOptions[radio.value];
      }
    });
  }

  // Если тип 3 — прибавляем цену выбранных свойств
  if (select.value === "3") {
    const checkboxes = document.querySelectorAll("#checkboxes input");
    checkboxes.forEach(checkbox => {
      if (checkbox.checked) {
        price += prices.prodProperties[checkbox.name];
      }
    });
  }

  // Умножаем на количество
  const quantity = parseInt(quantityInput.value, 10);
  if (!isNaN(quantity) && quantity > 0) {
    price *= quantity;
  }

  // Выводим цену
  document.getElementById("prodPrice").textContent = "Стоимость: " + price + " ₽";
}

// Подключаем обработчики событий при загрузке страницы
window.addEventListener("DOMContentLoaded", () => {
  const form = document.getElementById("calcForm");
  form.addEventListener("input", updatePrice);
  updatePrice();
});

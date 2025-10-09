function click1(event) {
  event.preventDefault();
  
  let quantityInput = document.getElementsByName("quantity")[0];
  let productSelect = document.getElementsByName("product")[0];
  let resultDiv = document.getElementById("result");
  
  let quantity = quantityInput.value;
  let product = productSelect.value;
  
  // ПРОВЕРКА РЕГУЛЯРНЫМ ВЫРАЖЕНИЕМ (обязательно!)
  const numberRegex = /^\d+$/;
  if (!numberRegex.test(quantity)) {
    resultDiv.innerHTML = "Ошибка! Введите только цифры";
    return false;
  }
  
  // ПРЕОБРАЗОВАНИЕ В ЧИСЛО
  quantity = parseInt(quantity);
  
  let price = 0;
  if (product == "v1") {
    price = 100 * quantity;
  } else if (product == "v2") {
    price = 450 * quantity;
  } else if (product == "v3") {
    price = 65 * quantity;
  } else if (product == "v4") {
    price = 310 * quantity;
  } else if (product == "v5") {
    price = 150 * quantity;
  } else {
    price = 300 * quantity;
  }
  
  resultDiv.innerHTML = price + " руб.";
  return false;
}

window.addEventListener('DOMContentLoaded', function (event) {
  console.log("DOM fully loaded and parsed");
  let button = document.getElementById("button1");
  button.addEventListener("click", click1);
});

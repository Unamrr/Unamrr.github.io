class FeedbackForm {
    constructor() {
        this.popupOverlay = document.getElementById('popupOverlay');
        this.feedbackForm = document.getElementById('feedbackForm');
        this.closeBtn = document.getElementById('closeBtn');
        this.submitBtn = document.getElementById('submitBtn');
        this.openFormBtn = document.querySelector('.open-form-btn');
        
        this.STORAGE_KEY = 'feedbackFormData';
        // ЗАМЕНИТЕ НА ВАШ РЕАЛЬНЫЙ URL ИЗ FORMCARRY ИЛИ ДРУГОГО СЕРВИСА
        this.FORMCARRY_URL = 'https://formcarry.com/s/ВАШ_ID_ФОРМЫ';
        
        this.init();
    }

    init() {
        // Восстановление данных из LocalStorage
        this.restoreFormData();
        
        // Обработчики событий
        this.openFormBtn.addEventListener('click', () => this.openPopup());
        this.closeBtn.addEventListener('click', () => this.closePopup());
        this.feedbackForm.addEventListener('submit', (e) => this.handleSubmit(e));
        
        // Сохранение данных при изменении
        this.feedbackForm.addEventListener('input', () => this.saveFormData());
        
        // Обработка кнопки "Назад" в браузере
        window.addEventListener('popstate', (e) => {
            if (e.state && e.state.popupOpen) {
                this.closePopup();
            }
        });

        // Закрытие по клику вне формы
        this.popupOverlay.addEventListener('click', (e) => {
            if (e.target === this.popupOverlay) {
                this.closePopup();
            }
        });

        // Закрытие по ESC
        document.addEventListener('keydown', (e) => {
            if (e.key === 'Escape' && this.popupOverlay.style.display === 'flex') {
                this.closePopup();
            }
        });
    }

    openPopup() {
        this.popupOverlay.style.display = 'flex';
        // Добавляем состояние в History API
        history.pushState({ popupOpen: true }, '', '#feedback');
        this.adjustFormForMobile();
        
        // Фокус на первом поле
        setTimeout(() => {
            document.getElementById('fullName').focus();
        }, 100);
    }

    closePopup() {
        this.popupOverlay.style.display = 'none';
        // Возвращаем предыдущее состояние
        if (history.state && history.state.popupOpen) {
            history.back();
        }
    }

    adjustFormForMobile() {
        // Автоматическая адаптация для мобильных устройств
        if (window.innerWidth <= 768) {
            const formElements = this.feedbackForm.querySelectorAll('input, textarea, button');
            formElements.forEach(element => {
                element.style.fontSize = '16px'; // Предотвращает масштабирование в iOS
            });
        }
    }

    saveFormData() {
        const formData = new FormData(this.feedbackForm);
        const data = {};
        
        for (let [key, value] of formData.entries()) {
            if (key !== 'privacyPolicy') {
                data[key] = value;
            }
        }
        
        data.privacyPolicy = document.getElementById('privacyPolicy').checked;
        
        localStorage.setItem(this.STORAGE_KEY, JSON.stringify(data));
    }

    restoreFormData() {
        const savedData = localStorage.getItem(this.STORAGE_KEY);
        if (savedData) {
            try {
                const data = JSON.parse(savedData);
                
                Object.keys(data).forEach(key => {
                    const element = document.getElementById(key);
                    if (element) {
                        if (element.type === 'checkbox') {
                            element.checked = data[key];
                        } else {
                            element.value = data[key];
                        }
                    }
                });
            } catch (error) {
                console.error('Ошибка восстановления данных:', error);
                this.clearFormData();
            }
        }
    }

    clearFormData() {
        localStorage.removeItem(this.STORAGE_KEY);
        this.feedbackForm.reset();
    }

    showMessage(message, type = 'success') {
        // Удаляем предыдущие сообщения
        const existingMessage = this.popupOverlay.querySelector('.message');
        if (existingMessage) {
            existingMessage.remove();
        }

        const messageDiv = document.createElement('div');
        messageDiv.className = `message ${type}`;
        messageDiv.textContent = message;

        this.feedbackForm.insertBefore(messageDiv, this.submitBtn);

        // Автоскрытие сообщения
        setTimeout(() => {
            if (messageDiv.parentNode) {
                messageDiv.remove();
            }
        }, 5000);
    }

    async handleSubmit(e) {
        e.preventDefault();
        
        // Валидация формы
        if (!this.feedbackForm.checkValidity()) {
            this.showMessage('Пожалуйста, заполните все обязательные поля правильно', 'error');
            return;
        }

        this.submitBtn.disabled = true;
        this.submitBtn.textContent = 'Отправка...';

        try {
            const formData = new FormData(this.feedbackForm);
            const data = Object.fromEntries(formData.entries());

            // Отправка данных на Formcarry
            const response = await fetch(this.FORMCARRY_URL, {
                method: 'POST',
                headers: {
                    'Accept': 'application/json',
                    'Content-Type': 'application/json',
                },
                body: JSON.stringify(data)
            });

            if (response.ok) {
                this.showMessage('Сообщение успешно отправлено! Мы свяжемся с вами в ближайшее время.', 'success');
                this.clearFormData();
                setTimeout(() => {
                    this.closePopup();
                }, 2000);
            } else {
                throw new Error(`Ошибка сервера: ${response.status}`);
            }

        } catch (error) {
            console.error('Ошибка отправки формы:', error);
            this.showMessage('Произошла ошибка при отправке. Пожалуйста, попробуйте еще раз или свяжитесь с нами другим способом.', 'error');
        } finally {
            this.submitBtn.disabled = false;
            this.submitBtn.textContent = 'Отправить';
        }
    }
}

// Инициализация формы при загрузке страницы
document.addEventListener('DOMContentLoaded', () => {
    new FeedbackForm();
});

// Автоматическое открытие формы если в URL есть хэш
window.addEventListener('load', () => {
    if (window.location.hash === '#feedback') {
        setTimeout(() => {
            document.querySelector('.open-form-btn').click();
        }, 100);
    }
});

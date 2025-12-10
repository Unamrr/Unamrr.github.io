/*const form = document.getElementById('feedbackForm');
const submitBtn = form.querySelector('button[type="submit"]');

form.addEventListener('submit', async (e) => {
    e.preventDefault();

    const formData = new FormData(form);
    formData.append("access_key", "2f150c45-44a5-4083-affa-81d1de06b6ee");

    const originalText = submitBtn.textContent;

    submitBtn.textContent = "Sending...";
    submitBtn.disabled = true;

    try {
        const response = await fetch("https://api.web3forms.com/submit", {
            method: "POST",
            body: formData
        });

        const data = await response.json();

        if (response.ok) {
            alert("Success! Your message has been sent.");
            form.reset();
        } else {
            alert("Error: " + data.message);
        }

    } catch (error) {
        alert("Something went wrong. Please try again.");
    } finally {
        submitBtn.textContent = originalText;
        submitBtn.disabled = false;
    }
});*/
class FeedbackForm {
    constructor() {
        this.feedbackForm = document.getElementById('feedbackForm');
        this.submitBtn = document.getElementById('submitBtn');
        this.STORAGE_KEY = 'feedbackFormData';
        this.init();
    }

    init() {
        this.restoreFormData();
        this.feedbackForm.addEventListener('submit', (e) => this.handleSubmit(e));
        this.feedbackForm.addEventListener('input', () => this.saveFormData());
    }

    saveFormData() {
        const formData = {
            name: document.getElementById('field-name-1').value,
            phone: document.getElementById('phone').value,
            email: document.getElementById('field-email').value,
            comment: document.getElementById('field-name-2').value,
            agree: document.getElementById('agree').checked
        };
        localStorage.setItem(this.STORAGE_KEY, JSON.stringify(formData));
    }

    restoreFormData() {
        const savedData = localStorage.getItem(this.STORAGE_KEY);
        if (savedData) {
            try {
                const data = JSON.parse(savedData);
                document.getElementById('field-name-1').value = data.name || '';
                document.getElementById('phone').value = data.phone || '';
                document.getElementById('field-email').value = data.email || '';
                document.getElementById('field-name-2').value = data.comment || '';
                document.getElementById('agree').checked = data.agree || false;
            } catch (error) {
                console.error('Ошибка восстановления данных:', error);
                this.clearFormData();
            }
        }
    }

    clearFormData() {
        localStorage.removeItem(this.STORAGE_KEY);
    }

    showMessage(message, type = 'success') {
        // Удаляем старое сообщение если есть
        const existingMessage = document.querySelector('.form-message');
        if (existingMessage) {
            existingMessage.remove();
        }

        const messageDiv = document.createElement('div');
        messageDiv.className = `form-message alert alert-${type === 'success' ? 'success' : 'danger'} mt-3`;
        messageDiv.textContent = message;
        
        // Вставляем сообщение после формы
        this.feedbackForm.appendChild(messageDiv);

        // Автоудаление через 5 секунд
        setTimeout(() => {
            if (messageDiv.parentNode) {
                messageDiv.remove();
            }
        }, 5000);
    }

    async handleSubmit(e) {
        e.preventDefault();
        
        // Проверяем валидность формы
        if (!this.feedbackForm.checkValidity()) {
            this.showMessage('Пожалуйста, заполните все обязательные поля правильно', 'error');
            return;
        }

        const originalText = this.submitBtn.textContent;
        this.submitBtn.disabled = true;
        this.submitBtn.textContent = 'Отправка...';

        try {
            const formData = new FormData(this.feedbackForm);
            
            // Отправка данных через Web3Forms
            const response = await fetch('https://api.web3forms.com/submit', {
                method: 'POST',
                body: formData
            });

            const result = await response.json();

            if (result.success) {
                this.showMessage('✅ Сообщение успешно отправлено! Мы свяжемся с вами в ближайшее время.', 'success');
                this.feedbackForm.reset();
                this.clearFormData();
            } else {
                throw new Error(result.message || 'Ошибка отправки формы');
            }

        } catch (error) {
            console.error('Ошибка отправки формы:', error);
            this.showMessage('❌ Произошла ошибка при отправке. Пожалуйста, попробуйте еще раз.', 'error');
        } finally {
            this.submitBtn.disabled = false;
            this.submitBtn.textContent = originalText;
        }
    }
}

// Инициализация при загрузке страницы
document.addEventListener('DOMContentLoaded', () => {
    new FeedbackForm();
});

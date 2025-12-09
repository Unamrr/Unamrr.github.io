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
        //this.popupOverlay = document.getElementById('popupOverlay');
        this.feedbackForm = document.getElementById('feedbackForm');
        //this.closeBtn = document.getElementById('closeBtn');
        this.submitBtn = document.getElementById('submitBtn');
        
        
        this.STORAGE_KEY = 'feedbackFormData';
        this.init();
    }

    init() {
        this.restoreFormData();
        
        //this.closeBtn.addEventListener('click', () => this.closePopup());
        this.feedbackForm.addEventListener('submit', (e) => this.handleSubmit(e));
        this.feedbackForm.addEventListener('input', () => this.saveFormData());
        
        window.addEventListener('popstate', (e) => {
            if (e.state && e.state.popupOpen) {
                this.closePopup();
            }
        });

        /*this.popupOverlay.addEventListener('click', (e) => {
            if (e.target === this.popupOverlay) {
                this.closePopup();
            }
        });*/

        document.addEventListener('keydown', (e) => {
            if (e.key === 'Escape' && this.popupOverlay.style.display === 'flex') {
                this.closePopup();
            }
        });
    }

    openPopup() {
        this.popupOverlay.style.display = 'flex';
        history.pushState({ popupOpen: true }, '', '#feedback');
        this.adjustFormForMobile();
        setTimeout(() => {
            document.getElementById('fullName').focus();
        }, 100);
    }

    closePopup() {
        this.popupOverlay.style.display = 'none';
        if (history.state && history.state.popupOpen) {
            history.back();
        }
    }

    adjustFormForMobile() {
        if (window.innerWidth <= 768) {
            const formElements = this.feedbackForm.querySelectorAll('input, textarea, button');
            formElements.forEach(element => {
                element.style.fontSize = '16px';
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
        const existingMessage = this.popupOverlay.querySelector('.message');
        if (existingMessage) {
            existingMessage.remove();
        }

        const messageDiv = document.createElement('div');
        messageDiv.className = `message ${type}`;
        messageDiv.textContent = message;
        this.feedbackForm.insertBefore(messageDiv, this.submitBtn);

        setTimeout(() => {
            if (messageDiv.parentNode) {
                messageDiv.remove();
            }
        }, 5000);
    }

    async handleSubmit(e) {
        e.preventDefault();
        
        /*if (!this.feedbackForm.checkValidity()) {
            this.showMessage('Пожалуйста, заполните все обязательные поля правильно', 'error');
            return;
        }*/

        this.submitBtn.disabled = true;
        this.submitBtn.textContent = 'Отправка...';

        try {
            const formData = new FormData(this.feedbackForm);
            
            const data = {
                access_key: '2f150c45-44a5-4083-affa-81d1de06b6ee',
                subject: 'Новое сообщение с формы обратной связи',
                name: formData.get('fullName'),
                email: formData.get('email'),
                phone: formData.get('phone'),
                company: formData.get('organization'),
                message: formData.get('message'),
                from_name: 'Сайт обратной связи'
            };

            const response = await fetch('https://api.web3forms.com/submit', {
                method: 'POST',
                headers: {
                    'Content-Type': 'application/json',
                },
                body: JSON.stringify(data)
            });

            const result = await response.json();
            
            if (result.success) {
                this.showMessage('✅ Сообщение успешно отправлено! Мы свяжемся с вами в ближайшее время.', 'success');
                this.clearFormData();
                setTimeout(() => {
                    this.closePopup();
                }, 2000);
            } else {
                throw new Error(result.message || 'Ошибка отправки формы');
            }

        } catch (error) {
            console.error('Ошибка отправки формы:', error);
            this.showMessage('❌ Произошла ошибка при отправке: ' + error.message, 'error');
        } finally {
            this.submitBtn.disabled = false;
            this.submitBtn.textContent = 'Отправить';
        }
    }
}

document.addEventListener('DOMContentLoaded', () => {
    new FeedbackForm();
});

window.addEventListener('load', () => {
    if (window.location.hash === '#feedback') {
        setTimeout(() => {
            document.querySelector('.open-form-btn').click();
        }, 100);
    }
});
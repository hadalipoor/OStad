document.addEventListener('DOMContentLoaded', function() {
    const apiUrl = '/elevatorsystemconfig'; 
    let configForm = document.getElementById('configForm');
    let submitBtn = document.getElementById('submitBtn');
    let resetBtn = document.getElementById('resetBtn');
    let notification = document.getElementById('notification');

    submitBtn.addEventListener('click', saveConfig);
    resetBtn.addEventListener('click', resetConfig);

    function showNotification(message) {
        notification.innerText = message;
        notification.style.display = 'block';
        setTimeout(() => {
            notification.style.display = 'none';
        }, 3000);
    }

    function saveConfig(e) {
        e.preventDefault();
        let configsArray = [];

        for (let i = 0; i < configForm.elements.length; i++) {
            let element = configForm.elements[i];
            if (element.id) {
                configsArray.push({
                    id: i + 1,
                    key: element.id,
                    value: element.value
                });
            }
        }
        update_url = `${apiUrl}/update_configs?configs={"configs":`+JSON.stringify(configsArray)+`}`;
        fetch(update_url, {
            method: 'PUT',
            headers: {
                'Content-Type': 'application/json'
            }
            // body: { configs: configsArray }
        })
        .then((response) => response.text())
        .then((response) => {
            if (response === 'Succesfull') {
                showNotification('تغییرات با موفقیت انجام شد. لطفا برای اعمال تغییرات بورد را دوباره راه اندازی کنید');
            } else {
                throw new Error(response);
            }
        })
        .catch((error) => {
            showNotification(error.message);
        });
    }

    function resetConfig() {
        fetch(`${apiUrl}/getSystemConfigs`, {
            method: 'GET',
        })
        .then((response) => response.json())
        .then((response) => {
            if (typeof response === 'object') {
                for (let key in response) {
                    let element = document.getElementById(key);
                    if (element) element.value = response[key];
                }
                showNotification('تنظیمات به حالت پیش فرض بازگشت');
            } else {
                throw new Error(response);
            }
        })
        .catch((error) => {
            showNotification(error.message);
        });
    }

    function loadConfig() {
        fetch(`${apiUrl}/getAll`, {
            method: 'GET',
        })
        .then((response) => response.json())
        .then((response) => {
            if (typeof response === 'object') {
                for (let key in response) {
                    let element = document.getElementById(response[key]["key"]);
                    if (element) element.value = response[key]["value"].toString();
                }
            } else {
                throw new Error(response);
            }
        })
        .catch((error) => {
            showNotification(error.message);
        });
    }

    loadConfig();
});

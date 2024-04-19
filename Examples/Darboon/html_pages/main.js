document.addEventListener('DOMContentLoaded', function() {
    var sidebarMenu = document.getElementById('menu');
    var sidebarToggle = document.getElementById('menu-toggle');
  
    if (sidebarMenu && sidebarToggle) {
        sidebarToggle.addEventListener('click', function(event) {
            event.stopPropagation(); // Prevent the click from being immediately captured by the document event listener
            toggleMenu('toggle');
        });
    }

    // Close the menu when clicking anywhere on the page
    document.addEventListener('click', function(event) {
        var isClickInsideMenu = sidebarMenu.contains(event.target);
        var isMenuOpen = sidebarMenu.classList.contains('open');

        if (!isClickInsideMenu && isMenuOpen) {
            toggleMenu('close'); // Close the menu if the click is outside and the menu is open
        }
    });
});

function toggleMenu(action) {
    const menu = document.getElementById('menu');
    if (action === 'toggle') {
        menu.classList.toggle('open');
    } else if (action === 'close' && menu.classList.contains('open')) {
        menu.classList.remove('open');
    } else if (action === 'open' && !menu.classList.contains('open')) {
        menu.classList.add('open');
    }
}
  // Function to show a status message to the user
function showStatusMessage(message) {
    const statusMessage = document.getElementById('statusMessage');
    statusMessage.textContent = message;
    statusMessage.style.display = 'block';

    // Hide the message after 3 seconds
    setTimeout(() => {
        statusMessage.style.display = 'none';
    }, 3000);
}

function openDoor() {
    fetch('http://192.168.4.1/tagcontroller/openDoor', { method: 'POST' })
    .then(response => {
        if (response.ok) {
            showStatusMessage('Door opened successfully');
        } else {
            showStatusMessage('Failed to open door');
        }
    })
    .catch(error => showStatusMessage('Network error: ' + error.message));
}

function toggleGardenLight() {
    fetch('http://192.168.4.1/light/gardenlight', { method: 'POST' })
    .then(response => {
        if (response.ok) {
            showStatusMessage('Garden light toggled successfully');
        } else {
            showStatusMessage('Failed to toggle garden light');
        }
    })
    .catch(error => showStatusMessage('Network error: ' + error.message));
}

function toggleYardLight() {
    fetch('http://192.168.4.1/light/yardlight', { method: 'POST' })
    .then(response => {
        if (response.ok) {
            showStatusMessage('Yard light toggled successfully');
        } else {
            showStatusMessage('Failed to toggle yard light');
        }
    })
    .catch(error => showStatusMessage('Network error: ' + error.message));
}


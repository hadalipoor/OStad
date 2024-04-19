
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

    document.getElementById('addGuestBtn').addEventListener('click', function() {
        openAddGuestForm();
    });
    
    fetchGuests();
});

// This function is now used for both adding and editing guests
function openAddGuestForm(editMode = false, guestData = {}) {
    var modal = document.getElementById("addGuestModal");
    var closeButton = document.querySelector(".close-button");
    var submitButton = document.getElementById("modalSubmitButton"); // Ensure your modal form's submit button has this ID
    var formTitle = document.getElementById("modalFormTitle"); // Ensure your modal has a title element with this ID
    
    // Clear previous data
    document.getElementById('guestName').value = editMode ? guestData.Name : "";
    document.getElementById('guestDescription').value = editMode ? guestData.Description : "";
    document.getElementById('startActiveTime').value = editMode ? guestData.StartActiveTime : "";
    document.getElementById('endActiveTime').value = editMode ? guestData.EndActiveTime : "";

    // Adjust modal for edit mode
    if (editMode) {
        formTitle.textContent = "Edit Guest";
        submitButton.textContent = "Edit Guest";
    } else {
        formTitle.textContent = "Add Guest";
        submitButton.textContent = "Add Guest";
    }

    // Handle modal open and close behaviors
    modal.style.display = "block";
    closeButton.onclick = function() {
        modal.style.display = "none";
    };
    window.onclick = function(event) {
        if (event.target == modal) {
            modal.style.display = "none";
        }
    };

    // Set a data attribute on the form for the guest ID if in edit mode
    document.getElementById('addGuestForm').setAttribute("data-guest-id", editMode ? guestData.id : "");
}

document.getElementById('addGuestForm').addEventListener('submit', function(e) {
    e.preventDefault();

    // Check if we are in add or edit mode
    const isEditMode = this.hasAttribute("data-guest-id") && this.getAttribute("data-guest-id") !== "";
    const guestId = this.getAttribute("data-guest-id");

    const name = document.getElementById('guestName').value;
    const description = document.getElementById('guestDescription').value;
    const startActiveTime = document.getElementById('startActiveTime').value;
    const endActiveTime = document.getElementById('endActiveTime').value;

    let apiUrl;
    let method;

    if (isEditMode) {
        // Construct the API URL for updating
        apiUrl = `http://192.168.4.1/guests/update?Name=${encodeURIComponent(name)}&Description=${encodeURIComponent(description)}&UId=${encodeURIComponent(guestId)}&Active=SAMPLE&StartActiveTime=&EndActiveTime=&id=${encodeURIComponent(guestId)}`;
        method = 'PUT'; // Assuming your API requires PUT for updates
    } else {
        // Construct the API URL for adding
        apiUrl = `http://192.168.4.1/tagcontroller/addGuest?name=${encodeURIComponent(name)}&description=${encodeURIComponent(description)}&start_active_time=${encodeURIComponent(startActiveTime)}&end_active_time=${encodeURIComponent(endActiveTime)}`;
        method = 'POST';
    }

    fetch(apiUrl, {
        method: method,
        headers: {
            'Content-Type': 'application/json',
        },
    })
    .then(response => response)
    .then(data => {
        console.log('Success:', data);
        document.getElementById("addGuestModal").style.display = "none";
        fetchGuests(); // Refresh the guest list
    })
    .catch((error) => {
        console.error('Error:', error);
    });
});

function editGuest(id) {
    // Construct the URL for fetching guest data by ID
    const url = `http://192.168.4.1/guests/getById?id=${id}`;

    // Use fetch API to request guest data
    fetch(url)
    .then(response => {
        if (!response.ok) {
            throw new Error('Network response was not ok');
        }
        return response.json();
    })
    .then(data => {
        // Assuming the response data is the guest data object directly
        // If the structure is different, adjust the access accordingly
        if (data) {
            // const guestData = data[0]; // Assuming the data comes as an array with the guest object as the first item
            openAddGuestForm(true, data);
        } else {
            throw new Error('Guest data not found');
        }
    })
    .catch(error => {
        console.error('Error fetching guest data:', error);
    });
}


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
function fetchGuests() {
    fetch('http://192.168.4.1/guests/getAll')
        .then(response => response.json())
        .then(data => displayGuests(data))
        .catch(error => console.error('Error fetching guests:', error));
}

function displayGuests(guests) {
    const guestList = document.querySelector('.guest-list');
    guestList.innerHTML = ''; // Clear current guests

    guests.forEach(guest => {
        const guestItem = document.createElement('div');
        guestItem.className = 'guest-item';
        guestItem.innerHTML = `
            <div class="guest-info">
                <strong>Name:</strong> ${guest.Name}<br>
                <strong>Description:</strong> ${guest.Description}<br>
                <strong>UID:</strong> ${guest.UId}
            </div>
            <div class="guest-details">
                <span class="guest-active-status">${guest.Active == '1' ? 'Active' : 'Inactive'}</span><br>
                <strong>Start:</strong> ${guest.StartActiveTime}<br>
                <strong>End:</strong> ${guest.EndActiveTime}
            </div>
            <div class="guest-actions">
                <button onclick="editGuest(${guest.id})">Edit</button>
                <button onclick="deleteGuest(${guest.id})">Delete</button>
            </div>
        `;
        guestList.appendChild(guestItem);
    });
}



function deleteGuest(id) {
    if (confirm('Are you sure you want to delete this guest?')) {
        // Perform fetch DELETE request to backend
        console.log(`Deleting guest with ID: ${id}`);
        fetchDeleteGuest(id);
    }
}

function fetchDeleteGuest(id) {
    // Construct the URL with the guest ID
    const url = `http://192.168.4.1/guests/delete?id=${id}`;

    fetch(url, {
        method: 'DELETE', // Specify the method to use
    })
    .then(response => {
        if (!response.ok) {
            // If the server response was not ok, throw an error
            throw new Error('Network response was not ok');
        }
        return response.body; // Parse the JSON response body
    })
    .then(data => {
        console.log('Guest deleted successfully:', data);
        // Optionally, refresh the guest list to reflect the deletion
        fetchGuests();
    })
    .catch(error => {
        console.error('Error deleting guest:', error);
    });
}


// Additional implementations for showModal(), showEditModal(id), fetchDeleteGuest(id), etc., go here

function fetchTankerCapacity() {
    fetch('http://192.168.4.1/tanker/get_capacity')
        .then(response => response.json())
        .then(data => {
            const capacity = data;
            const capacityElement = document.getElementById('capacity');
            const tankerElement = document.getElementById('tanker');

            capacityElement.textContent = `Capacity: ${capacity}`;

            if (capacity < 15) {
                // Tanker is full
                tankerElement.style.backgroundColor = '#4CAF50'; // Green
            } else if (capacity >= 250) {
                // Tanker is empty
                tankerElement.style.backgroundColor = '#FFFFFF'; // White
            } else {
                // Intermediate values
                const percentageFull = 100 - ((capacity - 15) / (250 - 15)) * 100;
                const colorIntensity = Math.floor((255 * percentageFull) / 100);
                tankerElement.style.backgroundColor = `rgb(${colorIntensity}, ${255 - colorIntensity}, 0)`; // Gradient from green to red based on fill level
            }
        })
        .catch(error => {
            console.error('Error fetching tanker capacity:', error);
        });
}

// Fetch capacity every 2 seconds
setInterval(fetchTankerCapacity, 2000);

// Initial fetch
fetchTankerCapacity();

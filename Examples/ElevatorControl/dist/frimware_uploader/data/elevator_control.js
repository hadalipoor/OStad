// Global state to check if API response is being shown
const serverUrl = "";
let apiResponseShowing = false;

// Fetching elevator configuration
fetch(`${serverUrl}/elevatorsystemconfig/getAll`)
    .then(response => response.json())
    .then(data => {
        // Filter the data to get the number of floors
        const floorConfig = data.find(config => config.key === 'number_of_floors');
        if (floorConfig) {
            const numberOfFloors = Number(floorConfig.value);
            const floorControlSection = document.getElementById('floorControlSection');
            
            for(let i = 1; i <= numberOfFloors; i++) {
                const button = document.createElement('button');
                button.textContent = `طبقه ${i}`;
                button.className = 'floorButton';
                button.onclick = () => floorRequested(i);
                floorControlSection.appendChild(button);
            }
        }
    });

// Request elevator state every second
setInterval(() => {
    if (!apiResponseShowing) {
        fetch(`${serverUrl}/elevatorcontrol/getState`)
            .then(response => response.text())
            .then(data => {
                document.getElementById('lcdDisplay').textContent = data;
            });
    }
}, 1000);

function floorRequested(floor) {
    apiResponseShowing = true;
    fetch(`${serverUrl}/elevatorcontrol/floorRequested?floor=${floor}`)
        .then(response => response.text())
        .then(data => {
            document.getElementById('lcdDisplay').textContent = data;
            // Wait for 3 seconds before showing the getState result
            setTimeout(() => { apiResponseShowing = false; }, 3000);
        });
}

function calibrationRequested() {
    apiResponseShowing = true;
    fetch(`${serverUrl}/elevatorcontrol/calibrationRequested`)
        .then(response => response.text())
        .then(data => {
            document.getElementById('lcdDisplay').textContent = data;
            // Wait for 3 seconds before showing the getState result
            setTimeout(() => { apiResponseShowing = false; }, 3000);
        });
}

function emsStopRequested() {
    apiResponseShowing = true;
    fetch(`${serverUrl}/elevatorcontrol/eMSStopRequested`)
        .then(response => response.text())
        .then(data => {
            document.getElementById('lcdDisplay').textContent = data;
            // Wait for 3 seconds before showing the getState result
            setTimeout(() => { apiResponseShowing = false; }, 3000);
        });
}


    // Uppdatera klockan varje sekund
    function updateClock() {
      const now = new Date();
      const hours = String(now.getHours()).padStart(2, '0');
      const minutes = String(now.getMinutes()).padStart(2, '0');
      const seconds = String(now.getSeconds()).padStart(2, '0');
      document.getElementById('clock').innerText = hours + ':' + minutes + ':' + seconds;
    }
    setInterval(updateClock, 1000);
    updateClock();

    // Klickfunktion för att visa/dölja detaljer
    function toggleDetails() {
      const details = document.getElementById('details');
      const arrow = document.getElementById('arrow')
      if (details.style.display === 'none') {
        details.style.display = 'block';
        arrow.innerText = '⬆';
      } else {
        details.style.display = 'none';
        arrow.innerText = '⬇';
      }
    }

    // Uppdatera sensorvärden
    async function update() {
      const res = await fetch("/sensor");
      const data = await res.json();
      if (!data.error) {
        document.getElementById("temp").innerText = "Temperature: " + data.temperature + " °C";
        document.getElementById("hum").innerText = "Humidity: " + data.humidity + " %";

        // Här kan du sätta max/min värden
        // Exempel:
        document.getElementById("maxTemp").innerText = "Max Temp: " + data.maxTemp + " °C";
        document.getElementById("minTemp").innerText = "Min Temp: " + data.minTemp + " °C";
      }
    }

    setInterval(update, 2000);
    update();

let time = document.getElementById("time");
let timeout = document.getElementById("timeout");

let clockBtn = document.getElementById("clockBtn");
clockBtn.addEventListener('click', setTimer);

let timeValue = 0;
let refreshInterval = 0;
function setTimer()
{
    clearInterval(refreshInterval);

    timeValue = parseInt(time.value);
    printTimer(timeValue);

    refreshInterval = setInterval(deacreaseTimer, 1000);
}

function deacreaseTimer()
{
    timeValue--;
    printTimer(timeValue);

    if (timeValue == 0)
    {
        clearInterval(refreshInterval);
        timeout.innerHTML = "Time to wake up!";
    }
}

let days = document.getElementById("days");
let hours = document.getElementById("hours");
let minutes = document.getElementById("minutes");
let seconds = document.getElementById("seconds");

function printTimer(n)
{
    let day = 0;
    let hour = 0;
    let minute = 0;
    let seconde = 0;

    let value = 0;
    let timeValue = n;

    seconde = timeValue % 60;
    value = Math.floor(timeValue / 60);

    minute = value % 60;
    value = Math.floor(timeValue / 3600);

    hour = value % 24;
    value = Math.floor(timeValue / 3600 / 24);

    day = value;

    let secondeStr = seconde.toString();
    let minuteStr = minute.toString();
    let hourStr = hour.toString();
    let dayStr = day.toString();

    if (secondeStr.length == 1)
        secondeStr = "0" + secondeStr;

    if (minuteStr.length == 1)
        minuteStr = "0" + minuteStr;

    if (hourStr.length == 1)
        hourStr = "0" + hourStr;

    if (dayStr.length == 1)
        dayStr = "0" + dayStr;

    seconds.innerHTML = secondeStr;
    minutes.innerHTML = minuteStr;
    hours.innerHTML = hourStr;
    days.innerHTML = dayStr;
}

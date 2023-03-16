var xValues = [0];
var yValues = [0];
var rand = Math.random();
var time = 0;
var energy = 0;
var winddir = 0;
function rpm() {
  rand = Math.random();
  var rpm = rand * 10 + 40;
  document.querySelector(".rpmval").innerHTML = Math.trunc(rpm);
  //   console.log(rpm | 0);
}
function wspeed() {
  var wspd = rand * 10 + 10;
  document.querySelector(".windspeed").innerHTML = Math.trunc(wspd);
  //   console.log(wspd | 0);
}
function wdir() {
  var wdir = rand * 360;
  document.querySelector(".windDir").innerHTML = Math.trunc(wdir);
  document.querySelector(".pointer").style.transform =
    "rotate(" + wdir + "deg)";
  // document.querySelector(".pointer").style.transform = "rotate(50deg)";
}
var brakestatus = 1; //1 is on 0 false
function powergen() {
  var power = rand * 250 + 0;

  document.querySelector(".powerdata").innerHTML = Math.trunc(power);
  if (xValues.length > 20) {
    xValues.shift();
    yValues.shift();
  }
  xValues.push(getFormattedDate());
  yValues.push(power | 0);
  energy += (power * 1000) / 1000;
  document.querySelector(".energytotal").innerHTML = energy | 0;
  new Chart("myChart", {
    type: "line",
    data: {
      labels: xValues,
      datasets: [
        {
          fill: false,
          lineTension: 0.5,
          backgroundColor: "rgba(0,0,255,1.0)",
          borderColor: "rgba(0,0,255,0.1)",
          data: yValues,
        },
      ],
    },
    options: {
      legend: { display: false },
      scales: {
        yAxes: [{ ticks: { min: 0, max: 260 } }],
      },
      bezierCurve: true,
      animation: true,
      //Boolean - If we want to override with a hard coded scale
      scaleOverride: true,
      //** Required if scaleOverride is true **
      //Number - The number of steps in a hard coded scale
      scaleSteps: 10,
      //Number - The value jump in the hard coded scale
      scaleStepWidth: 10,
      //Number - The scale starting value
      scaleStartValue: 0,
    },
  });
  //   console.log(power | 0);
  // console.log(xValues,yValues);
}
setInterval(rpm, 1000);
setInterval(wspeed, 1000);
setInterval(powergen, 1000);
setInterval(wdir, 1000);

function getFormattedDate() {
  let currentDate = new Date();
  return (
    currentDate.getHours() +
    ":" +
    currentDate.getMinutes() +
    ":" +
    currentDate.getSeconds()
  );
}

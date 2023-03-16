var xValues = [];
var yValues = [];
var time = 0;
var energy = 0;
var winddir = 0;
var wspd = 0;
var rand;

function wspeed() {
  rand = Math.random();
  wspd = rand * 20 + 5;
  document.querySelector(".windspeed").innerHTML = Math.trunc(wspd);
  //   console.log(wspd | 0);
}
function wdir() {
  var wdir = Math.random() * 360;
  document.querySelector(".windDir").innerHTML = Math.trunc(wdir);
  document.querySelector(".pointer").style.transform =
    "rotate(" + wdir + "deg)";
  // document.querySelector(".pointer").style.transform = "rotate(50deg)";
}
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
var dataPointsCounter = 0;
function addData(chart, label, data) {
  // console.log(chart.data.labels);
  // chart.data.datasets.forEach(dataset => {
  //   dataset.data.push(data);
  // });
  yValues.push(data);
  chart.data.labels.push(label);
  dataPointsCounter++;
  if (dataPointsCounter > 10) {
    const diff =
      chart.scales.x.getPixelForValue(
        chart.data.labels[dataPointsCounter - 11]
      ) -
      chart.scales.x.getPixelForValue(
        chart.data.labels[dataPointsCounter - 10]
      );
    console.log(diff, chart.scales);
    chart.pan(
      {
        x: diff - 0.1 * diff,
      },
      undefined,
      "default"
    );
  }
  chart.update();
}

function removeData(chart) {
  chart.data.labels.pop();
  chart.data.datasets.forEach(dataset => {
    dataset.data.pop();
  });
  chart.update();
}
var myChart;
const zoomOptions = {
  pan: {
    enabled: true,
    modifierKey: "ctrl",
  },
  zoom: {
    drag: {
      enabled: true,
    },
    wheel: {
      enabled: true,
    },
    mode: "x",
    onZoom: function () {
      self.onZoomChange();
    },
  },
};
// </block>

const panStatus = () => (zoomOptions.pan.enabled ? "enabled" : "disabled");
const zoomStatus = () =>
  zoomOptions.zoom.drag.enabled ? "enabled" : "disabled";

const scales = {
  x: {
    position: "bottom",
    type: "time",
    ticks: {
      autoSkip: true,
      autoSkipPadding: 50,
      maxRotation: 0,
    },
    time: {
      displayFormats: {
        hour: "HH:mm",
        minute: "HH:mm",
        second: "HH:mm:ss",
      },
    },
  },
  y: {
    position: "right",
    ticks: {
      callback: (val, index, ticks) =>
        index === 0 || index === ticks.length - 1 ? null : val,
    },
    grid: {
      // borderColor: Utils.randomColor(1),
      color: "rgba( 0, 0, 0, 0.1)",
    },
    title: {
      display: true,
      text: ctx => ctx.scale.axis + " axis",
    },
  },
};

var mom = moment();
const sc = {
  x: {
    position: "bottom",
    type: "timeseries",
    ticks: {
      autoSkip: true,
      autoSkipPadding: 50,
      maxRotation: 0,
      major: {
        enabled: true,
      },
      maxTicksLimit: 10,
      align: "end",
    },
    min: "13:20:45",

    time: {
      unit: "second", // <-- that does the trick here
      displayFormats: {
        hour: "HH:mm",
        minute: "HH:mm",
        second: "HH:mm:ss",
        day: "DD:MM:YY",
        month: "MM:YY",
      },
      // unitStepSize: 1,
      tooltipFormat: "hh:mm:ss",

      // tooltipFormat: "D-M-Y H:00:00", // <-- same format for tooltip
    },
  },
  y: {
    min: 0,
    max: 40,
  },
};

function wsgraph() {
  if (myChart == undefined) {
    myChart = new Chart("myChart", {
      type: "scatter",
      responsive: "true",
      data: {
        labels: xValues,
        datasets: [
          {
            label: "wind speed",
            fill: false,
            lineTension: 0.5,
            backgroundColor: "rgba(0,0,255,1.0)",
            borderColor: "rgba(0,0,255,0.1)",
            data: yValues,
            showLine: true,
          },
        ],
      },
      options: {
        // scales: {
        //   yAxes: [{ ticks: { min: 0, max: 260 } }],
        // },
        scales: sc,
        plugins: {
          zoom: zoomOptions,

          title: {
            display: true,
            position: "bottom",
            text: ctx => "Zoom: " + zoomStatus() + ", Pan: " + panStatus(),
          },
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
  }
  tmp = moment();
  // console.log(mom, mom.format("DD:MM:YYYY:hh:mm:ss"));
  addData(myChart, tmp, wspd);
  // document.querySelector(".powerdata").innerHTML = Math.trunc(wspd);
  // if (xValues.length > 20) {
  //   xValues.shift();
  //   yValues.shift();
  // }
  // xValues.push(getFormattedDate());
  // yValues.push(wspd | 0);
  // console.log(yValues, xValues);
  //   energy +='; (power * 1000) / 1000;
  //   document.querySelector(".energytotal").innerHTML = energy | 0;

  //   console.log(power | 0);
  // console.log(xValues,yValues);
}

function windgraph() {
  if (myChart != undefined) myChart.destroy();
  // document.querySelector(".powerdata").innerHTML = Math.trunc(wspd);
  if (xValues.length > 20) {
    xValues.shift();
    yValues.shift();
  }
  xValues.push(getFormattedDate());
  yValues.push(wspd | 0);
  // console.log(yValues, xValues);
  //   energy +='; (power * 1000) / 1000;
  //   document.querySelector(".energytotal").innerHTML = energy | 0;
  myChart = new Chart("myChart", {
    type: "line",
    data: {
      labels: xValues,
      datasets: [
        {
          label: "wind speed",
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
resetZoomBtn = chart => {
  chart.resetZoom();
};
function onZoomChange() {
  console.log("min: ", myChart.scales);
  console.log("max: ", myChart.scales);
  console.log(this);
}
setInterval(wspeed, 1000);
setInterval(wdir, 1000);
setInterval(wsgraph, 1000);

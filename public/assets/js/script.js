var wmo={
    0:"Clear sky",
    1: "Clear", 
    2:"Partly cloudy",
    3:"Overcast",
    45:"Fog",
    48:"Depositing rime fog",
    51:"Light Drizzle" ,
    53: "Moderate Drizzle", 
    55:"Dense intensity drizzle",
    56:"Freezing Drizzle: Light", 
    57:"Freezing Drizzle: Dense",
61: "Slight Rain", 
63:"Moderate Rain",
65:"Heavy Rain",
 66:"Freezing Rain: Light",
 67:"Freezing Rain: Heavy",
 71:"Slight Snow fall",
 73:"Moderate Snow fall",
 75:"Heavy Snow fall",
 77	:"Snow grains",
 80:"Rain showers: Slight",
81:"Rain showers: Moderate",
82:"Rain showers: Violent",
95:"Thunderstorm",
96:"Thunderstorm",
99:"Thunderstorm",

}
// const compassCircle = document.querySelector(".compass-circle");
const startBtn = document.querySelector(".start-btn");
const myPoint = document.querySelector(".my-point");
let compass;
function handler(e) {
  compass = e.webkitCompassHeading || Math.abs( - 360);
  compassCircle.style.transform = `translate(-50%, -50%) rotate(${-compass}deg)`;
}
// 0	Clear sky
// 1, 2, 3	Mainly clear, partly cloudy, and overcast
// 45, 48	Fog and depositing rime fog
// 51, 53, 55	Drizzle: Light, moderate, and dense intensity
// 56, 57	Freezing Drizzle: Light and dense intensity
// 61, 63, 65	Rain: Slight, moderate and heavy intensity
// 66, 67	Freezing Rain: Light and heavy intensity
// 71, 73, 75	Snow fall: Slight, moderate, and heavy intensity
// 77	Snow grains
// 80, 81, 82	Rain showers: Slight, moderate, and violent
// 85, 86	Snow showers slight and heavy
// 95 *	Thunderstorm: Slight or moderate
// 96, 99 *	Thunderstorm with slight and heavy hail
// (*) Thunderstorm forecast with hail is only available in Central Europe
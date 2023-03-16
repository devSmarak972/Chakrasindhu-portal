const express = require("express");
const app = express();
const http = require("http");
const server = http.createServer(app);

const { Server } = require("socket.io");
const io = new Server(server);
// const Readline = require("@serialport/parser-readline");
const { PythonShell } = require("python-shell");
const moment = require("moment");
var time = moment().toArray();

let options = {
  // mode: "text",
  pythonPath: "pyscript/penv/Scripts/python.exe",
  pythonOptions: ["-u"], // get print results in real-time
  // scriptPath: "pyscripts",
  args: ["17-03-2023"],
};

setInterval(() => {
  // console.log(time);
  var d = moment().diff(moment(time), "days");
  // console.log(d);
  // d = 0;
  if (d > 0) {
    time = moment().toArray();

    options.args = [moment().format("DD-MM-YYYY-hh-mm-ss")];
    PythonShell.run("pyscript/pyscript.py", options).then(messages => {
      console.log("finished", messages);
    });
  }
}, 84600 * 1000);
const { SerialPort } = require("serialport");
// const port = new SerialPort({
//   path: "COM4",
//   baudRate: 9600,
// });
// const parser = port.pipe(new Readline({ delimiter: "\n" }));
// Read the port data

app.use(express.static(__dirname + "/public/"));

app.get("/wind/", (req, res) => {
  res.sendFile(__dirname + "\\public\\wind.html");
});

server.listen(8080, () => {
  console.log("listening on *:8080");
});
console.log(
  "Web Server Started go to 'http://localhost:8080' in your Browser."
);
// port.on("open", function () {
//   console.log("-- Connection opened --");
// });
io.on("connection", socket => {
  // socket.emit("stopbrake", { value: 0 });
});

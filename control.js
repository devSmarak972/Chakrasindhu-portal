const express = require("express");
const app = express();
const http = require("http");
const server = http.createServer(app);

const { Server } = require("socket.io");
const io = new Server(server);
// const Readline = require("@serialport/parser-readline");

const { SerialPort } = require("serialport");
const port = new SerialPort({
  path: "COM4",
  baudRate: 9600,
});
// const parser = port.pipe(new Readline({ delimiter: "\n" }));
// Read the port data
port.on("open", function () {
  console.log("-- Connection opened --");
  port.on("data", function (data) {
    // console.log("Data received: " + data, typeof data);
    console.log("Data received: \n");
    // data.substring(data.indexOf("\n")

    var dstr = data.toString();
    if (dstr.includes("brakeapplied") || dstr.includes("brakestopped")) {
      var dstr = dstr.substring(dstr.indexOf("\n") + 1);
      var cmd = dstr.substring(0, dstr.indexOf(":"));
      var rpm = dstr.substring(dstr.indexOf(":") + 1, dstr.indexOf(","));
      var counter = dstr.substring(dstr.indexOf(":") + 1);
      console.log(cmd, ":", rpm, ":", counter, ":");
      if (dstr == "brakeapplied") socket.emit("applybrake", { value: 1 });
      else if (dstr == "brakestopped") socket.emit("stopbrake", { value: 0 });
      else console.log("invalid string");
    } else {
      console.log("data ", dstr);
    }
  });
});

app.use(express.static(__dirname + "/public/"));

app.get("/", (req, res) => {
  res.sendFile(__dirname + "/public/chakra-sindhu.html");
});

server.listen(8080, () => {
  console.log("listening on *:8080");
});
console.log(
  "Web Server Started go to 'http://localhost:8080' in your Browser."
);

io.on("connection", socket => {
  socket.on("applybrake", function (data) {
    var brake = data.value;
    var buf = new Buffer.alloc(1);
    buf.writeUInt8(brake, 0);
    port.write("1");
    console.log("applybrake", brake);
    port.on("available", function (data) {
      console.log("Data:", data.toString("utf8"));
    });
    // io.sockets.emit("applybrake", { value: brake });
  });
  socket.on("stopbrake", function (data) {
    var brake = data.value;
    var buf = new Buffer.alloc(1);
    buf.writeUInt8(brake, 0);
    port.write("0");
    console.log("stopbrake", brake);

    // io.sockets.emit("stopbrake", { value: brake });
  });
  socket.emit("stopbrake", { value: 0 });
});

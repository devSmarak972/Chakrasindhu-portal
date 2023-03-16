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

app.use(express.static(__dirname + "/public/"));

app.get("/wind/", (req, res) => {
  res.send("GET Request Called");
});

server.listen(8080, () => {
  console.log("listening on *:8080");
});
console.log(
  "Web Server Started go to 'http://localhost:8080' in your Browser."
);
port.on("open", function () {
  console.log("-- Connection opened --");
});
io.on("connection", socket => {
  socket.on("applybrake", function (data) {
    console.log("applybrake", brake);
    var brake = data.value;
    var buf = new Buffer.alloc(1);
    buf.writeUInt8(brake, 0);
    port.write("1");
    io.sockets.emit("applybrake", { value: brake });
  });
  socket.on("stopbrake", function (data) {
    console.log("stopbrake", brake);
    var brake = data.value;
    var buf = new Buffer.alloc(1);
    buf.writeUInt8(brake, 0);
    port.write("0");

    io.sockets.emit("stopbrake", { value: brake });
  });

  // socket.emit("stopbrake", { value: 0 });

  port.on("data", function (data) {
    // console.log("Data received: " + data, typeof data);
    console.log("Data received: \n");
    // data.substring(data.indexOf("\n")

    var dstr = data.toString();
    console.log(dstr);
    if (dstr.includes("1") || dstr.includes("0")) {
      // var str = dstr.substring(dstr.indexOf("<") + 1, dstr.indexOf(">"));
      // console.log(str);
      // var cmd = dstr.substring(0, dstr.indexOf(":"));
      // var rpm = dstr.substring(dstr.indexOf(":") + 1, dstr.indexOf(","));
      // var counter = dstr.substring(dstr.indexOf(":") + 1);
      // console.log(cmd, ":", rpm, ":", counter, ":");
      if (dstr.includes("0")) {
        io.sockets.emit("stopbrake", { value: 0 });
        console.log("stop");
      } else if (dstr.includes("1")) {
        io.sockets.emit("applybrake", { value: 1 });
        console.log("appluy");
      } else console.log("invalid string");
    } else {
      console.log("data ", dstr);
    }
  });
});

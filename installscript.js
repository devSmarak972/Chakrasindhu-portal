let { PythonShell } = require("python-shell");
var package_name = "pytube";
let options = {
  args: [package_name],
};
PythonShell.run("./pyscript/install.py", options, function (err, results) {
  if (err) throw err;
  else console.log(results);
});

var fs = require('fs');
function getFile(){
  var fileName = process.argv[3];
  var res = fs.readFileSync(fileName);
  return res;
}


var http = require('http');
var port = process.argv[2];
var server = http.createServer(function (req, res) {
  res.end(getFile()); 
})


server.listen(port)






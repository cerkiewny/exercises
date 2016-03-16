var http = require('http')
var fs = require('fs')
var map = require('through2-map');
var server = http.createServer(function (req, res) {
  req.pipe(map(function(chunk){return chunk.toString().toUpperCase();})).pipe(res);
  res.end('<html><body><div style="background-color: red;">AAAAA!!!</div></body></html>');
})

server.listen(Number(process.argv[2]))

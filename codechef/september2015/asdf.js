var http = require('http');

function processa(response){
  response.setEncoding('utf-8');
  console.log("Got response "+response.statusCode);
  response.on("data",function(data){
    console.log(data);
  });
};
var url = process.argv[2];
http.get(url,processa);

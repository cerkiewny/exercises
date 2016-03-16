var http = require('http');
var adr = process.argv[2];
var finished = 0;
var results = [];

http.get(adr, function(res)
    {
      var alldata = '';
      res.on("data", function(data){
        alldata += data.toString();
      });
      res.on("end", function(){
        finished++;
        results[0] = alldata;
        alldata = '';
      });
    })




adr = process.argv[3];
http.get(adr, function(res)
    {
      var alldata = '';
      res.on("data", function(data){
        alldata += data.toString();
      });
      res.on("end", function(){
        finished++;
        results[1] = alldata;
        alldata = '';
      });
    })


adr = process.argv[4];
http.get(adr, function(res)
    {
      var alldata = '';
      res.on("data", function(data){
        alldata += data.toString();
      });
      res.on("end", function(){
        finished++;
        results[2] = alldata;
        alldata = '';
      });
    })


function wypisz(results, inter, finished){
  if(finished == 3){
    for(var i = 0; i < 3; i++){
      console.log(results[i]);
    }
    clearInterval(inter);
  }
}

var inter = setInterval(function(){wypisz(results, inter, finished);}, 30)

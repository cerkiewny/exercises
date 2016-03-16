
function getCurDate(){
  var dt = new Date();
  var res = dt.getFullYear() + '-';
  res += ('0' + (dt.getMonth() + 1)).slice(-2);
  res += '-' + ('0' + dt.getDate()).slice(-2) + ' ';
  res += ('0' + dt.getHours()).slice(-2) + ":";
  res += ('0' + dt.getMinutes()).slice(-2) + '\n';
  
  return res;
}

var net = require('net');
var port = process.argv[2];
var server = net.createServer(function (c) {
  
  c.on('data', function(data) {
    console.log(data.toString());
  }); 
  console.log('client connected');
  c.on('error', function() {
    console.log('error');
  }); 
  c.on('end', function() {
    console.log('client disconnected');
  }); 
  var res = getCurDate();
  c.write(res);
  c.close()
})


server.listen(port)






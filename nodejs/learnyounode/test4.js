function print(err, data){
  data.forEach(function(a){console.log(a)})
}

var mod = require('./mod.js');


mod(process.argv[2], process.argv[3] , print);






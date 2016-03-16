
function countNL(err, data){
  var counter = 0;
  var index = 0;
  var text = data.toString();
  while(index < text.length){
    if(text[index] == '\n'){
      counter ++;
    }
    index++;
  }
  console.log(counter);
}


var fs = require('fs');
var name = process.argv[2];

fs.readFile(name, countNL)





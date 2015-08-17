



var a = process.argv.length;
var sum = 0;
for(var i = 2; i < a; i ++){
  sum += parseInt(process.argv[i]);
}
console.log(sum);

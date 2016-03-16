

var res = 0;
for(var ctr = 2; ctr < process.argv.length; ctr++){
  res = res + Number(process.argv[ctr]);
}
console.log(res);


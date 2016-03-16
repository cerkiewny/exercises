



module.exports = function(dir, ext, call){
    var fs = require('fs');
    fs.readdir(dir, function(err, list){
      if(err){
       return  call(err);
      }
      var data = [];
      for(var i = 0; i < list.length; i++ ){
          if(list[i].indexOf(ext) == list[i].length - ext.length && list[i].indexOf(ext) > 0){
            data.push(list[i]);
          }
        }
      call(undefined, data);
      
    });
  }















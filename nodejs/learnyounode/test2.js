var http = require('http');
var responses = {"length": 0};


var counter = 0;

function callback(res, i) {
    res.setEncoding('utf8');

    var str = '';

    res.on('data', function (chunk) {
      str += chunk;
    });

    res.on('end', function () {
      responses[i] = str;    // Here, I want to save the full response text keyed by the url, but 
      responses.length++;         // I don't know how to retrieve the url
      if (responses.length == 3) {
        for (var j = 0; j < 3; ++j) {
          console.log(responses[j])  // Here it looks up the correct response for a given url
        }
      }
    });
  }



function myhttp(i) {
    http.get(process.argv[i], function(res){callback(res, i - 2);}).on('error', function(err) {
            console.error("Got error: " + err.message);
    });
}

for (var j = 2; j < 5; ++j) {
  myhttp(j);
}

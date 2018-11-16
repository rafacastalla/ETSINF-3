var http = require('http');
var fs = require('fs');
var path = require('path');
http.createServer(function(request,response){
	console.log('solicitud http');
	//response.writeHead(200, {'Content-Type': 'text/plain'});
	//response.end('Hello World\n');
	//var url = "/home/ruben/Download/upv.html";
  var url = path.join(__dirname,request.url);
  console.log(url);
  return function(response) {
		console.log('readFile '+url);
    fs.readFile(url,function(error,content){
		if(error){
			response.writeHead(404);
			//response.write('not found');
			response.end('not found');
		}else{
			//path.join(__dirname,request.url);
			response.writeHead(200, {'Content-Type': 'text/plain'});
			response.write(content);
			response.end('Hello World\n');
		}
	});
  }


	//path.join(__dirname,request.url);
}).listen(1337,"127.0.0.1");
console.log('Server running at http://127.0.0.1:1337/');

var http = require('http');
var url = require('url');
var qs = require('querystring');
http.createServer( function(request,response) {
	var query = url.parse(request.url).query;
	var info = qs.parse(query).info;
	var x = 'equis';
	var y = 'y griega';
	response.writeHead(200, {'Content-Type':'text/plain'});
	switch( info ) {
		case 'x': response.end('Value = ' + x); break;
		case 'y': response.end('Value = ' + y); break;
	}
}).listen('1337');

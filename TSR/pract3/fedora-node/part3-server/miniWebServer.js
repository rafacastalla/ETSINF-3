//
// miniWebServer.js
//

// Common section
var fs    = require('fs');
var path  = require('path');

// Web section
var http  = require('http');
var url   = require('url');
var PORT  = 8000;
var ADDR  = '0.0.0.0';
var PREFIX = path.dirname(__filename) + "/public/";

// Image section
var image_basedir = path.dirname(__filename) + "/fonts/";
var Rotulo = require('./theImageFactory');

//{valid_url:{path_from_PREFIX, mime}}
var contents={
  '/':{path:'formulario_rotulo.html', mime:'text/html'},
  '/index.html':{path:'formulario_rotulo.html', mime:'text/html'},
  '/formulario_rotulo.html':{path:'formulario_rotulo.html', mime:'text/html'},
  '/css/tsr.css':{path:'css/tsr.css', mime:'text/css'}
//  '/process':{path:'css/cover.css', mime:'text/css'}
};

http.createServer(function(req, res) {
  var request = url.parse(req.url, true);
  var action  = request.pathname;
  
  if (contents[action]){ // not undefined
    fs.readFile(PREFIX+contents[action].path,
      function (err, data) {
        res.writeHead(200, {'Content-Type': contents[action].mime,'Content-Length':data.length});
        res.end(data);
    })
  } else {
	  if (action == '/process') {
		  var form = request.query;
		Rotulo.Label(form.texto, form.fuente, form.tam, form.color,
        function(err, rot){
          if (!err)  { // not undefined
              res.writeHead(200, {'Content-Type': 'image/png'});
		          res.end(rot.image, 'binary');
	        }
          else { // incorrect user data || internal error
		         res.writeHead(404, {'Content-Type': 'text/plain'});
	     	     res.end("404 Not found");
        }});}
	  else { // incorrect url
		  res.writeHead(404, {'Content-Type': 'text/plain'});
		  res.end("404 Not found");
	  }
  };
}).listen(PORT,ADDR);

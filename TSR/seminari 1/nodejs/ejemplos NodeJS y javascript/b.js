/*
var http = require("http")
var fs   = require("fs")
var path = require("path")

http.createServer( function(req, resp) {
   var f = path.join("c:\\tmp\\", req.url)
   var txt = fs.readFileSync(f)
   console.log('request ',f)
   resp.writeHead(200, {'Content-Type': 'text/plain'});
   resp.end(txt)
}).listen(8000)
*/

var http = require("http")
var fs   = require("fs")
var path = require("path")

http.createServer( function(req, resp) {
   var f= path.join("c:\\tmp\\",req.url)
   console.log('request',f)
   fs.readFile(f, 
     function (err,data) {
       if (err){
         resp.writeHead(404, {'Content-Type': 'text/html'});
		 resp.end('<H1>'+f+' not found</H1>')
       } else {
         resp.writeHead(200, {'Content-Type': 'text/plain'});
		 resp.end(data)        
       }
   })
}).listen(8000)


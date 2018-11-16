var path = require('path');
var http = require('http');
var url = require('url');
var qs = require('querystring');
var fs = require('fs');

function printDir(r){
  var p = path.join(__dirname,r.url);
  var dir = p.split("?")[0];
  return "Directorio actual " + dir+ "\n"+"Ficheros de este directorio: \n" + getFiles('.');
}

function leerfichero(f){
    
  var inf = "";
  
   fs.readFile('a file that does not exist', (err, data) => {
    if (err) {
      console.error('There was an error reading the file!', err);
      return inf = El fichero no existe;
    }
  });
   
  return inf;
}

function getFiles(dir, files_){

  files_ = files_ || [];
  var files = fs.readdirSync(dir);

  for (var i in files ){
    var name = dir + '/' + files[i];
    if ( fs.statSync(name).isDirectory()){
      getFiles(name, files_);
    } else {
      files_.push(name);
    }
  }
  return files_;
}



function getDateTime() {
  var date = new Date();

  var hour = date.getHours();
  hour = (hour < 10 ? "0" : "") + hour;

  var min  = date.getMinutes();
  min = (min < 10 ? "0" : "") + min;

  var sec  = date.getSeconds();
  sec = (sec < 10 ? "0" : "") + sec;

  var year = date.getFullYear();

  var month = date.getMonth() + 1;
  month = (month < 10 ? "0" : "") + month;

  var day  = date.getDate();
  day = (day < 10 ? "0" : "") + day;

  return "Fecha actual "+ day+"/"+month+"/"+year+" Hora actual " + hour + ":" + min + ":" + sec;
}

http.createServer( function(request,response) {
  var query = url.parse(request.url).query;
  var info = qs.parse(query).info;

  response.writeHead(200, {'Content-Type':'text/plain'});
    switch(info) {
      case 'time': response.end(getDateTime());
      break;
      case 'dir': response.end("" +  printDir(request));
      break;
    //  default: response.end(""+leerfichero(info));
    }
    response.end("Ir a http://127.0.0.1:1337/?info=time o http://127.0.0.1:1337/?infor=dir");
}).listen('1337', "127.0.0.1");
console.log('Server running at http://127.0.0.1:1337/');

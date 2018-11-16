var fs = require('fs');
var path = require('path');
var dir;
var numEntrada=0;
var fileMax =0;
var fichero;
var numFiles = 0;
function printDir(r){
  var p = path.join(__dirname);
  dir = p.split("?")[0];
  return "Directorio actual " + dir+ "\n"+"Ficheros de este directorio: \n"+readDir(dir);
}

function readDir(dir){
  fs.readdir(dir, function(err, flist){
     if (err) {
        console.log('Error al leer el directorio ' + dirAllegir);
        console.log(err);
        return;
     }
     numFiles = flist.length;
     var elemNum = 0;
     var numEntrada = 0;
     var mostrarEntrada = function(entry,tamany){
        numEntrada = elemNum+1;
        console.log('Entrada '+numEntrada+": " + entry+" tamany: "+ tamany);
     }
     var BucleFichers = function(){
       llegirFichero(flist[elemNum]);
        /*mostrarEntrada(flist[elemNum],fitx);*/
        elemNum++;
        if (elemNum < flist.length) process.nextTick(BucleFichers);
     }
     if (elemNum < flist.length) process.nextTick(BucleFichers);
  });
}
function llegirFichero(file){
  fs.readFile(file,'utf8', function(err,fitx){
    if (err) {
       console.log('Error al leer el fichero ' + file);
       console.log(err);
       return;
    }
    ++numEntrada;
    if(file.length > fileMax){
      fileMax = file.length;
      fichero = file;
    }
    logMaxFile()
    console.log('Entrada '+numEntrada+": " + file+" tamany: "+ file.length);
    //  mostrarEntrada(fitx,fitx.length);
  });
}

function logMaxFile(){
  --numFiles;
  if(numFiles == 0){console.log("El fichero de mayor tamaño es: "+ fichero + " con tamaño: "+fileMax);}
}

console.log(printDir());

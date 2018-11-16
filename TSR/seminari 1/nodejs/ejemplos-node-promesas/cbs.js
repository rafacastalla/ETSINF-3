/* Lee y muestra por consola, mediante callbacks, el contenido de los ficheros 
 * (en orden alfabetico) de la carpeta denominada archivos. 
 * Omite el contenido de las subcarpetas.
*/


var fs = require('fs');


var path = __dirname + '/archivos';


var resultado = '';
fs.readdir(path, function(err,ficheros) {
  if(err) throw err;
  function leerFichero(i){
    if(i == ficheros.length) return console.log(resultado);
    var ficheroEnCurso = path + '/' + ficheros[i];
    fs.stat(ficheroEnCurso, function(err,stats) {
      if(err) throw err;
      if(stats.isFile()){
        fs.readFile(ficheroEnCurso,'utf8',function(err,texto) {
          if(err) throw err;
          resultado += texto;
          leerFichero(i+1);
        });
      } else leerFichero(i+1);
    });
  }
  leerFichero(0);
})



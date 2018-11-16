/* Lee y muestra por consola, mediante promesas, el contenido de los ficheros 
 * (en orden alfabetico) de la carpeta denominada archivos. 
 * Omite el contenido de las subcarpetas.
*/


var blue = require("bluebird");
var fs = require('fs');


process.chdir('archivos'); // Cambia el directorio de trabajo a archivos


fs.readdir(".", function(err,ficheros) {
  
  if(err){console.log("error: " + err);return}
 
  var resultado = '';
  var numFicheros = ficheros.length;
  
  if(numFicheros == 0) return resultado;
  
  var promesas = new Array(numFicheros);
  
  function prom(ficheroEnCurso){
	  	var p = blue.defer();
	  	fs.stat(ficheroEnCurso, function(err,stats) {
		  if(err) p.reject(err);
		  if(stats.isFile())
		     fs.readFile(ficheroEnCurso,"utf8",function(err,cont){
			   if(err)p.reject(err);
			     else p.resolve(cont);
		     });
		   else p.resolve("");
		 }); 
		 return p.promise;
  }  
  
  
  function exitoTotal(contenidos){ 
	  for(var k = 0; k < numFicheros; k++) resultado += contenidos[k];
	  console.log("resultado:\n"+resultado);
  }
  
  function algunError(err){console.log("error: " + err);}
  
  for(var j = 0; j < numFicheros; j++) promesas[j] = prom(ficheros[j]);

  blue.all(promesas).then(exitoTotal,algunError);
   
})




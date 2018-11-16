var fs = require('fs')
var total_votos = [ ]
var votos = [ ]
var res = 0;
var cont = 0;

fs.readdir('.',
  function (err, files) {
    cont = files.length;
    for (var i=0; i < files.length; i++) {
      var fitx = files[i];
      cont--;
      result(fitx);
      }
    }
)
function result(fitx){
  if(fitx.slice(-4) == '.txt'){
    fs.readFile(fitx,
      function(err,fix){
        var valor = JSON.stringify(fix);
        if(cont <=0){
          res++;
          console.log('Resultados globales: '+res);
        }
        total_votos[fitx]
        console.log('Provincia: \n'+fitx + '\nvotos en '+valor);
     }
   )
  }
}

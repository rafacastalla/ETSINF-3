var http = require("http");

var manejador = function(solicitud, respuesta){
  console.log("Resposta rebuda");
  respuesta.end("Hola món");
};

var servidor = http.createServer(manejador);
servidor.listen(8080);

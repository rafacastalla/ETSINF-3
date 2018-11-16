//Cliente chat



var net = require('net');


var client = net.connect({port: 10000},function() {   
   console.log('conectado');
   process.stdin.setEncoding('utf8');
});

process.stdin.on('data', function (datos) {
   if(datos=="fin\n") {
	   process.stdout.write('\n\n>>>>>              ---- Fin ----\n\n');
	   client.end();
	   process.stdin.destroy();
   }
   else {
	   process.stdout.write('Datos -->: '+ datos);
       client.write(datos);
	 }
});

process.stdin.on('end', function (datos) {
  process.stdout.write('\n\n>>>>>              ---- Cerrar ----\n\n');
  client.end();
});

client.on('data', function(data) {
  console.log(data.toString());
  process.stdout.write('Entrada de datos <-- : ');
});

client.on('end', function() {
  console.log('desconectado');
});

process.on('exit', function (datos) {
  console.log("················  Terminado");
  process.exit(0);
});




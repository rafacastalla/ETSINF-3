//Cliente tcp


var net = require('net');

var client = net.connect({port: 10000},function() { 
   console.log('\n\n-------- CONECTADO --------');
   process.stdin.setEncoding('utf8');
   process.stdout.write('Entrada de datos <-- : ');
});

process.stdin.on('data', function (datos) {
   if(datos=="fin\n") client.end();
   else {
	   process.stdout.write('Datos -->: '+ datos);
       client.write(datos);
	 }
});

client.on('data', function(data) {
  console.log("= = =>  ",data.toString());
  process.stdout.write('Entrada de datos <-- : ');
});

client.on('end', function() {
  console.log('-------- DESCONECTADO --------');
  process.stdin.destroy();
});


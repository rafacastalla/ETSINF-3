//Lectura de datos por stdin y manejo de eventos.


process.stdin.setEncoding('utf8');

console.log("\n\nplataforma:  " + process.platform + "\n\n");

setTimeout(function(){process.stdout.write('\n\n\t------------->>>>>\n\n\nEntrada de datos <--: ')},30000)

if(process.argv.length >= 3){
   var intervalo = parseInt(process.argv[2]);
   var comienzo = new Date();
   while(new Date() - comienzo < intervalo);
}

console.log("\n\n···················>> ¡ADELANTE!\n\n");
process.stdout.write('\n\nEntrada de datos <-- : ');

process.stdin.on('data', function (datos) {
  process.stdout.write('>>>  ' + datos + '\n\n\nEntrada de datos <--: ');
});

process.stdin.on('end', function (datos) {
  process.stdout.write('\n\n>>>>>              ---- Cerrar ----\n\n');
});

process.on('exit', function (datos) {
  process.stdout.write('\n\n>>>>>              Adiosssssssssssssssssss  hasta pronto  :-)\n\n');
});


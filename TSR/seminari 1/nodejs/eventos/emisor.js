//Emisor de eventos


var EventEmitter = require('events').EventEmitter;

var evento1 = 'e1';
var evento2 = 'e2';

function Acumulador(evento,entidadEmisora,valor){
   this.incremento = function(incr){
     valor += incr;
     this.emisor.emit(evento,entidadEmisora,evento,valor);
   }
}

function visualizar(entidad,evento,dato){
   console.log(entidad,evento+'··> ',dato);
}

Acumulador.prototype.emisor = new EventEmitter();

var registro1 = new Acumulador(evento1,'registro1:   ',0);
var registro2 = new Acumulador(evento2,'registro2:   ','0');

registro1.emisor.on(evento1,visualizar);
registro2.emisor.on(evento2,visualizar);

console.log('\n\n------->> inicial\n\n');

for(var i=1;i<=3;i++) registro1.incremento(i);

console.log('\n\n------------------>> intermedio\n\n');

for(var i=1;i<=3;i++) registro2.incremento(i);


console.log('\n\n-------------------------------->> fin\n\n');

//Utilizacion de funciones como argumentos. Uso de arguments.



function sumar(x,y){
  return x+y;
};

function eva(){
  if(arguments.length != 3) return null;
  if(typeof arguments[0] != 'function') return null;
  return arguments[0](arguments[1],arguments[2]);
};

var z = eva(sumar,10,-10);
console.log(z);

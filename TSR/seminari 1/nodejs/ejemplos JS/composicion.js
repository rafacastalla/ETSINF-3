var total=1000;

function operar(operacion){
  return operacion;
}

function sumar(cantidad){
  total += cantidad;
  console.log("Tras sumar "+cantidad+", hay "+total);
}

function restar(cantidad){
  total -= cantidad;
  console.log("Tras restar "+cantidad+", hay "+total);
}

operar(sumar)(10);
operar(sumar)(100);
operar(restar)(33);
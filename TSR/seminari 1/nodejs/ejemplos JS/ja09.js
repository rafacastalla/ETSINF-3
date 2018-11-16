//Creacion de objetos directamente y mediante constructores


var z="apellido"

var p1=new Object();
p1.nombre="Luis";
p1.apellido="Benavente";
console.log(p1);

var p2=new Object();
p2["nombre"]='Luis';
p2[z]='Benavente';
console.log(p2);

var p3={"nombre":"Luis",apellido:"Benavente"};
console.log(p3);

function Persona(nombre,apellido){
  this.nombre=nombre;
  this.apellido=apellido;
}
var p4=new Persona("Luis","Benavente"); //Es de tipo Persona
console.log(p4);

function persona(nombre,apellido){
  var o=new Object();
  o.nombre=nombre;
  o.apellido=apellido;
  return o;
}

var p5=persona("Luis","Benavente"); // es de tipo Object
console.log(p5);

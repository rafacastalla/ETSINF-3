//Similar a los anteriores. Se hace uso de this en los metodos.


var nombre="Aureliano";

var p1=new Object();
p1.nombre="Luis";
p1.apellido="Benavente";
p1.mensaje=function(texto){
	return p1.nombre+"  "+p1.apellido+"  dice: "+texto;
}
console.log(p1);
console.log(p1.mensaje("HOLA"));


var p3={"nombre":"Luis",apellido:"Benavente",
  mensaje:function(texto){
	return nombre+"  "+this.apellido+"  dice: "+texto;
}};
console.log(p3);
console.log(p3.mensaje("ADIOS"));


function Persona(nombre,apellido){
  this.nombre=nombre;
  this.apellido=apellido;
  this.mensaje=function(texto){
	return this.nombre+"  "+this.apellido+"  dice: "+texto;
}
}
var p4=new Persona("Luis","Benavente");
console.log(p4);
console.log(p4.mensaje("HOLA Y ADIOS"));

p4.nombre="Fernando";
console.log(p4);
console.log(p4.mensaje("HOLA Y ADIOS"));

function persona(nombre,apellido){
  var o=new Object();
  o.nombre=nombre;
  o.apellido=apellido;
  o.mensaje=function(texto){
	return this.nombre+"  "+apellido+"  dice: "+texto;
}
  return o;
}
var p5=persona("Luis","Benavente");
console.log(p5);
console.log(p5.mensaje("HE VUELTO"));


var p6=persona("Jose","Benavente");
console.log(p6);
console.log(p6.mensaje("HE VUELTO"));

p6.nombre="Felix";
p6.apellido="Morente";
console.log(p6);
console.log(p6.mensaje("HE VUELTO"));


var p7=new Object();
p7.nombre="Miguel";
p7.apellido="Bellido";
p7.mensaje=p5.mensaje;
console.log(p7);
console.log(p7.mensaje("Estoy de vacaciones"));


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
	return nombre+"  "+apellido+"  dice: "+texto;
}
}
var p4=new Persona("Luis","Benavente");
console.log(p4);
console.log(p4.mensaje("HOLA Y ADIOS"));

function persona(nombre,apellido){
  var o=new Object();
  o.nombre=nombre;
  o.apellido=apellido;
  o.mensaje=function(texto){
	return nombre+"  "+apellido+"  dice: "+texto;
}
  return o;
}
var p5=persona("Luis","Benavente");
console.log(p5);
console.log(p5.mensaje("HE VUELTO"));

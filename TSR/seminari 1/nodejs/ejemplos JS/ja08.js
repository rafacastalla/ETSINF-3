//Creacion y manipulacion elemental de objetos


var x=new Object();

x.nombre="Jaime";
x["edad"]=15;
console.log(x["nombre"]);
console.log(x.edad);
console.log(x);

delete x.nombre;
console.log(x);
delete x.edad;
console.log(x);

var y = {};
y.persona = x;
y["otra persona"] = {};
y["otra persona"].nombre = "Luis";
y["otra persona"].edad = 20;
console.log(y);

var z = "otra persona";
console.log(y[z]);

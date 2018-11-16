//Funciones con propiedades y variables internas. Creacion de objetos mediante constructores.

var z = 1000;


function f(x1,x2){
	var y = x1;
	this.z = x2;
	this.fun = function(){return f.op(f.a,y,this.z);}
	this.getY = function(){return y;}
}

f.a = 101;

f.op = function(u,v,w){return u+v+w;}

var obj = new f(11,21); // En obj y puede contemplarse como una propiedad privada.

console.log(obj);
console.log(obj.z);
console.log(obj.fun());

f.op = function(u,v,w){return u-v/w}
console.log(obj.fun());

console.log(obj.getY());


obj.z = -1001;
console.log(obj);
console.log(obj.fun());

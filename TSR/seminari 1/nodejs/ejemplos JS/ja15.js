//Introspeccion.



Object.prototype.saludo=function(){
	var y=typeof this;
	var x="HOLA, SOY UN/A: " + y + "   ";
	var z;
	switch(y){
	  case "function": z=this; break;
	  case "object": z=JSON.stringify(this);
    }
    return x+z;
}

ar=[1,2,3];
console.log(ar.saludo());

var fun=function(){
	return 5;
}

console.log(fun.saludo());

var p=new Object();
p.x=1;
p.y=2;

console.log(p.saludo());

var qq=new fun();
console.log(qq);
console.log(qq.saludo());



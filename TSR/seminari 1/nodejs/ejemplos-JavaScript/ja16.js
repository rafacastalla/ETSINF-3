

//Introspeccion.



Object.prototype.presentación=function(){
	if(typeof this =="function") return "" + this;
	  else{
		  var r = "Object:{";
		  var s = " ";
		  var n = arguments.length;
		  var m = n == 0? 1:arguments[0]+1;
		  for(var k = 0;k < m;k++) s = s + " ";
		  for(var x in this) if(x != "presentación")
		              r = r + "\n" + s + x + ":  " +  (typeof this[x] == "object"? this[x].presentación(m+1):this[x]);
		  return r + "\n" + s +"}";
	  }
}




function fun(){return 7}

var z=new Object();
z.u=1;
z.v=2;
z.m=function(){return "x x x x"};
z.n={q:{xx:"OBJ1",yy:"OBJ2"},qq:2000};


var ar=[1,2,3,4]

console.log(fun.presentación());
console.log(z.presentación());
console.log(ar.presentación());

fun.prototype.presentación=function(){return "------------->"}
var t=new fun();
console.log(t.presentación());


var zSerial=JSON.stringify(z); //Solamente se serializa el estado del objeto
console.log("objeto serializado:  ");
console.log(zSerial);

var zzz=JSON.parse(zSerial); //Solamente se deseriza el estado del objeto
console.log("objeto deserializado:  ");
console.log(zzz);






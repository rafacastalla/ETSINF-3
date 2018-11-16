//Uso de strings y arrays. Algunas operaciones relacionadas y booleanas.


var s="hola";
var st=new String("hola");

console.log("s==st:  "+(s==st));
console.log("s===st:  "+(s===st));

var so=new String("hola");

console.log("so==st:  "+(so==st));
console.log("so===st:  "+(so===st));

	
var ar=["cuadrado","rectángulo","triángulo"];
console.log(ar);
console.log("es array:  " + (ar instanceof Array));
console.log(ar.toString());

var fig="cuadrado,rectángulo,triángulo";

console.log("fig==ar.toString():  "+(fig==ar.toString()));

console.log("s!=NaN:  "+(s!=NaN));
console.log("s>=0:  "+(s>=0));
console.log("s<0:  "+(s<0));

console.log('""==0:  '+(""==0));

console.log('"alfa"<"b":  '+("alfa"<"b"));
console.log('"alfa"<"Alfa":  '+("alfa"<"Alfa"));

console.log("true > false:  "+(true > false));
console.log("false < 0:  "+(false < 0));
console.log("false >= 0:  "+(false >= 0));
console.log("---"+true);



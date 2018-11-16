//Strings junto con algunas operaciones booleanas


var s="hola";
var st=new String("HOLA");

console.log(st);
console.log("st:  "+st);
console.log(st.toString());

console.log("s||st:  "+(s||st));
console.log("true||s||st:  "+(true||s||st));
console.log("false||s||st:  "+(false||s||st));

console.log("-------------------------------------\n");

console.log("s && st:  "+(s && st));
console.log("true && s && st:  "+(true && s && st));
console.log("false && s && st:  "+(false && s && st));
console.log('"****" && s && st:  '+("****" && s && st));
console.log('"" && s && st:  '+("" && s && st));
console.log("0 && s && st:  "+(0 && s && st));
console.log("1 && s && st:  "+(1 && s && st));

console.log("-------------------------------------\n");


console.log("0 && null && NaN:  "+(0 && null && NaN));
console.log("0 || null || NaN:  "+(0 || null || NaN));

console.log("-------------------------------------\n");

var x={a:1,b:2}
var y=false||x;
console.log(y);




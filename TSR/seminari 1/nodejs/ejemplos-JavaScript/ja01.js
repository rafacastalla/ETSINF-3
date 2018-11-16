// Utilizacion numerica

console.log(5/0);
console.log(Infinity==Number.POSITIVE_INFINITY);




function FFF(x){
	var z=Number.MAX_VALUE + x;
	console.log("Number.MAX_VALUE: "+Number.MAX_VALUE);
	console.log("Number.MAX_VALUE+Number.MAX_VALUE: "+(Number.MAX_VALUE+Number.MAX_VALUE));
	console.log("z: "+z);
	console.log("z/0: "+z/0);
	console.log("Infinity/Infinity: "+Infinity/Infinity);
};



console.log("------------------");


FFF(10000);



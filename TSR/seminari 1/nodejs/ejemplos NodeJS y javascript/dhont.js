// reparto de escaños mediante la ley d'hont
const totalEscaños=8, votos={A:12, B:7, C:4, D:3}
var escaños={}, partido, result={}

function seq(n,e) {
	var r=[n]
	for (var i=2; i<=e; i++) r.push(n/i)
	return r
}

for (partido in votos) {
	escaños[partido]=seq(votos[partido],totalEscaños)
	result[partido]=0
}
//console.log(escaños)
for (var i=0; i<totalEscaños; i++) {
		// elige el maximo entre primeros valores de cada partido, y borra el elegido
	var pmax="", max=0
	for (partido in votos) {
		if (escaños[partido][0]>max) {
			pmax=partido; max=escaños[partido][0]
		}
	}
	//console.log(max,pmax)
	result[pmax]++; escaños[pmax].shift(0)
}
console.log("total escaños:     ", 	totalEscaños, 
			"\nvotos:           ",	votos, 
			"\nreparto escaños: ",	result)

var fs = require("fs")
var ficheros = process.argv.slice(2)

function sync(ficheros) { 		// -------- sincronico, resultado ok (pero se pide asincronico)
	var fmax="", max=0
	for (var i=0; i<ficheros.length; i++) {
		var item = ficheros[i], data=fs.readFileSync(item)
		if (data.length>max) {max=data.length; fmax=item}
	}
	console.log("El maximo es",fmax,"con talla",max)
}

function asyncErr1(ficheros) { 	// -------- asincronico, (escribe resultado antes de tiempo)
	var fmax="", max=0
	for (var i=0; i<ficheros.length; i++) {
		var item = ficheros[i]
		fs.readFile(item, function(err,data) {  // Asynchronous
			if (!err && data.length>max) {max=data.length; fmax=ficheros[i]}
		})
	}
	console.log("El maximo es",fmax,"con talla",max)
}

function asyncErr2(ficheros) { 	// -------- asincronico, falta clausura
	var fmax="", max=0
	for (var i=0; i<ficheros.length; i++) {
		var item = ficheros[i]//item es igual al ultim ficheros de i per aixo no sactualitza
		fs.readFile(item, function(err,data) {  // Asynchronous
			if (!err && data.length>max) {max=data.length; fmax=item}
		})
	}
	process.on('exit',function() {console.log("El maximo es",fmax,"con talla",max)})
}

function async1(ficheros) { 	// -------- asincronico, ok
	var fmax="", max=0
	function procesa(item) {
		fs.readFile(item, function(err,data) {  // Asynchronous
			if (!err && data.length>max) {max=data.length; fmax=item}
		})
	}
	for (var i=0; i<ficheros.length; i++)
		procesa(ficheros[i])//passem el ficher per a cada iteracio aixina no agafa el ultim quan entra en el fmax=item
	process.on('exit',function() {console.log("El maximo es",fmax,"con talla",max)})
}

function async2(ficheros) { 	// -------- asincronico, ok
	var fmax="", max=0
	ficheros.forEach(function (item) {
		fs.readFile(item, function(err,data) {
			if (!err && data.length>max) {max=data.length; fmax=item}
		})
	})
	process.on('exit',function() {console.log("El maximo es",fmax,"con talla",max)})
}
function async3(ficheros) { 	// -------- asincronico, (escribe resultado antes de tiempo)
	var fmax="", max=0
	var cont = ficheros.length;
	for (var i=0; i<ficheros.length; i++) {
		var item = ficheros[i]
		fs.readFile(item, function(err,data) {  // Asynchronous
			if (!err && data.length>max) {max=data.length; fmax=ficheros[i]}
			cont--;
			if(cont == 0) console.log("El maximo es",fmax,"con talla",max)
		})
	}
}

//sync(ficheros)
//asyncErr1(ficheros)
//asyncErr2(ficheros)
//async3(ficheros)
//async1(ficheros)
//async2(ficheros)

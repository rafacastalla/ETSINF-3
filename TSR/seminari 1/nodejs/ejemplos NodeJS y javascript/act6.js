var fs = require("fs")
var ficheros = process.argv.slice(2)
var fmax=0, max=0, faltan=ficheros.length

ficheros.forEach(function (item,idx) {
	fs.readFile(item, function(err,data) {
		if (!err && data.length>max) {max=data.length; fmax=idx}
		if (!--faltan) console.log("El maximo es ",ficheros[fmax],"con talla",max)
	})
})
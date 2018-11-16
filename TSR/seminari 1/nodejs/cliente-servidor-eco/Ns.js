//Servidor eco tcp


var net=require("net");

var servidor=net.createServer();

servidor.on("connection",function(usuario){
	
	var direccion = usuario.remoteAddress + "   " + usuario.remotePort;
	console.log("Conexión establecida. Usuario: " + direccion);
	
	usuario.on("data",function(datos){
		console.log("datos usuario " + direccion + " ---> "  + datos.toString("utf8"));
		usuario.write("eco: " + datos);
	})

	usuario.on("end",function(){
		console.log("Fin de la conexión. Usuario: " + direccion);
	}) 
	
});

servidor.listen(10000,"localhost");



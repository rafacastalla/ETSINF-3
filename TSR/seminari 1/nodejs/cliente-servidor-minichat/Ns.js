//Servidor chat

var net=require("net");

var servidor=net.createServer();  

var usuarios = [];


function añadir(item){
	for(var itm in usuarios) if(itm == item) return;
	item.setTimeout(0);
    usuarios.push(item);
    usuarios.forEach(function(usu) {
       usu.write("\n\n NUEVA CONEXION  ··········> numero usuarios: "+ usuarios.length);
    });
};

function eliminar(item){
	var j = 0;
	for(var i = 0; i < usuarios.length; i++) 
	  if(usuarios[i] != item) usuarios[j++] = usuarios[i];
	usuarios.length = j;
	usuarios.forEach(function(usu) {
       usu.write("\n\n DESCONEXION   ··········> numero usuarios: "+ usuarios.length);
    });
};

servidor.on("connection",function(usuario){

	var direccion = usuario.remoteAddress + "   " + usuario.remotePort;
	añadir(usuario);
	
	console.log("numero usuarios: "+ usuarios.length);
	console.log("Conexión establecida. Usuario: " + direccion);
	
	usuario.on("data",function(datos){
		console.log("datos --> " + datos.toString("utf8"));
		
		usuarios.forEach(function(usu) {
            usu.write("\n\n-->: " + datos);
         });
         
	});

	usuario.on("end",function(){
		console.log("Fin de la conexión. Usuario: " + direccion);
		eliminar(usuario);
		console.log("numero usuarios: "+ usuarios.length);
	});
	
});

servidor.listen('10000',"localhost", function(){
	console.log("----> En servicio:");
	console.log("     ",servidor.address());
});





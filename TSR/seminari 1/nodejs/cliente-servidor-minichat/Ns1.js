//Servidor chat

var net=require("net");

var servidor=net.createServer();  

var usuarios = [];


function añadir(item){
	item.setTimeout(0);
    usuarios.push(item);
    usuarios.forEach(function(usu) {
       usu.write("\n\n NUEVA CONEXION  ··········> numero usuarios: "+ usuarios.length);
    });
};


//EJERCICIO: Reescribir la funcion eliminar con los métodos indexOf y splice
//de Array.

function eliminar(item){
	var j = 0;
	var copiar = false;
	for(var i = 0; i < usuarios.length; i++) 
	  if(!copiar){
		  if(usuarios[i] == item) {
		     j = i;
		     copiar = true;
	      }
	  } else usuarios[j++] = usuarios[i];
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





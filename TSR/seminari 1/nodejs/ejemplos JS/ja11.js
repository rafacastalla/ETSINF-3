//Influencia de la sentencia return en la creacion de objetos mediante constructores.



function f(x,y){
	this.x=x;
	this.y=y;
	return {u:"defecto1",v:"defecto2"}
}

var a=f(1,2);

var b=new f(1,2);

console.log(a);

console.log(b);

function ff(x,y){
	this.x=x;
	this.y=y;
}

console.log(new ff(1,2));



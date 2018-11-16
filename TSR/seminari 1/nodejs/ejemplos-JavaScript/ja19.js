//Algunos usos de la funcion bind


var perro = {
  nombre: 'sultan',
  patas: 4,
  ladra: function() {console.log(this.nombre + "guau")}
}

perro.ladra() // escribe "sultan guau"

var f = perro.ladra
f() // f no esta asociada a un objeto (this no esta definido) -----> error

var g=f.bind(perro); 
g();


//-------------------------------------------------


var rectangulo = {
	ancho: 10,
	alto: 100,
	tipo: "rectangulo",
	area: function() {return this.ancho * this.alto;}
}

function mostrarArea(){
   console.log("\nEl area de la figura (" + this.tipo + ") es: " + this.area());
}

var mostrarAreaRectangulo = mostrarArea.bind(rectangulo);
mostrarAreaRectangulo();

rectangulo.ancho = 20;
rectangulo.alto = 30;
mostrarAreaRectangulo();




//Prototipos externos asignados a funciones. Uso del operador instanceof.

function P(){}

var prototipo={
  nombre:"Aquiles",
  apellido:"Pelaez",
  estado:"jubilado",
  igual:function (x){
        return this.nombre==x.nombre && this.apellido==x.apellido && this.edad==x.edad &&  
               this.ocupación==x.ocupación;
       }
}

P.prototype=prototipo;

var p=new P();

console.log("p instanceof Object:  " + (p instanceof Object));

console.log("p instanceof P:  " + (p instanceof P));

console.log("-----------------------------------------------------");
console.log(P.prototype);
console.log(P.prototype.constructor === Object);

var x=new P.prototype.constructor();
console.log(x);// Objeto vacio

console.log("p.constructor==Object: " +(p.constructor==Object));



function Q(){}

var Qprototipo={
  constructor:Q,
  nombre:"Aquiles",
  apellido:"Pelaez",
  estado:"jubilado",
  igual:function (x){
        return this.nombre==x.nombre && this.apellido==x.apellido && this.edad==x.edad &&  
               this.ocupación==x.ocupación;
       }
}

Q.prototype=Qprototipo;

var q=new Q();

console.log("q instanceof Object:  " + (q instanceof Object));

console.log("q instanceof Q:  " + (q instanceof Q));

console.log(Q.prototype.constructor);
console.log("q.constructor==Q: " + (q.constructor==Q));


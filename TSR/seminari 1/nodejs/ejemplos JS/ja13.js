//Prototipos


function Persona(){}

Persona.prototype.nombre="Aquiles";
Persona.prototype.apellidos="Pelaez";
Persona.prototype.edad=95;
Persona.prototype.estado="jubilado";
Persona.prototype.igual=function (x){
        return this.nombre==x.nombre && this.apellido==x.apellido && this.edad==x.edad &&  
               this.estado==x.estado;
}
Persona.prototype.prototipo=function(){return this;}

var p=new Persona();

var p1=new Persona();
p1.nombre="Alejandro";

console.log("p: ---->");
console.log(p);
for(x in p)console.log(x+"  "+p[x]);

console.log("p1: ---->");
console.log(p1);
for(x in p1)console.log(x+"  "+p1[x]);

console.log("------------------------------");
console.log(p.igual(p1));
console.log(p1.igual(p));

console.log("------------------------------");
delete p1.nombre;
console.log(p.igual(p1));

console.log("------------------------------");
console.log(p.prototype); // Indefinido

console.log("-------------------> PROTOTIPO:");
console.log(Object.getPrototypeOf(p));
console.log(Object.getPrototypeOf(p) === p.__proto__);
console.log(p.__proto__.constructor);

console.log("=========================================================");

var q=new p.__proto__.constructor();
q.nombre="Graciano";
for(x in q)console.log("                  "+x+"  "+q[x]);

console.log("------------------------------");

console.log(p==p.prototipo());


console.log("=========================================================");

Persona.prototype.nombre="Ulises";
var p2=new Persona();

console.log(p.igual(p2));
console.log(p==p2.prototipo());

for(x in p2)console.log(x+"  "+p[x]);

console.log("------------------------------");
q=new p.constructor();
q.nombre="Aquiles Jr.";
q.estado="activo";
q.edad=35;
for(x in q)console.log("                  "+x+"  "+q[x]);









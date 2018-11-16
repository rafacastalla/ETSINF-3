//Algunas operaciones con Arrays


var a1=new Array();

a1[2]=100;
console.log(a1);

a1[0]=12;
console.log(a1);

a1[-1]=-120;
console.log(a1);

delete a1[-1];
console.log(a1);

a1["elemento"]="valor";
console.log(a1);

var obj={p1:100,p2:-2};
a1[obj]=function(x,y){return y*x};
console.log(a1);

console.log(obj);

console.log(a1[obj](obj.p1,obj.p2));

console.log(a1.length);

a1.length=2;
console.log(a1);

a1[6]=0;
console.log(a1);

for(x in a1)console.log(x + "   " + a1[x]);


a1=[1,2,3,4,5];
console.log(a1);


a1=new Array(1,2,3,4,5);
console.log(a1);

var a2=[1,2,"verde",4,5,"azul"];
console.log(a2);

var a3=new Array();
a3[10]=10;
console.log(a3);
console.log(a3[2]);




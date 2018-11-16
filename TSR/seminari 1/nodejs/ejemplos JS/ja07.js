//Uso de clausuras y parametros funcionales.


function f(y,z){
  console.log("y="+y);
  console.log("z="+z);
  return function(n){
            return y+z+n;
          }
}

var xx=f(2,3);
console.log(xx(10));


function ff(fun,n){
	return fun(n);
}

console.log(ff(xx,-1000));

console.log("----------------------------");

function fff(n,m,k,fun){
	return fun(n,m)(k)
}

console.log(fff(2,3,10,f));

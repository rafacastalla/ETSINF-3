//Clausuras y variable locales y globales

var x=20;

function f(y,z){
  x =12;
  console.log("y="+y);
  console.log("z="+z);
  return function(){
            return y+z+x;
          }
}

function ff(y,z){
  var x =10;
  console.log("y="+y);
  console.log("z="+z);
  return function(){
            return y+z+x;
          }
}


var xx=f(2,3);
console.log(xx());
console.log(x);


xx=ff(2,3);
console.log(xx());
console.log(x);

function sum(seq) {
   var x=seq[0]
   for(var i=1; i<seq.length; i++){
	  x=x+seq[i]
   }
   return x
}

function prod(seq) {
   var x=seq[0]
   for(var i=1; i<seq.length; i++){
	  x=x*seq[i]
   }
   return x
}

function maxim(seq) {
   var x=seq[0]
   for(var i=1; i<seq.length; i++){
	  x=Math.max(x,seq[i])
   }
   return x
}

function minim(seq) {
   var x=seq[0]
   for(var i=1; i<seq.length; i++){
	  x=Math.min(x,seq[i])
   }
   return x
}

/*
function redu(f) {
   return function(seq){
      var x=seq[0]
	  for(var i=1; i<seq.length; i++){
	     x=f(x,seq[i])
      }
	  return x
   }
}

var sum  = redu(function(a,b){return a+b})
var prod = redu(function(a,b){return a*b})
var maxim= redu(function(a,b){return Math.max(a,b)})
var minim= redu(function(a,b){return Math.min(a,b)}
*/

var seq=[1,2,3,2,1]
console.log(sum  (seq))
console.log(prod (seq))
console.log(maxim(seq))
console.log(minim(seq))
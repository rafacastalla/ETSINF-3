function qs(seq) {
   if (seq.length < 2) return seq;
   var p=seq[0]
   return qs(seq.filter(function(i){return i<p}
		  )).concat(seq.filter(function(i){return i==p}
		  )).concat(qs(seq.filter(function(i){return i>p}
		  )))
}

console.log(qs([3,1,5,8,2,4,3,7]))
console.log(qs(["uno","dos","tres","cuatro","dos","uno"]))

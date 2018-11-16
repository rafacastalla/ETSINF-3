

//Pseudoarrays.

var i = 0;

var a = {};

while(i < 5) {
a[i] = i;
i++;
};

console.log(a.length);

console.log(a);
console.log(a instanceof Array);

a.length = i;

console.log(a.length);

var total = 0;

for(var j = 0; j < a.length; j++){
total += a[j];
console.log(total);
};

console.log(a);


var b = Array.prototype.slice.call(a);

console.log(b);
console.log(b instanceof Array);




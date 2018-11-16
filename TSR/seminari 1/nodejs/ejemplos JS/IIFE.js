//Immediately-invoked function expressions allow functions to pass around variables under their own closures.

var v;
v = 1;
var getValue = (function(v) {
  return function() {return v;};
})(v);

v = 2;

getValue(); // 1

var obj = {
            x:1,
            y:2,
            f: function(z){
                 return this.x + this.y +z;
               }
           };


var oo = Object.create(obj);

console.log(oo.f(3));

console.log(Object.getPrototypeOf(oo) == obj);

console.log(oo.prototype);
console.log("proto:  " );
console.log(oo.__proto__);
console.log(Object.getPrototypeOf(oo) == oo.__proto__);
console.log(oo.__proto__ == obj);
console.log(obj.isPrototypeOf(oo));


oo.proto =  Object.getPrototypeOf(oo);

oo.proto.f = function(z){
                 return this.x - this.y +z;
               };
               
console.log(oo.f(3));

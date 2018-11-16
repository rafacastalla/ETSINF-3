function suma  (x,y) {return x+y}
function prod  (x,y) {return x*y}
function minimo(x,y) {return x<y?x:y}
function maximo(x,y) {return x>y?x:y}

function recorre(op,a) {
    var r= a[0]
    for (var i=1; i<a.length; i++)
        r = op(r,a[i])
    return r
}

var a=[1,2,3,4]
console.log(recorre(suma,a), recorre(prod,a), recorre(minimo,a), recorre(maximo,a))
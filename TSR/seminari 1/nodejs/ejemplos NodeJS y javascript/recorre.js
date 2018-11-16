function suma  (x,y) {return x+y}
function prod  (x,y) {return x*y}
function minimo(x,y) {return x<y?x:y}
function maximo(x,y) {return x>y?x:y}

function sumaTotal(a) {
    var r= a[0]
    for (var i=1; i<a.length; i++)
        r = suma(r,a[i])
    return r
}

function prodTotal(a) {
    var r= a[0]
    for (var i=1; i<a.length; i++)
        r = prod(r,a[i])
    return r
}

function minimoDe(a) {
    var r= a[0]
    for (var i=1; i<a.length; i++)
        r = minimo(r,a[i])
    return r
}

function maximoDe(a) {
    var r= a[0]
    for (var i=1; i<a.length; i++)
        r = maximo(r,a[i])
    return r
}

var a=[1,2,3,4]
console.log(sumaTotal(a), prodTotal(a), minimoDe(a), maximoDe(a))

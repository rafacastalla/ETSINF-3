function suma  (x,y) {return x+y}
function prod  (x,y) {return x*y}
function minimo(x,y) {return x<y?x:y}
function maximo(x,y) {return x>y?x:y}

function recorre(op) {
    return function(a) {
        var r= a[0]
        for (var i=1; i<a.length; i++)
            r = op(r,a[i])
        return r
    }
}

var sumaTotal 	= recorre(suma)
var prodTotal   = recorre(prod)
var minimoDe 	= recorre(minimo)
var maximoDe 	= recorre(maximo)

var a=[1,2,3,4]
console.log(sumaTotal(a), prodTotal(a), minimoDe(a), maximoDe(a))
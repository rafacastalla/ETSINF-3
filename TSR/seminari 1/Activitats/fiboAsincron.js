//Asincron
function fibo(n) { return (n<2) ? 1 : fibo(n-2) + fibo(n-1) }

function fibo_back1(n,cb) {
  var m = fibo(n)
  cb('fibonacci('+n+') = '+m)
}

function fact(n) { return (n<2) ? 1 : n * fact(n-1) }

function fact_back1(n,cb) {
  var m = fact(n)
  cb('factorial('+n+') = '+m)
}
console.log('Iniciant execució...')

setTimeout( function(){
  fibo_back1(40, console.log)
}, 2000 )

console.log('llançat càlcul fibonacci...')

setTimeout( function(){
  fact_back1(10, console.log)
}, 1000 )

console.log('llançat càlcul factorial...')

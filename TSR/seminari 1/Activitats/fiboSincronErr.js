//Sincron amb err
function fibo(n) {
  return (n<2) ? 1 : fibo(n-2) + fibo(n-1)
}

function fibo_back2(n,cb) {
  var err = eval_err(n,'fibonacci')
  var m = err ? '': fibo(n)
  cb(err,'fibonacci('+n+') = '+m)
}

function fact(n) { return (n<2) ? 1 : n * fact(n-1) }

function fact_back2(n,cb) {
  var err = eval_err(n,'factorial')
  var m = err ? '': fact(n)
  cb(err,'factorial('+n+') = '+m)
}

function show_back(err,res) {
  if (err) console.log(err)
  else console.log(res)
}

function eval_err(n,s) {
  return (typeof n != 'number') ?
  s+'('+n+') ??? : '+n+' is not a number' : ''
}
console.log('Iniciant execució...')
setTimeout( function(){
  fibo_back2(40, show_back)
  fibo_back2('pep', show_back)
}, 2000 )
console.log('llançat càlcul fibonacci...')
setTimeout( function(){
  fact_back2(10, show_back)
  fact_back2('ana', show_back)
}, 1000 )
console.log('llançat càlcul factorial...')

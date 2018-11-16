//Sincron
function fibo(n) {
  return (n<2) ? 1 : fibo(n-2) + fibo(n-1)
}
function fact(n) {
  return (n<2) ? 1 : n * fact(n-1)
}

console.log('Iniciant execució...')
console.log('llançat càlcul fibonacci...')
console.log('fibo(40) =', fibo(40))
console.log('llançat càlcul factorial...')
console.log('fact(10) =', fact(10))

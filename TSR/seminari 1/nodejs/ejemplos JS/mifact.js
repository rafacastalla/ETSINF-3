function f(x){
  if (x==0) return 1;
  return x*f(x-1);
}
z=4; k=f(z);
console.log("El factorial de "+z+" es "+k);
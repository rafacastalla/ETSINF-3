var net = require('net');
var fun = require('./myfunctuin');

var end_listener = function() {console.log('server disconnected');}
var error_listener = function() {console.log('some connection error');}
var bound_listener = function() {console.log('server bound');}

var server = net.createServer(
  function(usuario){
    usuario.on('err',error_listener);
    usuario.on('end',end_listener);
    usuario.on('data',
      function(data){
        var obj = JSON.parse(data);
        var res;
        if(typeof(obj.numb)!='number'){
           res = NaN;
        }else{/*
          switch(obj.func){
            case 'fibo': res = fun.fibo(obj.numb);break;
            case 'fact': res = fun.fact(obj.numb);break;
            default: res = NaN;
          }*/
          if(obj.func == 'fibo'){
            res = fun.fibo(obj.numb);
          }else if(obj.func =='fact'){
            res = fun.fact(obj.numb);
          }else {
            res = NaN;
          }
        }
        usuario.write( obj.func+'('+obj.numb+') = '+res );
      }
    )
  }
);
server.listen(9000, bound_listener);

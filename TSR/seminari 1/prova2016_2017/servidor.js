var net = require('net')
var fs = require('fs')
var votos = [ ]

var server = net.createServer(function(c) {
  c.on('data', function(data){
    var object = JSON.parse(data);
    var prov = object.provincia;
    delete object.provincia;
    delete object.colegio;

    if(votos[prov]){
      for(i in object){
          if(!votos[prov][i]){
            votos[prov][i]=object[i];
          }else{
            votos[prov][i]+=object[i]
          }
      }
    }
    else{
      votos[prov] = object;
    }
  })
})
server.listen(9000,
  function() { console.log('server bound')
})

function guardar() {
  for(prov in votos){
    var obj = JSON.stringify(votos[i])
    fs.writeFileSync(prov+".txt",obj)
  }
  console.log('datos volcados a disco')
}
setInterval(guardar(),20000)

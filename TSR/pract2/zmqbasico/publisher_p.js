var zmq = require('zmq')
var publisher = zmq.socket('pub')

var args = process.argv.slice(2);
var port = args[0] || 'tcp://*:8688';
var nMSGs = args[1] || 10;
var type1 = args[2] || "NEWS";
var type2 = args[3] || "SPORTS";
var aux = require("./auxfunctions1718.js");

publisher.bind(port, function(err) {
  if(err)
    console.log(err)
  else
    console.log("Listening on "+port+"...")
})

for (var i=1 ; i<nMSGs ; i++)
    setTimeout(function() {
        console.log('sent');
        publisher.send(type1 +  " Hello there! " + aux.randNumber(nMSGs,1));
        publisher.send(type2 +  " Hello there! " + aux.randNumber(nMSGs,1));
    }, 1000 * i)

process.on('SIGINT', function() {
  publisher.close()
  console.log('\nClosed')
})

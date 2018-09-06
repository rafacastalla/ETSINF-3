// broker.js
// Basic ROUTER-DEALER broker.

var zmq = require('zmq');
var router = zmq.socket('router');
var dealer = zmq.socket('dealer');

// Bind these sockets to their ports.
router.bindSync("tcp://*:8000");
dealer.bindSync("tcp://*:8001");

// The router simply forwards messages 
// in both directions...
router.on('message', function(){
  var args = Array.apply(null, arguments);
  dealer.send(args);
});

dealer.on('message', function() {
  var args = Array.apply(null, arguments);
  router.send(args);
});

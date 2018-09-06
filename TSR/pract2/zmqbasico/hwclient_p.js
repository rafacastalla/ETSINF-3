// Hello World client
// Connects REQ socket to tcp://localhost:5555
// Sends "Hello" to server.

var zmq = require('zmq');

//take the arguments and delete 'node' and 'nameprogram.js'
var args = process.argv.slice(2);

//variable for url and port that we use to connect to the server
var servURL = args[0] || "tcp://localhost:5555";
//number of petitions we are going to do
var numPet = args[1] || 10;
//text we are going to send
var msg = args[2] || "Hello";

// socket to talk to server
console.log("Connecting to hello world server...");
var requester = zmq.socket('req');

var x = 0;
requester.on("message", function(reply) {
  console.log("Received reply", x, ": [", reply.toString(), ']');
  x += 1;
  if (x === 10) {
    requester.close();
    process.exit(0);
  }
});

requester.connect(servURL);

for (var i = 0; i < numPet; i++) {
  console.log("Sending request", i, '...');
  requester.send(msg);
}

process.on('SIGINT', function() {
  requester.close();
});

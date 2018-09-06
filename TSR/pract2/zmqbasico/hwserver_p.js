// Hello World server
// Binds REP socket to tcp://*:5555
// Expects "Hello" from client, replies with "world"

var zmq = require('zmq');

//take the arguments and delete 'node' and 'nameprogram.js'
var args = process.argv.slice(2);

//variable for the port that we use to binding
var servURL = args[0] || 'tcp://*:5555';
//number of seconds to wait for each response
var numSec = args[1] || 1000;
//text for each response
var msg = args[2] || "World";

// socket to talk to clients
var responder = zmq.socket('rep');

responder.on('message', function(request) {
  console.log("Received request: [", request.toString(), "]");

  // do some 'work'
  setTimeout(function() {

    // send reply back to client.
    responder.send(request +" "+ msg);
  }, numSec);
});

responder.bind(servURL, function(err) {
  if (err) {
    console.log(err);
  } else {
    console.log("Listening on 5555...");
  }
});

process.on('SIGINT', function() {
  responder.close();
});

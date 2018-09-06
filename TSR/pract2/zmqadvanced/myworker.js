// myworker server in NodeJS
// By default:
// - It connects its REQ socket to tcp://*:8060
// - It expects a request message from client, and it replies with "World"
// Multiple non-mandatory command-line arguments can be provided in
// the following order:
// - 1st: URL of the broker backend socket.
// - 2nd: Worker identifier (a string).
// - 3rd: Text to be used in its initial connection message.
// - 4th: Text to be used in the replies to be returned to clients.
var zmq = require('zmq'), responder = zmq.socket('req');
// Get the command-line arguments, if any.
var args = process.argv.slice(2);
var backendURL = 'tcp://localhost:8060';
var myID = 'NONE';
var connText = 'id';
var replyText = 'World';
//Set the worker identity to the connection.
//Note that a random ID is assigned by default.
//Thus, when no command-line arguments are given,
//no identity must be set.
if (myID != 'NONE'){
  responder.identity = myID;
}
// Connect to the broker backend socket.
responder.connect(backendURL);
// Process each incoming request.
responder.on('message', function(client, delimiter, msg) {
  setTimeout(function() {
    responder.send([client,'',replyText]);
  }, 1000);
});
//This is the first message sent by a worker.
//Since this "responder" socket has been connected
//to a ROUTER socket, ZeroMQ will prepend the identity
//of the worker to every sent message. That identity
//is used by the broker to "register" this
//worker in its appropriate data structures.
responder.send(connText);

// worker.js
// It assumes that requests only carry an integer value.
// It returns the double of the incoming value.

// Import the zmq module.
var zmq = require('zmq');

// Check whether we have received the URL as an argument.
if (process.argv.length != 3) {
  console.error("The broker URL should be given as an argument!!");
  process.exit(1);
}
// Get the broker URL.
var url = process.argv[2];
console.log("Worker: The broker URL is %s", url);

// Create the REP socket.
var rep = zmq.socket('rep');
// Connect to the broker.
rep.connect(url);

// Handle the received requests.
rep.on('message', function(msg) {
  // Get the incoming value.
  var value = parseInt(msg);
  // Double it!
  value *= 2;
  // Print the reply.
  console.log("Reply: %d", value);
  // Send the reply.
  rep.send(value.toString());
});

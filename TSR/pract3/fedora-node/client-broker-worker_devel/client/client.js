// client.js
// Client process. It sends a random integer value to 
// the servers, and it prints the returned result.

// Import the zmq module.
var zmq = require('zmq');
// Count the number of replies.
var numReplies = 0;
// Total number of requests.
const reqs = 10;

// Check whether we have received the URL as an argument.
if (process.argv.length != 3) {
  console.error("The broker URL should be given as an argument!!");
  process.exit(1);
}
// Get the broker URL.
var url = process.argv[2];
console.log("Broker URL is %s.", url);
var req = zmq.socket('req');
// Connect to the broker.
req.connect(url);

// Handle the received replies.
req.on('message', function(msg) {
	// Get the reply value.
	var value = parseInt(msg);
	// Print the value.
	console.log("Returned value: %d", value);
	// Check whether we should terminate.
	if (++numReplies == reqs)
		process.exit(3);
});

// Send a sequence of 10 requests
for (var i = 0; i < reqs; i++) {
	// Generate a random integer value in the range 1..100
	var value = Math.floor(Math.random()*100 + 1);
	// Print the request.
	console.log("Request: %d", value);
	// Send it.
	req.send(value.toString());
}

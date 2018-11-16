// File Act7remove.js
// This is a simple REMOVE client for the Act7's file server.
// The port number and host name to be used by the server should be passed as arguments from the command line.
// Requests and replies are received and sent using TCP channels.

var net = require('net');
var fs = require('fs');
// Default port number.
var port = 9000;
var host = 'localhost';

// We need at least one argument (the file name). If not given,
// print usage information.
if (process.argv.length==2) {
	console.log( "Usage:" );
	console.log( "\tnode Act7remove filename [port] [hostname]" );
	process.exit(1);
}

// Get command line arguments.
if (process.argv.length > 3)
	port = process.argv[3];
if (process.argv.length > 4)
	host = process.argv[4];
filename = process.argv[2];

// Connect to server.
var client = net.connect(port, host,
	// Connection listener.
	function(c) {
		console.log("Client connected!");
	} );

// Build an appropriate message
// and send it to the server.
var msg = {type:'REMOVE', name: filename};
var m = JSON.stringify(msg);
client.write(m);

// On reply reception...
client.on('data', function(m) {
	var msg = JSON.parse(m);
	if (msg.type=='OK') {
		console.log("Remove successfully managed.");
		client.end();
		process.exit(0);
	} else {
		console.log("Error: %s", msg.data);
		client.end();
		process.exit(2);
	}
}  // End of callback.
); // End of on() call.

client.on('end', function() {
	console.log("Connection ended.");
	process.exit(3);
}
);

client.on('error', function(e) {
	console.log( "%s", e );
	process.exit(4);
}
);

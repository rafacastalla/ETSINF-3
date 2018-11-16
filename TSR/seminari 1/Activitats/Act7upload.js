// File Act7upload.js
// This is a simple UPLOAD client for the Act7's file server.
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
	console.log( "\tnode Act7upload filename [port] [hostname]" );
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

// Read the specified file and send it to server.
fs.readFile(filename,
	// readFile() callback.
	function(err,contents) {
		if (err) {
			// Problems reading file...
			// Print an error message in the client.
			console.log("Unable to read file %s. %s",
				filename, err);
			// Close the connection to the server.
			client.end();
			// Terminate client.
			process.exit(1);
		} else {
			// Build an appropriate message with the file contents
			// and send it to the server.
			var msg = {type:'UPLOAD', name: filename, data: contents.toString()};
			var m = JSON.stringify(msg);
			client.write(m);
		}
	} // End of callback.
) // End of readFile() call.

// On reply reception...
client.on('data', function(m) {
	var msg = JSON.parse(m);
	if (msg.type=='OK') {
		console.log("Upload successfully managed.");
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

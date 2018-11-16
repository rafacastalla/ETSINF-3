// File Act7server.js
// This is a simple file server that understands these requests:
// - DOWNLOAD: Receives the name of a file whose contents should be returned in the reply message.
// - UPLOAD: Receives the name and contents of a file that should be stored in the server directory.
// - REMOVE: Removes a given file if its name exists in the current directory.
// The port number to be used by the server should be passed as an argument from the command line.
// Requests and replies are received and sent using TCP channels.

var net = require('net');
var fs = require('fs');
// Default port number.
var port = 9000;

// Check command line arguments.
if (process.argv.length > 2)
	port = process.argv[2];

// Create the server.
var server = net.createServer( function(c) {
	console.log("Server connected!");
	// Manage end events.
	c.on("end", function() {
		console.log("Server disconnected!");
	});
	// Manage message receptions.
	c.on("data", function(m) {
		// Get the message object.
		var msg = JSON.parse(m);
		switch (msg.type) {
		// Download management.
		case 'DOWNLOAD':
			// Read the file named in the request message.
			fs.readFile(msg.name, 
				// readFile() callback.
				function(err,result) {
					var msg2 = {};
					// If error, print an error message at the server's
					// console and return an error reply.
					if (err) {
						console.log( "%s trying to apply %s on %s",
							err, msg.type, msg.name );
						msg2 = { type:'ERROR', data:err.code };
					// Otherwise, print a message and return an OK reply.
					} else {
						console.log( "%s successfully applied on %s",
							msg.type, msg.name );
						msg2 = { type:'OK', data: result.toString() };
					}
					// Build and send the reply message.
					var m2 = JSON.stringify(msg2);
					c.write(m2);
				} // End of callback.
			); // End of writeFile() call.
			break;
		// Upload management.
		case 'UPLOAD':
			// Write the received file contents in the local directory.
			fs.writeFile(msg.name, msg.data,
				// writeFile() callback.
				function(err,result) {
					var msg2 = {};
					// If error, print an error message at the server's
					// console and return an error reply.
					if (err) {
						console.log( "%s trying to apply %s on %s",
							err, msg.type, msg.name );
						msg2 = { type:'ERROR', data:err.code };
					// Otherwise, print a message and return an OK reply.
					} else {
						console.log( "%s successfully applied on %s",
							msg.type, msg.name );
						msg2 = { type:'OK' };
					}
					// Build and send the reply message.
					var m2 = JSON.stringify(msg2);
					c.write(m2);
				} // End of callback.
			); // End of writeFile() call.
			break;
		// Remove management.
		case 'REMOVE':
			// Remove the file whose name is received in this message.
			// Not implemented yet!!
			break;
		};
	});
	// Manage errors on the current connection.
	c.on("error", function(e) {
		console.log("Error: %s", e);
	});
}); // End of createServer();

// Listen to the given port.
server.listen(port, function() {
	console.log("Server bound to port %s", port );
});

// If any error arises in this socket, report it.
server.on("error", function(e) {
	console.log("Server error: %s", e.code);
});



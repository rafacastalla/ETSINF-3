// File Act7serverPromise.js
// This is a simple file server that understands these requests:
// - DOWNLOAD: Receives the name of a file whose contents should be returned in the reply message.
// - UPLOAD: Receives the name and contents of a file that should be stored in the server directory.
// - REMOVE: Removes a given file if its name exists in the current directory.
// The port number to be used by the server should be passed as an argument from the command line.
// Requests and replies are received and sent using TCP channels.
// This variant uses promises instead of callbacks, when possible.

var net = require('net');
var fs = require('fs');
var bb = require('bluebird');
// Default port number.
var port = 9000;

// Check command line arguments.
if (process.argv.length > 2)
	port = process.argv[2];

// Create promises from the required fs functions.
writeFilePromise = bb.promisify(fs.writeFile);
readFilePromise = bb.promisify(fs.readFile);

// Create the server.
var server = net.createServer( function(c) {
	// This is the connection listener function...
	// Print a first message when the connection is set.
	console.log("Server connected!");
	// Manage end events.
	c.on("end", function() {
		console.log("Server disconnected!");
	});
	// Manage message receptions.
	c.on("data", function(m) {
		// Get the message object.
		var msg = JSON.parse(m);
		// onSuccess callback.
		function success(contents) {
			// REMOVE and UPLOAD requests do not generate any data to be passed to
			// the onSuccess handler but DOWNLOAD passes the file contents in 
			// this callback "contents" parameter. Since we want to convert it to 
			// a string, we should check whether it is undefined or not.
			if (typeof contents=='undefined')
				contents='';
			var msg2 = {};
			console.log("%s successfully applied on %s", msg.type, msg.name);
			msg2 = { type: 'OK', name: msg.name, data: contents.toString() };
			var m = JSON.stringify(msg2);
			c.write(m);
		}
		// onError callback.
		function onError(er) {
			var msg2 = {};
			console.log("%s trying to apply %s on %s", er.message, msg.type, msg.name);
			msg2 = { type: 'ERROR', data: er.message };
			var m = JSON.stringify(msg2);
			c.write(m);
		}
		switch (msg.type) {
		case 'DOWNLOAD':
			// Read the file contents onto the reply message.
			readFilePromise(msg.name).
				then( success, onError );
			break;
		// Upload management.
		case 'UPLOAD':
			// Write the received file contents in the local directory.
			writeFilePromise(msg.name, msg.data).
				then( success, onError );
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



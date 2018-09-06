// myworker server in NodeJS
var zmq = require('zmq')
var responder = zmq.socket('req');

var args = process.argv.slice(2);

var backendURL = args[0] || 'tcp://localhost:8060';
var myID = args[1] || 'NONE';
var connText = args[2] || 'id';
var replyText = args[3] || 'World';

var verbose = false;
if(args[4] == 'verbose') verbose = true;

if (myID != 'NONE')
	responder.identity = myID;

responder.connect(backendURL);
if (verbose) console.log('Worker (%s) connected to %s', myID, backendURL);

responder.on('message', function(client, delimiter, msg) {
	if (verbose) { console.log('Worker (%s) has received request "%s" from client (%s)', myID, msg, client); }

	setTimeout(function() {
		responder.send([client, '', replyText]);
		if (verbose) console.log('Worker (%s) has sent its reply "%s"', myID, replyText);
	}, 1000);
});

responder.send(connText);
if (verbose) console.log('Worker (%s) has sent its first connection message: "%s"', myID, connText);
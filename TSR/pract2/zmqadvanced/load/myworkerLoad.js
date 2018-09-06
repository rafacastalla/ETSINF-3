// myworker server in NodeJS
var zmq = require('zmq')
var responder = zmq.socket('req');
var aux = require('./auxfunctions1718.js');

// node myworker.js tcp://localhost:8060 W1 READY REPLY verbose
var args = process.argv.slice(2);
if ( args.length < 5 ) console.log('WARNING: example of invocation ("node myworker.js tcp://localhost:8060 W1 READY REPLY verbose")');

var backendURL = args[0] || 'tcp://localhost:8060';
var myID = args[1] || 'NONE';
var connText = args[2] || 'id';
var replyText = args[3] || 'World';
var verbose = false;
if (args[args.length - 1] == 'verbose') verbose = true; args.pop();

if (myID != 'NONE') responder.identity = myID;

responder.connect(backendURL);
if (verbose) console.log('Worker (%s) connected to %s', myID, backendURL);

responder.on('message', function(client, delimiter, msg) {
	
	if (verbose) console.log("Message recived from broker.");
	if (verbose) aux.showMessage( [client, delimiter, msg] );
	
	setTimeout(function() {

		var m = [ client, '', replyText, aux.getLoad() ];

		responder.send(m);
		
		if (verbose) console.log("Sending message to broker.");
		if (verbose) aux.showMessage(m);

	}, 1000);
});

responder.send( [ connText, aux.getLoad() ] );
if (verbose) console.log("Message (%s) send to broker, worker wating work.", connText);

setTimeout(function() {
	if (verbose) console.log("Worker (%s) closed.", myID);
	process.exit(0);
}, 120000);
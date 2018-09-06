// myworker server in NodeJS
var zmq = require('zmq')
var responder = zmq.socket('req');
var log = zmq.socket('push');
var util = require('util');

// node myworker.js tcp://localhost:8060 W1 ready T1 A tcp://localhost:8066

var args = process.argv.slice(2);
var backendURL = args[0] || 'tcp://localhost:8060';
var myID = args[1] || 'NONE';
var connText = args[2] || 'id';
var replyText = args[3] || 'World';
var classID = args[4] || 'B';
var loggerURL = args[args.length-1] || 'tcp://localhost:8066';

if (myID != 'NONE')
	responder.identity = myID;

responder.connect(backendURL);
log.connect(loggerURL);

log.send( util.format('Worker (%s) connected to %s\n', myID, backendURL) );

responder.on('message', function(client, delimiter, msg) {

	log.send( util.format('Worker (%s) has received request "%s" from client (%s)\n', myID, msg, client) );

	setTimeout(function() {

		responder.send([client, '', replyText, classID]);
		log.send( util.format('Worker (%s) has sent its reply "%s"\n', myID, replyText) );

	}, 1000);

});

responder.send( [connText, classID] );
log.send( util.format('Worker (%s) has sent its first connection message: "%s" on group: "%s"\n', myID, connText, classID) );
// myclient in NodeJS
var zmq = require('zmq')
var requester = zmq.socket('req');
var log = zmq.socket('push');
var util = require('util');

// node my10client.js tcp://localhost:8059 C1 M1 A tcp://localhost:8066
var args = process.argv.slice(2);

var brokerURL = args[0] || 'tcp://localhost:8059';
var myID = args[1] || 'NONE';
var myMsg = args[2] || 'Hello';
var classID = args[3] || 'B';
var loggerURL = args[args.length-1] || 'tcp://localhost:8066';

var cont = 0;
var nMessages = 10;

if (myID != 'NONE')
	requester.identity = myID;

requester.connect(brokerURL);
log.connect(loggerURL);

log.send( util.format('Client (%s) with class "%s" connected to %s\n', myID, classID, brokerURL) );

requester.on('message', function(msg) {
	
	log.send( util.format('Client (%s) has received reply "%s"\n', myID, msg.toString()) );
	
	cont++;
	if (cont === nMessages)	process.exit(0);
	else requester.send(  [ myMsg, classID ] );
});

requester.send( [ myMsg, classID ] );
log.send( util.format('Client (%s) sending request "%s" of class "%s"\n', myID, myMsg, classID) );
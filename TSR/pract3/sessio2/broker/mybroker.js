// ROUTER-ROUTER request-reply broker in NodeJS

//var aux = require('./auxfunctions1718.js');
// node mybroker.js 8059 8060 A B C D tcp://localhost:8066
var zmq = require('zmq');
var frontend = zmq.socket('router');
var backend = zmq.socket('router');
var log = zmq.socket('push');
var util = require('util');

var args = process.argv.slice(2);
var fePortNbr = args[0] || 8059;
var bePortNbr = args[1] || 8060;
var loggerURL = args[args.length-1] || 'tcp://localhost:8066';

var workers = [];
var clients = [];
var requestsPerWorker = [];
var classIDs = [];
var busyWorkers = [];
// Array of busy workers. Each slot contains an array with all
// the segments being needed for resending the current message
// being processed by that worker.

var cont = 0;
for (var i = 2; i < args.length-2; i++) {
	classIDs[cont] = args[i];
	cont++;
}

for(var i in classIDs){
	workers[classIDs[i]] = [];
	clients[classIDs[i]] = [];
}

// Reply awaiting period, in ms.
const answerInterval = 2000;


frontend.bindSync('tcp://*:'+fePortNbr);
backend.bindSync('tcp://*:'+bePortNbr);
log.connect(loggerURL);

frontend.on('message', function() {
	var args = Array.apply(null, arguments);
	var classID = args.pop();

	log.send( util.format('Message recived from client (%s) on class (%s).\n', args[0], classID) );
	
	if( !clients[classID] ) { clients[classID] = []; }
	if( !workers[classID] ) { workers[classID] = []; }

	sendRequest(args, classID);

	if (workers[classID].length > 0) {
		var myWorker = workers[classID].shift();
		var m = [myWorker, ''].concat(args);
		
		log.send( util.format('Sending request (%s) to worker (%s) through backend.\n', m[4], m[0]) );
		backend.send(m);

		if( !requestsPerWorker[myWorker] ) requestsPerWorker[myWorker] = 1;
		else requestsPerWorker[myWorker]++;

	} else {
		clients[classID].push( {id:args[0], msg:args.slice(2)} );
	}
});

function processPendingClient(workerID, classID) {

	if (clients[classID].length>0) {
		var nextClient = clients[classID].shift();
		var msg = [workerID, '', nextClient.id, ''].concat(nextClient.msg);

		sendToWorker(msg, classID);
		
		log.send( util.format('Sending request (%s) to worker (%s) through backend.\n', msg[4], msg[0]) );
		backend.send(msg);

		if( !requestsPerWorker[workerID] ) requestsPerWorker[workerID] = 1;
		else requestsPerWorker[workerID]++;

		return true;

	} else { return false; }
}

backend.on('message', function() {
	var args = Array.apply(null, arguments);
	var classID = args.pop();

	log.send( util.format('Message recived from worker (%s) on class (%s).\n', args[0], classID) );

	if( !clients[classID] ) { clients[classID] = []; }
	if( !workers[classID] ) { workers[classID] = []; }

	if (args.length == 3) {

		if ( !processPendingClient(args[0], classID) ){
			workers[classID].push(args[0]);
			log.send( util.format('New worker (%s) connected.\n', args[0]) );
		}

	} else {
		var workerID = args[0];

		// Cancel the reply timeout.
		if(busyWorkers[workerID]) clearTimeout(busyWorkers[workerID].timeout);
		
		args = args.slice(2);
		
		frontend.send(args);
		log.send( util.format('Sending answer (%s) to client (%s) through frontend.\n', args[2], args[0]) );
		
		if (!processPendingClient(workerID, classID))
			workers[classID].push(workerID);
	}
});

// Send a message to a worker.
function sendToWorker(msg, classID) {
	
	//var classID = id.toString();
	var myWorker = msg[0];
	// Send the message.
	backend.send(msg);
	// Initialise busyWorkers slot object.
	busyWorkers[myWorker] = {};
	// Recall that such message has been sent.
	busyWorkers[myWorker].msg = msg.slice(2);
	// Set a timeout of its response.
	busyWorkers[myWorker].timeout = setTimeout( generateTimeoutHandler(myWorker, classID), answerInterval );
}

// Function that sends a message to a worker, or
// holds the message if no worker is available now.
// Parameter 'args' is an array of message segments.
function sendRequest(args, classID) {

	if (workers[classID].length > 0) {
		var myWorker = workers[classID].shift();
		var m = [myWorker, ''].concat(args);
		sendToWorker(m, classID);

	} else {
		clients[classID].push( {id: args[0],msg: args.slice(2)} );
	}
}

// Function that creates the handler for a reply
// timeout.
function generateTimeoutHandler(workerID, classID) {
	return function() {
		
		if( busyWorkers[workerID] ){
			// Get the message to be resent.
			var msg = busyWorkers[workerID].msg;
			// Remove that slot from the busyWorkers array.
			delete busyWorkers[workerID];
			// Resend that message.
			sendRequest(msg, classID);
		}
		
	}
}

function showStatistics() {
	var totalAmount = 0;
	
	log.send( util.format('Current amount of requests served by each worker: \n') );
	
	for (var i in requestsPerWorker) {
		log.send( util.format(' %s : %d requests\n', i, requestsPerWorker[i]) );
		totalAmount += requestsPerWorker[i];
	}

	log.send( util.format('Requests already served (total): %d\n', totalAmount) );
	process.exit(0);
}

process.on('SIGINT', showStatistics);



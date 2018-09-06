// ROUTER-ROUTER request-reply broker in NodeJS

var aux = require('./auxfunctions1718.js');
var zmq = require('zmq');

var args = process.argv.slice(2);

var broker1 = zmq.socket('dealer')
var backend = zmq.socket('router');

var fePortNbr = args[0] || 8000;
var bePortNbr = args[1] || 8060;

var verbose = false;
if(args[2] == 'verbose') verbose = true;

var workers = [];
var clients = [];

var requestsPerWorker = [];

broker1.connect('tcp://127.0.0.1:'+fePortNbr);
backend.bindSync('tcp://*:'+bePortNbr);

broker1.on('message', function(c, s, m) {
	if (verbose) console.log("Client:" + c + " S:" + s + " Msg:" + m);
	
	if (workers.length > 0) {
		var myWorker = workers.shift();
		var msg = [myWorker, "", c, s, m];
		
		if (verbose) console.log('The message for worker is: ' + m);
		if (verbose) console.log("W:"+msg[0] + " D1:"+msg[1] + " C:"+msg[2] + " S2:"+msg[3] + " M:"+msg[4]);
		
		backend.send(msg);
		if( !requestsPerWorker[myWorker] ) requestsPerWorker[myWorker] = 1;
		else requestsPerWorker[myWorker]++;

	} else {
		clients.push( {id:c, msg:m} );
	}
});

function processPendingClient(workerID) {
	if (clients.length>0) {
		var nextClient = clients.shift();
		var m = [workerID,'',nextClient.id,''].concat(nextClient.msg);
		
		if (verbose) { 
			console.log('Sending client (%s) request to worker (%s) through backend.', m[2], m[0]);
			aux.showMessage(m);
		}

		backend.send(m);
		if( !requestsPerWorker[workerID] ) requestsPerWorker[workerID] = 1;
		else requestsPerWorker[workerID]++;

		return true;

	} else { return false; }
}

backend.on('message', function() {
	var args = Array.apply(null, arguments);
	
	if (args.length == 3) {
		if (!processPendingClient(args[0]))
			workers.push(args[0]);
	} else {
		var workerID = args[0];
		args = args.slice(2);

		var msg = [args[0], args[1], args[2]]

		broker1.send(msg);
		
		if (!processPendingClient(workerID))
			workers.push(workerID);
	}
});

function showStatistics() {
	var totalAmount = 0;
	
	console.log('Current amount of requests served by each worker:');
	
	for (var i in requestsPerWorker) {
		console.log(' %s : %d requests', i, requestsPerWorker[i]);
		totalAmount += requestsPerWorker[i];
	}

	console.log('Requests already served (total): %d', totalAmount);
	process.exit(0);
}

process.on('SIGINT', showStatistics);



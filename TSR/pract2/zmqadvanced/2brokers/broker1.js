// ROUTER-ROUTER request-reply broker in NodeJS

var aux = require('./auxfunctions1718.js');
var zmq = require('zmq');

var args = process.argv.slice(2);

var frontend = zmq.socket('router')
var broker2 = zmq.socket('dealer');

var fePortNbr = args[0] || 8059;
var bePortNbr = args[1] || 8000;

var verbose = false;
if(args[2] == 'verbose') verbose = true;

var workers = [];
var clients = [];

var requestsPerClient = [];

frontend.bindSync('tcp://*:'+fePortNbr);
broker2.bindSync('tcp://127.0.0.1:'+bePortNbr);

frontend.on('message', function(c, s, m) {
	// ARGS = idClient "" msg
	if (verbose) console.log('The client (%s) request.', c);
	var m = [c, s , m];
	broker2.send(m);

	if( !requestsPerClient[c] ) requestsPerClient[c] = 1;
	else requestsPerClient[c]++;

});

broker2.on('message', function(c, s, m) {
	if (verbose) console.log('Replay to client (%s). ', c);
	frontend.send([c, s, m]);
});

function showStatistics() {
	var totalAmount = 0;
	
	console.log('Current amount of requests served by each worker:');
	
	for (var i in requestsPerClient) {
		console.log(' %s : %d requests', i, requestsPerClient[i]);
		totalAmount += requestsPerClient[i];
	}

	console.log('Requests already served (total): %d', totalAmount);
	process.exit(0);
}

process.on('SIGINT', showStatistics);



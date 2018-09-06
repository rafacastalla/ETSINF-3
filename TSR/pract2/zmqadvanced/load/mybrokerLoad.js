// ROUTER-ROUTER request-reply broker in NodeJS
var zmq = require('zmq')
var frontend = zmq.socket('router')
var backend = zmq.socket('router');
var aux = require('./auxfunctions1718.js');

// node mybroker.js 8059 8060 verbose
var args = process.argv.slice(2);
if ( args.length < 3 ) console.log('WARNING: example of invocation ("node mybroker.js 8059 8060 verbose")');

var fePortNbr = args[0] || 8059;
var bePortNbr = args[1] || 8060;
var verbose = false;
if (args[args.length -1] == 'verbose') verbose = true; args.pop();

var workers = [];
var clients = [];
var requestPerWork = [];

frontend.bindSync('tcp://*:'+fePortNbr);
backend.bindSync('tcp://*:'+bePortNbr);

if (verbose) console.log("Server lisening... (frontend: " + fePortNbr + " backend: " + bePortNbr + " )");

frontend.on('message', function() {
	var args = Array.apply(null, arguments);

	if (verbose) console.log("New message recived from client.");
	if (verbose) aux.showMessage(args);
	
	if (workers.length > 0) {
		
		var myWorker = workers.shift().w;
		var m = [ myWorker, '' ].concat(args);
		
		backend.send(m);

		if (verbose) console.log("Sending message to worker.");
		if (verbose) aux.showMessage(m);

	} else{

		clients.push( { id:args[0], msg:args.slice(2) } );

		if (verbose) console.log("Saving message of client.");
		if (verbose) console.log(clients);
	}
});

function processPendingClient() {
	
	if (clients.length > 0) {
		
		var nextClient = clients.shift();
		
		if (verbose) console.log("Giving message from list of clients.");
		if (verbose) console.log(nextClient);

		var workerID = workers.shift().w;

		var m = [ workerID, '', nextClient.id, '' ].concat(nextClient.msg);
		backend.send(m);

		if (verbose) console.log("Sending message to worker.");
		if (verbose) aux.showMessage(m);
	}
}

backend.on('message', function() {
	var args = Array.apply(null, arguments);

	if (verbose) console.log("New message recived from worker.");
	if (verbose) aux.showMessage(args);

	var worker = { w:args[0], c:args.pop() };
	guardarWorker(worker);

	if (verbose) console.log("Saving worker.");
	if (verbose) mostrar();
	
	
	if (args.length == 3) {

		requestPerWork[worker.w] = 0;

		processPendingClient();

	} else {

		requestPerWork[worker.w]++;

		args = args.slice(2);
		frontend.send(args);

		if (verbose) console.log("Sending reply to client.");
		if (verbose) aux.showMessage(args);
		
		processPendingClient();
	}
});

function guardarWorker(worker){
	var carrega = worker.c;

	for (var i = 0; i < workers.length; i++) {
		if ( workers[i].c > carrega ) break;
	}

	workers.splice(i, 0, worker);
}

function mostrar(){
	for (var i = 0; i < workers.length; i++) {
		console.log( workers[i].c.toString() );
	}
}

function showStatistics() {
	var totalAmount = 0;

	console.log('Current amount of requests served by each worker:');
	
	for (var i in requestPerWork) {
		console.log(' %s : %d requests', i, requestPerWork[i]);
		totalAmount += requestPerWork[i];
	}

	console.log('Requests already served (total): %d', totalAmount);
	process.exit(0);
}

process.on('SIGINT', showStatistics);
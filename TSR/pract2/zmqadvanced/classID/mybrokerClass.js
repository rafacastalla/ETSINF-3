var zmq = require('zmq'), frontend = zmq.socket('router'), backend = zmq.socket('router');
var aux = require("./auxfunctions1718.js");

var args = process.argv.slice(2);

var fePortNbr = args[0] || 8059;
var bePortNbr = args[1] || 8060;

var workers = [];
var clients = [];
var classIDs = [];

var verbose = false;
if(args[2] == 'verbose') verbose = true;

var cont = 0;
for (var i = 2; i < args.length-1; i++) {
	classIDs[cont] = args[i];
	cont++;
}

if(verbose) console.log(classIDs);

for(var i in classIDs){
	workers[classIDs[i]] = [];
	clients[classIDs[i]] = [];
}

if(verbose) console.log(clients);console.log(workers);

var requestsPerWorker = [];

frontend.bindSync('tcp://*:'+fePortNbr);
backend.bindSync('tcp://*:'+bePortNbr);

frontend.on('message', function() {

  var args = Array.apply(null, arguments);
  var classID = args.pop();

  if(verbose) console.log(classID.toString());
	if( !clients[classID] ) clients[classID] = [];
	if( !workers[classID] ) workers[classID] = [];
	if(verbose) console.log(clients);
	if(verbose) console.log(workers);

  if (workers[classID].length > 0) {

    var myWorker = workers[classID].shift();
    var m = [myWorker,''].concat(args);

    if (verbose) console.log('The message for worker is: ' + m);

    backend.send(m);

    if( !requestsPerWorker[myWorker] ) requestsPerWorker[myWorker] = 1;
		else requestsPerWorker[myWorker]++;

  } else
      clients[classID].push({id: args[0],msg: args.slice(2)});
});

function processPendingClient(workerID, classID) {
if(verbose) console.log(clients[classID]); console.log(workerID + classID);

  if (clients[classID].length>0) {

    var nextClient = clients[classID].shift();
    var m = [workerID,'',nextClient.id,''].concat(nextClient.msg);

    if (verbose) {
			console.log('Sending client (%s) request to worker (%s) through backend.', m[2], m[0]);
			aux.showMessage(m);
		}

    backend.send(m);
    if( !requestsPerWorker[workerID] ) requestsPerWorker[workerID] = 1;
		else requestsPerWorker[workerID]++;

    return true;

  } else{
      return false;
  }
}

backend.on('message', function() {
	if(verbose) console.log('Args worker:'); console.log(arguments);
	var args = Array.apply(null, arguments);
	if(verbose) console.log('Args worker:'); console.log(args);

	var classID = args.pop();

	if(verbose) console.log(classID.toString());

	if( !workers[classID] ) workers[classID] = [];
	if( !clients[classID] ) clients[classID] = [];
	if(verbose) console.log(workers);
	if(verbose) console.log(clients);

	if(verbose) console.log('Args worker:'); console.log(args);

	if (args.length == 3) {
		console.log('entra');
		if (!processPendingClient(args[0], classID)){
			console.log('entra2: ' + args[0].toString());
			workers[classID].push(args[0]);
			console.log(workers);
		}

	} else {
		var workerID = args[0];
		args = args.slice(2);
		frontend.send(args);

		if (!processPendingClient(workerID, classID))
			workers[classID].push(workerID);
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

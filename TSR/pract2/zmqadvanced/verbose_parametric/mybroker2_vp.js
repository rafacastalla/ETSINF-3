var zmq = require('zmq'), frontend = zmq.socket('router'), backend = zmq.socket('router');
var aux = require("./auxfunctions1718.js");

var args = process.argv.slice(2);

var fePortNbr = args[0] || 8059;
var bePortNbr = args[1] || 8060;

var workers = [];
var clients = [];

var requestsPerWorker = [];

var verbose = false;
if(args[2] == 'verbose') verbose = true;

frontend.bindSync('tcp://*:'+fePortNbr);
backend.bindSync('tcp://*:'+bePortNbr);

frontend.on('message', function() {

  var args = Array.apply(null, arguments);
  if (workers.length > 0) {

    var myWorker = workers.shift();
    var m = [myWorker,''].concat(args);

    if (verbose) console.log('The message for worker is: ' + m);

    backend.send(m);

    if( !requestsPerWorker[myWorker] ) requestsPerWorker[myWorker] = 1;
		else requestsPerWorker[myWorker]++;

  } else
      clients.push({id: args[0],msg: args.slice(2)});
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

  } else{
      return false;
  }
}

backend.on('message', function() {

var args = Array.apply(null, arguments);
if (args.length == 3) {
  if (!processPendingClient(args[0])){
      workers.push(args[0]);
  }
} else {
    var workerID = args[0];
    args = args.slice(2);
    frontend.send(args);

    if (!processPendingClient(workerID)){
      workers.push(workerID);
    }
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

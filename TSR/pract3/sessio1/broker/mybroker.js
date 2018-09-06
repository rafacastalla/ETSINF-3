// ROUTER-ROUTER request-reply broker in NodeJS

var zmq = require('zmq');

var frontend = zmq.socket('router')
var backend = zmq.socket('router');

var fePortNbr = 8059;
var bePortNbr = 8060;

var workers = [];
var clients = [];

frontend.bindSync('tcp://*:'+fePortNbr);
backend.bindSync('tcp://*:'+bePortNbr);

frontend.on('message', function() {
	var args = Array.apply(null, arguments);

	console.log("Client conected.");
	
	if (workers.length > 0) {
		var myWorker = workers.shift();
		var m = [myWorker,''].concat(args);
		backend.send(m);
	} else {
		clients.push( {id: args[0],msg: args.slice(2)} );
	}
});

function processPendingClient(workerID) {
	if (clients.length>0) {
		var nextClient = clients.shift();
		var m = [workerID,'',nextclient.id,''].concat(nextClient.msg);

		backend.send(m); 
		return true;

	} else { return false; }
}

backend.on('message', function() {
	var args = Array.apply(null, arguments);

	console.log("Worker conected.")
	
	if (args.length == 3) {
		if (!processPendingClient(args[0]))
			workers.push(args[0]);
	} else {
		var workerID = args[0];
		args = args.slice(2);
		frontend.send(args);
		
		if (!processPendingClient(workerID))
			workers.push(workerID);
	}
});
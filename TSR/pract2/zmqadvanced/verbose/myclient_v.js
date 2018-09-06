var zmq = require('zmq')
var requester = zmq.socket('req');

var args = process.argv.slice(2);

var brokerURL = 'tcp://localhost:8059';
var myID = 'NONE';
var myMsg = 'Hello';

var verbose = false;
if(args[3] == 'verbose') verbose = true;

if (myID != 'NONE')
	requester.identity = myID;

requester.connect(brokerURL);
if (verbose) console.log('Client (%s) connected to %s', myID, brokerURL);

requester.on('message', function(msg) {
	if (verbose) console.log('Client (%s) has received reply "%s"', myID, msg.toString());
	process.exit(0);
});

requester.send(myMsg);

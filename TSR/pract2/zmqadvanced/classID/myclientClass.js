var zmq = require('zmq')
var requester = zmq.socket('req');

var args = process.argv.slice(2);

var brokerURL = args[0] || 'tcp://localhost:8059';
var myID = args[1] || 'NONE';
var myMsg = args[2] || 'Hello';
var classID = args[3] || 'B';

var verbose = false;
if(args[4] == 'verbose') verbose = true;

if (myID != 'NONE')
	requester.identity = myID;

requester.connect(brokerURL);
if (verbose) console.log('Client (%s) connected to %s', myID, brokerURL);

requester.on('message', function(msg) {
	if (verbose) console.log('Client (%s) has received reply "%s"', myID, msg.toString());
	process.exit(0);
});
var m =[myMsg,classID];
requester.send(m);

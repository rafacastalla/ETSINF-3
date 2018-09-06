// myclient in NodeJS
// By default:
// - It connects REQ socket to tcp://localhost:8059
// - It sends "Hello" to server and expects "World" back
// Using the command line arguments, that default behaviour
// may be changed. To this end, those arguments are interpreted
// as follows:
// - 1st: URL of the broker frontend socket.
// - 2nd: Client ID, to tag the connection to the frontend router
//socket of the broker.
// - 3rd: String to be sent to the servers (i.e., worker agents).
var zmq = require('zmq'), requester = zmq.socket('req');
// Command-line arguments.
var args = process.argv.slice(2);
// Get those arguments.
var brokerURL = 'tcp://localhost:8059';
var myID = 'NONE';
var myMsg = 'Hello';
// Set the connection ID. This must be done before the
// connect() method is called.
if (myID != 'NONE'){
  requester.identity = myID;
}
// Connect to the frontend ROUTER socket of the broker.
requester.connect(brokerURL);
// Print trace information.
console.log('Client (%s) connected to %s', myID, brokerURL)
// A single reply is expected...
requester.on('message', function(msg) {
  console.log('Client (%s) has received reply "%s"', myID, msg.toString());
  process.exit(0);
});
// Send a single message.
requester.send(myMsg);
// Print trace information.
console.log('Client (%s) has sent its message: "%s"', myID, myMsg);

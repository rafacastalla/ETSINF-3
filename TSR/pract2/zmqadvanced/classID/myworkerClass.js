var zmq = require('zmq'), responder = zmq.socket('req');

var args = process.argv.slice(2);
var backendURL = args[0] || 'tcp://localhost:8060';
var myID = args[1] || 'NONE';
var connText = args[2] || 'id';
var replyText = args[3] || 'World';
var classID = args[4] || 'B';

var verbose = false;
if(args[5] == 'verbose') verbose = true;

if (myID != 'NONE'){
  responder.identity = myID;
}

responder.connect(backendURL);

if (verbose) console.log('Worker (%s) connected to %s', myID, backendURL);

responder.on('message', function(client, delimiter, msg) {
  if (verbose) console.log('Worker (%s) has received request "%s" from client (%s)', myID, msg.toString(), client);
  setTimeout(function() {
    responder.send([client,'',replyText, classID]);
  }, 1000);
  if (verbose) console.log('Worker (%s) has sent its reply "%s"', myID, replyText);

});

var m = [connText, classID];
responder.send(m);
if (verbose) console.log('Worker (%s) has sent its first connection message: "%s" on group: "%s"', myID, connText, classID);

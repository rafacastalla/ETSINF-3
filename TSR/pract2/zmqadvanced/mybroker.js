// ROUTER-ROUTER request-reply broker in Node.js
// It uses a FIFO policy to administer its pending
// clients and available workers.
// Each kind of agent is placed in its corresponding
// array, that is managed as a queue by default.
// - 1st: Port number for its frontend socket (8059)
// - 2nd: Port number for its backend socket (8060)
var zmq = require('zmq'), frontend = zmq.socket('router'), backend = zmq.socket('router');
// Get the command-line arguments.
var args = process.argv.slice(2);
// Port number for the frontend socket.
var fePortNbr = 8059;
// Port number for the backend socket.
var bePortNbr = 8060;
// Array of available workers.
var workers = [];
// Array of pending clients.
var clients = [];

frontend.bindSync('tcp://*:'+fePortNbr);
backend.bindSync('tcp://*:'+bePortNbr);

frontend.on('message', function() {
  // Note that separate message parts come as function arguments.
  var args = Array.apply(null, arguments);
  // Check whether there is any available worker.
  if (workers.length > 0) {
    // Remove the oldest worker from the array.
    var myWorker = workers.shift();
    // Build a multi-segment message.
    // & Send it.
    var m = [myWorker,''].concat(args);
    backend.send(m);
  } else
    // When no available worker exists, save
    // the client ID and message into the clients array.
    clients.push({id: args[0],msg: args.slice(2)});
});

function processPendingClient(workerID) {
  // Check whether there is any pending client.
  if (clients.length>0) {
    // Get the data from the first client and remove it
    // from the queue of pending clients.
    var nextClient = clients.shift();
    //Build the message and send it.
    //Note that a message is an array of segments. Therefore,
    //we should prepend: (a) the worker ID + a delimiter,
    //to choose the worker connection to be used, (b) the client ID +
    //a delimiter, to build the needed context for adequately
    //forwarding its subsequent reply at the worker domain.
    //& Send the message.
    var m = [workerID,'',nextClient.id,''].concat(nextClient.msg);
    backend.send(m);
    // Return true if any client has been found
    return true;
  } else{
    // Return false if no client is there.
    return false;
  }
}

backend.on('message', function() {

var args = Array.apply(null, arguments);
// If this is an initial ID message from a new worker,
// save its identity in the "workers" array...
if (args.length == 3) {
  // It may happen that some clients are already waiting
  // for available workers. If so, serve one of them!
  if (!processPendingClient(args[0])){
      // Otherwise, save this worker as an available one.
      workers.push(args[0]);
  }
  // ...otherwise, return the message to the appropriate
  // client.
} else {
    // Save the worker identity.
    var workerID = args[0];
    // Remove the first two slots (id+delimiter)
    // from the array.
    args = args.slice(2);
    // Send the resulting message to the appropriate
    // client. Its first slot holds the client connection
    // ID.
    frontend.send(args);
    // Check whether any client is waiting for attention.
    // If so, the request from the first one is sent and
    // it is remove from the pending queue.
    // Otherwise, a false value is returned.
    if (!processPendingClient(workerID)){
      // In that case, the worker ID is saved in the
      // queue of available workers.
      workers.push(workerID);
    }
  }
});

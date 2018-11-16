var zmq = require('zmq');

// Save the original socket method, we need it
var socket = zmq.socket;

// Possible states.
const INITIAL = 0;
const MSG = 1;
const ERROR = 2;
const TIMEOUT = 3;


// Create and store the wrapper method
zmq.socket = function(kind) {
    // It uses the original method anyways, to get a zmq socket
    var so = socket.call(zmq, kind);
    
    if (kind == 'req') {
	// We create a holder object. The actual socket will be one
	// of its properties. Thus, the socket can be closed and
	// replaced by a new one.
	var holder = {};

	// Set the automaton state.
	holder.state = INITIAL;
	holder.socket = so;
	holder.request = request;
	// Array of listener functions, one per relevant event.
	holder.listener = [];
	// A single endpoint is considered. Multiple endpoints are
	// difficult to manage, since we will need to close the socket
	// on each timeout event.
	holder.url = "";
	holder.bound = false;
	// Remember the URL being used for the initial connect call.
	holder.connect = function (arg) {
	    holder.url = arg;
	    holder.socket.connect(arg);
	}
	// The same is made for bindSync() and bind(). In this activity
	// only connect() is used, but we try to provide a general solution.
	holder.bindSync = function(arg) {
	    holder.url = arg;
	    holder.bound = true;
	    holder.socket.bindSync(arg);
	}
	holder.bind = function(arg1,arg2) {
	    holder.url = arg1;
	    holder.bound = true;
	    holder.socket.bind(arg1,arg2);
	}
	// The send(), close() and on() method calls are directly forwarded to
	// the actual socket.
	holder.send = function(arg) {
	    holder.socket.send(arg);
	}
	holder.close = function() {
	    holder.socket.close();
	}
	holder.on = function(arg1,arg2) {
	    holder.listener[arg1] = arg2;
	    holder.socket.on(arg1,arg2);
	}
	return holder;
    }
    else return so;
};


// This is the extra method definition required by activity 2
function request() {
    var timer={};
    var that = this; // save the reference to the object
    // First argument is the timeout value
    var tmout = parseInt(arguments[0]);
    // The message segments are all the remaining arguments
    var args = Array.prototype.slice.call(arguments,1);

    // Define the handler for the 'message' event of the underlying zmq socket
    var onResponse = function () {
	// We produce an array out of the argument list
	// and call the 'message' listener with it.
	if (that.listener['message'])
		that.listener['message'](Array.prototype.slice.call(arguments)); 
	// Remove the 'error' listener, if any.
	that.socket.removeListener('error', onError);
	// Clear the timeout.
	clearTimeout(timer);
	// Set the state.
	that.state = MSG;
    };

    // Define the handler for the 'error' event of the underlying zmq socket
    var onError = function () {
	clearTimeout(timer);
	// Do not forget to remove handler for the 'message' event for
	// this invocation
	that.socket.removeListener('message', onResponse);
	// Call the 'error' listener, if any had been registered.
	if (that.listener['error'])
		that.listener['error'](Array.prototype.slice.call(arguments));
	// Set the state.
	that.state = ERROR;
    };

    // Handler for the 'timeout' event.
    function onTimeout() {
      if (that.state != TIMEOUT) {
        // Remove all other listeners.
	that.socket.removeListener('message', onResponse);
	that.socket.removeListener('error', onError);
	// Close the current socket.
	that.socket.close();
	// Create a new one...
	that.socket = socket.call(zmq,'req');
	// ... and rebind or reconnect it.
	if (that.bound==false) {
	    console.log("Reconnecting to " + that.url);
	    that.socket.connect(that.url);
	} else {
	    console.log("Rebinding to " + that.url);
	    that.socket.bindSync(that.url);
	}
	that.state = TIMEOUT;
      }
    };
   
    // Set up the handler for only one message
    this.socket.once('message', onResponse);
    // Set up the handler for only one error
    this.socket.once('error', onError);
    // Set up the handler for the timeout event  
    if (tmout>0) {
	timer = setTimeout( onTimeout, tmout*1000);
    }
    // Send all the message segments
    this.socket.send(args);
}


// exports the zmq object we got (with the extra mods)
module.exports = zmq;

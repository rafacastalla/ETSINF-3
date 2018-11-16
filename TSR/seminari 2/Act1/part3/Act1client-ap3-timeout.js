// Client
var zmq = require('zmq');
var counter = 0;
var rq = zmq.socket('req');
var timerLength = 2000;
var timer = {}
rq.connect('tcp://127.0.0.1:8888');
// The "Hello" string is sent every second.
// Now, the counter value is appended to the string.
setInterval( function() {
    rq.send('Hello '+ ++counter);
}, 1000 );


function handleMsg(msg) {
    clearInterval(timer);
    timer=setInterval(onTimeout, timerLength);
    console.log('Response: ' + msg);
}

timer=setInterval(onTimeout, timerLength);
rq.on('message', handleMsg);

function onTimeout() {
    // In case of timeout, close the current socket.
    rq.close();
    // A new objet is needed. A closed socket cannot
    // be rebound.
    rq=zmq.socket('req');
    console.log('Reconnecting socket!!!');
    rq.connect('tcp://127.0.0.1:8888');
    // Reset the event handlers. This is a new object.
    rq.on('message', handleMsg);
}

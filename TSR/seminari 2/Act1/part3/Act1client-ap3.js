// Client
var zmq = require('zmq');
var counter = 0;
var rq = zmq.socket('req');
rq.connect('tcp://127.0.0.1:8888');
// The "Hello" string is sent every second.
// Now, the counter value is appended to the string.
setInterval( function() {
    rq.send('Hello '+ ++counter);
}, 1000 );
rq.on('message', function(msg) {
console.log('Response: ' + msg);
});

// Client
var zmq = require('zmq');
var rq = zmq.socket('req');
rq.connect('tcp://127.0.0.1:8888');
// The "Hello" string is sent every second
setInterval( function() {
    rq.send('Hello');
}, 1000 );
rq.on('message', function(msg) {
console.log('Response: ' + msg);
});

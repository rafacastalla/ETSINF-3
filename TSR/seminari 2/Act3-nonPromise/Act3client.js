// Client
var zmq = require('./nzmq3');
var rq = zmq.socket('req');
var counter=0;
function onSuccess(msg) {
    console.log('Response: '+msg);
}

function onError(err) {
    console.log('Error: '+err);
}

rq.connect('tcp://127.0.0.1:8888');
rq.on('message', onSuccess);
rq.on('error', onError);
// The "Hello" string is sent every second
setInterval( function() {
    rq.request(2,'Hello ', counter++);
}, 1010 );



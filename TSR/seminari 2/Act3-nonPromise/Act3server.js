// Server
// This server is inherited from Activity 1. It aborts before replying to
// the 10th request.
// As a result, this server should be manually restarted once it aborts.
// Client will reconnect automatically to this endpoint.
var zmq = require('zmq');
var rp = zmq.socket('rep');
var counter = 0;
rp.bind('tcp://127.0.0.1:8888',function(err) {
    if (err) throw err;
});
rp.on('message', function(seg1, seg2) {
    if (seg2)
	console.log('Request: ' + seg1 + seg2);
    else 
	console.log('Request: ' +seg1);
    if (++counter==10)
	process.exit();
    rp.send('World');
});

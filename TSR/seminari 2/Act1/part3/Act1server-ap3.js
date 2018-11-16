// Server
var zmq = require('zmq');
var count = 0;
var rp = zmq.socket('rep');
rp.bind('tcp://127.0.0.1:8888',function(err) {
    if (err) throw err;
});
rp.on('message', function(msg) {
    console.log('Request: ' + msg);
    count++;
    if (count==10)
	process.exit();
    rp.send('World');
});

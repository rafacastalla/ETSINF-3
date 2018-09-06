// logger in NodeJS
// First argument is port number for incoming messages
// Second argument is file path for appending log entries

// node logger.js 8066 logger.log

var fs = require('fs');
var zmq = require('zmq')
var log = zmq.socket('pull')
var args = process.argv.slice(2);

var loggerPort = args[0] || '8066';
var filename = args[1] || "/tmp/myfile.log";

log.bindSync('tcp://*:'+loggerPort);

log.on('message', function(text) {
	fs.appendFileSync(filename, text);
});
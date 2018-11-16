/* repl_server.js */

var net = require('net')
var repl = require('repl')

net.createServer(function(socket){
	repl
	.start({
		prompt: '>',
		input: socket,
		output: socket,
		terminal: true
	})
	.on('exit', function(){
		socket.end()
	})
}).listen(8001)

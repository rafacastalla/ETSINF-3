var net = require('net');

var LOCAL_PORT = 8000;
var LOCAL_IP = '127.0.0.1';

var REMOTE_PORT = 80;
var REMOTE_IP = '158.42.4.23'; // www.upv.es

var server = net.createServer(
	function (socket) {
		
		var serviceSocket = new net.Socket();

		serviceSocket.connect(parseInt(REMOTE_PORT), REMOTE_IP,
			function () {
				socket.on('data',
					function (msg) {
						serviceSocket.write(msg);
					}
				);

				serviceSocket.on('data',
					function (data) {
						socket.write(data);
					}
				);
			}
		);
	}
).listen(LOCAL_PORT, LOCAL_IP);

console.log("TCP server accepting connection on port: " + LOCAL_PORT);
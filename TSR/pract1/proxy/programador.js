var net = require('net');

var PROXY_IP = process.argv[2];
var REMOTE_IP = process.argv[3]; // www.upv.es
var REMOTE_PORT = process.argv[4];
var msg = JSON.stringify ({'remote_ip':REMOTE_IP, 'remote_port':REMOTE_PORT});

var serviceSocket = new net.Socket();

serviceSocket.connect(8001, PROXY_IP,
	function () {
		serviceSocket.write(msg);
	}
);

console.log("New data sended");
var net = require('net');

var PROXY_IP = process.argv[2];
var PROXY_PORT = process.argv[3];
var REMOTE_IP = process.argv[4];
var REMOTE_PORT = process.argv[5];
var msg =JSON.stringify ({'op':"set", 'inPort':PROXY_PORT, 'remote':{'ip':REMOTE_IP, 'port':REMOTE_PORT}});

var serviceSocket = new net.Socket();

serviceSocket.connect(8000, PROXY_IP,
	function () {
		serviceSocket.write(msg);
	}
);

console.log("New data sended");
var net = require('net');

var LOCAL_PORT = 8001;
var LOCAL_IP = '127.0.0.1';

var LOCAL_PORT_PROG = 8000;
var LOCAL_IP_PROG = '127.0.0.1';

var REMOTE_IP = ["","158.42.184.5","158.42.4.23","89.238.68.168","158.42.179.56","147.156.222.65","","",""];
var REMOTE_PORT = ["-1", "80", "80", "80", "8080", "80", "-1", "-1", "-1"];
var portAux;

for (var i = 1; i < REMOTE_IP.length; i++) {

	//console.log(REMOTE_IP[i] + ":" + REMOTE_PORT[i] + ", " + LOCAL_PORT);

	if( REMOTE_PORT[i] >= 0 && REMOTE_PORT[i] < 65536){

		var ip = REMOTE_IP[i];
		var port = parseInt(REMOTE_PORT[i]);

		var server = net.createServer(
			function (socket) {

				var serviceSocket = new net.Socket();

				console.log(REMOTE_IP[i] + ":" + REMOTE_PORT[i] + ", " + LOCAL_PORT);
				console.log(ip + ":" + port + ", " + LOCAL_PORT);
				serviceSocket.connect(port, ip,
					function () {
						socket.on('data',
							function (msg) {
								serviceSocket.write(msg);
								console.log("Message sended.");
							}
						);

						serviceSocket.on('data',
							function (data) {
								socket.write(data);
								console.log("Message recived.");
							}
						);

						serviceSocket.on('end',
							function (msg) {
								socket.end();
								console.log("Socket closed.");
							}
						);
					}
				);
			}
		).listen(LOCAL_PORT++, LOCAL_IP);
		console.log("connected.");
	} else {
		console.log("Impossible connect.");
		LOCAL_PORT++
	}
}
console.log("TCP server accepting connection on ports: 8001-8008");

var server_prog = net.createServer(
	function (socket_prog) {

		socket_prog.on('data',
			function (msg) {
				var conf = JSON.parse(msg);
				portAux = conf.inPort - 8000;
				console.log(conf.remote.ip + ":" + conf.remote.port +
					" in " + portAux + ", " + conf.inPort);
				REMOTE_PORT[portAux] = conf.remote.port;
				REMOTE_IP[portAux] = conf.remote.ip;
				console.log("New configuration recived");

			}
		);
	}
).listen(LOCAL_PORT_PROG, LOCAL_IP_PROG);
//var msg =JSON.stringify 
//({'op':"set", 'inPort':PROXY_PORT, 'remote':{'ip':REMOTE_IP, 'port':REMOTE_PORT}});
console.log("TCP server programer accepting connection on port: " + LOCAL_PORT_PROG);
var net = require('net');

var ipServer = process.argv[2];
var ipClient = process.argv[3];

//console.log(ipServer + ' ' + ipClient);

var client = net.connect(8000, ipServer,
	function() { //connect listener  tsr1.dsic.upv.es
		console.log('client connected');
		client.write(ipClient);
	}
);

client.on('data',
	function(data) {
		console.log(data.toString());
		client.end(); //no more data written to the stream
	}
);

client.on('end',
	function() { 
		console.log('client disconnected');
		console.log('Exit client process');
		process.exit();
	}
);

var fs = require('fs');
var net = require('net');

var server = net.createServer(
	function(c) { //connection listener
		console.log('server: client connected');
		
		c.on('end',
			function() {
				console.log('server: client disconnected');
				c.end(); // close socket
				console.log('Exit server process');
				process.exit();
			}
		);
		
		c.on('data',
			function(data) { // send resp
				console.log('server: ipClient ' + data.toString() );
				c.write( server.address().toString() );
				c.write( getLoad().toString() );
			}
		);
	}
);

server.listen(8000,
	function() { //listening listener
		console.log('server bound');
	}
);

function getLoad(){
	data=fs.readFileSync("/proc/loadavg"); //requereix fs
	var tokens = data.toString().split(' ');
	var min1 = parseFloat(tokens[0])+0.01;
	var min5 = parseFloat(tokens[1])+0.01;
	var min15 = parseFloat(tokens[2])+0.01;
	return min1*10+min5*2+min15;
};
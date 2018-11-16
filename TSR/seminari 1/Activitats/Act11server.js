// Server code.
var net = require('net');
var text = '';

var server = net.createServer(
  function(c) { //'connection' listener
    console.log('server connected');
    c.on('end', function() {
      console.log('server disconnected');
    }); 
    // Read what the client sent.
    c.on('data',  function(data) {
	  // Print data to stdout.
      console.log(data.toString()); 
      text += data; 
	  // Print text to stdout.
      console.log('text =\n'+text); 
      // Send the result to the client.
      c.write(text + " ");
      // Close connection.
      c.end(); 
    });
});

server.listen(9000, 
  function() { //'listening' listener
    console.log('server bound');
});

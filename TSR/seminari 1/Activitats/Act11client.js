// Client code.
var net = require('net');

// Check that an argument is given.
if (process.argv.length != 3) {
  console.log('An argument is required!!');
  process.exit();
}

// Obtain the argument value.
var info = process.argv[2];

// The server is in our same machine.
var client = net.connect({port: 9000},
  function() { //'connect' listener
    console.log('client connected');
    console.log('sent:', info);
    // This is sent to the server.
    client.write(info+'\n'); 
});

client.on('data', function(data) {
  // Write the received data to stdout.
  console.log('received:\n'+data.toString()); 
  // Close this connection.
  client.end();                 
});

client.on('end', function() {
  console.log('client disconnected');
});

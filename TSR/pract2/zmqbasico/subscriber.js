var zmq = require('zmq')
var subscriber = zmq.socket('sub')

var args = process.argv.slice(2);
var servURL = args[0];
var typeOfmsg = args[1];

if(args.length < 2){
  console.log("Missing arguments");
  process.exit(0);
}

subscriber.on("message", function(reply) {
  console.log('Received message: ', reply.toString());
})

subscriber.connect(servURL)
subscriber.subscribe(typeOfmsg)

process.on('SIGINT', function() {
  subscriber.close()
  console.log('\nClosed')
})

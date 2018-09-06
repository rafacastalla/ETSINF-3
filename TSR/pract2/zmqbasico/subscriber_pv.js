var zmq = require('zmq')
var subscriber = zmq.socket('sub')

var args = process.argv.slice(2);
var servURL = args[0] || "tcp://localhost:8688";
var typeOfmsg = args[1] || "NEWS";
var verbose = false;

if(args[args.length-1] == "verbose"){
  verbose = true;
  args.pop();
  console.log("Verbose mode activated.");
}


subscriber.on("message", function(reply) {
  console.log('Received message: ', reply.toString());
})

subscriber.connect(servURL)
subscriber.subscribe(typeOfmsg)

process.on('SIGINT', function() {
  subscriber.close()
  if(verbose){
      console.log('\nClosed')
  }
})

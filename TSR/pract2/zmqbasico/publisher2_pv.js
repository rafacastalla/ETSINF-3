var zmq = require('zmq')
var publisher = zmq.socket('pub')

var args = process.argv.slice(2);
var port = args[0];
var seconds = args[1];
var nMSGs = args[2];
var aux = require("./auxfunctions1718.js");
var verbose = false;

if(args.length < 4){
  console.log("Missing arguments");
  process.exit(0);
}

if(args[args.length-1] == "verbose"){
  verbose = true;
  args.pop();
  console.log("Verbose mode activated.");
}

var type = args.slice(3);
var n = 0;

publisher.bind(port, function(err) {
  if(err){
    console.log(err)
  }
  else{
    if(verbose){
        console.log("Listening on "+port+"...");
    }
  }
})

for (var i=1 ; i<nMSGs ; i++)
    setTimeout(function() {
        if(verbose){
            console.log('sent');
        }
        publisher.send(type[n] +  " Hello there! " + aux.randNumber(nMSGs,1));
        n++;
        if(n == type.length){
          n = 0;
        }
    }, 1000 * seconds * i)

process.on('SIGINT', function() {
  publisher.close()
  if(verbose){
      console.log('\nClosed')
  }
})

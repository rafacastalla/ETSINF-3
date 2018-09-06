var ev = require('events');
var emitter = new ev .EventEmitter;
var i1 = "print", i2= "read"; // name of events
var n1 = 0, n2 = 0; // auxiliary vars

// register listener functions on the event emitter
emitter.on(i1, function() { console.log('event ' + i1 + ': ' + (++n1) + 'times')})

emitter.on(i2, function() { console.log('event ' + i2 + ': ' + (++n2) + 'times')})

// more than one listener for the same event is possible
emitter.on(i1, function() { console.log('something has been printed!')})

// generate the events periodically
setInterval( function() {emitter.emit(i1);}, 2000); // generates i1 every 2 seconds
setInterval( function() {emitter.emit(i2);}, 8000); // generates i2 every 8 seconds
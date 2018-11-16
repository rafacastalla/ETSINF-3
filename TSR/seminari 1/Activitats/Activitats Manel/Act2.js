var ev = require('events');
var emitter = new ev.EventEmitter;
var e1 = "UNO";
var e2 = "DOS";
var e3 = "TRES";
var books = [ "Walk Me Home", "When I Found You", "Jane's Melody", "Pulse" ];
var temps = 2000;
// Constructor for class Listener.
function Listener(n1,n2,n3) {
	this.name1 = n1;
  this.name2 = n2;
  this.name3 = n3;
  this.num1 = 0;
  this.num2 = 0;
  this.num3 = 0;
}

Listener.prototype.event1 = function() {
  this.num1++;
	console.log( "Listener actiu: " + this.num1 + " esdeveniments de tipus "+this.name1);
}

Listener.prototype.event2 = function() {
  this.num2++;
  if(this.num1 >this.num2){
    console.log( "Hi ha mes esdeveniments de tipus UNO y el temps es "+temps);
    console.log( "Listener actiu: " + this.num2 + " esdeveniments de tipus dos "+this.name2);
  }else{
      console.log( "Listener actiu: " + this.num2 + " esdeveniments de tipus dos "+this.name2);
  }
}
Listener.prototype.event3 = function() {
  this.num3++;
  if(temps < 18000){
    clearInterval(i);
    temps *=3;
    i = setInterval(function(){
      emitter.emit(e2);
    },temps)
  }
  console.log("Temps nou:" + temps);
	console.log( "Listener actiu: " + this.num3 + " esdeveniments de tipus tres "+this.name3);
}

// A Listener object is created.
var lis = new Listener(e1,e2,e3);
// Listener is registered on the event emitter.
emitter.on(e1, function() {lis.event1()});
emitter.on(e2, function(x) {lis.event2()});
emitter.on(e3, function(x) {lis.event3()});

// Generate the events periodically...
setInterval( function() {
	emitter.emit(e1);
}, 3000 );

var i = setInterval( function() {
	emitter.emit(e2);
}, temps );

setInterval( function() {
	emitter.emit(e3);
}, 10000 );

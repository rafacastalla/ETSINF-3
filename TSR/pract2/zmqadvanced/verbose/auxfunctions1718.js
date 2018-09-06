 	//auxfunctions1718
 	
 	  // *** getLoad function
 	
 	function getLoad() {
 	  var fs     = require('fs') 
 	    , data   = fs.readFileSync("/proc/loadavg") // version sincrona 
 	    , tokens = data.toString().split(' ') 
 	    , min1   = parseFloat(tokens[0])+0.01
 	    , min5   = parseFloat(tokens[1])+0.01
 	    , min15  = parseFloat(tokens[2])+0.01
 	    , m      = min1*10 + min5*2 + min15;
 	  return m; 
 	}
 	
 	  // *** randNumber function
 	
 	function randNumber(upper, extra) {
 	  var num = Math.abs(Math.round(Math.random() * upper));
 	  return num + (extra || 0);
 	}
 	
 	  // *** randTime function
 	
 	function randTime(n) {
 	  return Math.abs(Math.round(Math.random() * n)) + 1;
 	}
 	
 	  // *** showArguments function
 	
 	function showMessage(msg) {
 	  msg.forEach( (value,index) => {
 	    console.log( '     Segment %d: %s', index, value );
 	  })
 	}
 	
 	  // *** ordered list functions for workers management
 	  // list has an "ordered" property (true|false) and a data property (array)
 	  // data elements consists of pairs {id, load}
 	
 	function orderedList() {
 	  return {ordered: true, data: []};
 	}
 	
 	function nonempty() {
 	  return (this.data.length > 0);
 	}
 	
 	function lowest() {  // ordered reads
 	  if (!this.ordered) {
 	    this.data.sort(function(a, b) {
 	      return parseFloat(b.load) - parseFloat(a.load);
 	    })
 	  }
 	  this.ordered = true; 
 	  return this.data.shift();
 	}
 	
 	function insert(k) { // unordered writes
 	  this.ordered = false;
 	  this.data.push(k);
 	}
 	
 	module.exports.getLoad = getLoad;
 	module.exports.randNumber = randNumber;
 	module.exports.randTime = randTime;
 	module.exports.showMessage = showMessage;
 	module.exports.orderedList = orderedList;
 	module.exports.nonempty = nonempty;
 	module.exports.lowest = lowest;
 	module.exports.insert = insert; 

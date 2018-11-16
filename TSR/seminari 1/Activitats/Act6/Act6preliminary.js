// Act6preliminary.js
// This first version follows the algorithm shown in the blackboard
// but it is not considering yet that fs.readFile() is an asynchronous
// function and that its callbacks will be executed once the main 
// thread has requested all the readFile() calls.

var fs = require('fs');

// We discard the first slot (since it always holds the name of the 
// interpreter) and the second one (since it holds the name of the
// program). With this, "args" maintains the actual arguments 
// passed by the user.
var args = process.argv.slice(2);
var maximumSize = 0;
var fileName = "";

for (var i in args) {

	fs.readFile( args[i], 
	    function(err, contents) {
			if (err) {
				console.error("Error reading one of the files!");
			} else {
				if (contents.length > maximumSize ) {
					maximumSize = contents.length;
					fileName = args[i];
				}
			}
		}
	)	
	if ( i == args.length-1 ) {
		console.log ("The largest file is %s and its length is %d", fileName, maximumSize);	
	}
}

// The main problem of these first version is that it prints the
// result message before any of the callbacks is started. Due to
// this, the variables being used still hold their initial values.

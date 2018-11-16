// This is the first version presented last Friday.
// It uses a closure in order to maintain the appropriate file name.
// Now, the output message is inside the callback.
var fs = require('fs');
var args = process.argv.slice(2);
var maximumSize = 0;
var fileName = "";

function processFile(i) {
	return function(err, contents) {
		if (err) {
			console.error("Error reading one of the files!");
		} else {
			if (contents.length > maximumSize ) {
				maximumSize = contents.length;
				fileName = args[i];
			}
		}
		if ( i == args.length-1 ) {
			console.log ("The largest file is %s and its length is %d", fileName, maximumSize);	
		}
	}
}	
	
for (var i in args) {
	fs.readFile( args[i], processFile(i) );
}

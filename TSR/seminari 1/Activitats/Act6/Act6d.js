// This is the third version presented last Friday.
// Although "Act6c.js" already prints a correct output, we'll
// try to get now additional information on errors.
var fs = require('fs');
var args = process.argv.slice(2);
var maximumSize = 0;
var count = 0;
var fileName = "";

// Another recommendable checking: verify that at least one
// argument has been given!
if (args.length < 1) {
	// Print an error message.
	console.error( "Please provide a list of file names!" );
	// Abort the process. It doesn't make sense to 
	// continue (although nothing wrong may happen) if
	// there is nothing to be processed.
	process.exit(1);
}

function processFile(i) {
	return function(err, contents) {
		count++;
		if (err) {
			// We may print the name of the erroneous file
			// and a description of the error.
			console.error("Error reading '%s'. Reason: %s", args[i], JSON.stringify(err));
		} else {
			if (contents.length > maximumSize ) {
				maximumSize = contents.length;
				fileName = args[i];
			}
		}
		if ( count == args.length ) {
			console.log ("The largest file is %s and its length is %d bytes.", fileName, maximumSize);	
		}
	}
}	
	
for (var i in args) {
	fs.readFile( args[i], processFile(i) );
}

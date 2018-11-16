// Act6preliminary2.js
// A slight improvement on the Act6preliminary.js version. Now,
// the program only prints something to the screen inside the
// callback. This guarantees that at least the current file has
// been processed.
var fs = require('fs');
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
				if ( i == args.length-1 ) {
					console.log ("The largest file is %s and its length is %d", fileName, maximumSize);	
				}
			}
		}
	)	
}
// This version is not yet enough, since it prints as many messages
// as files.
// Besides, in all of them the largest file name seems to be the
// name of the last processed file.
// Closures are needed to fix this problem.

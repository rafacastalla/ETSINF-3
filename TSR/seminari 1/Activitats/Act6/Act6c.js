// This is the second version presented last Friday.
// "Act6b.js" will not behave in a correct way when any of the
// first files whose names are passed as arguments is much
// bigger than all the other. In that case, its callback is still
// running when the last callback has printed the result.
// The correct behaviour depends on checking how many files have
// already been processed instead of checking whether the last one
// in the list is the current one.
var fs = require('fs');
var args = process.argv.slice(2);
var maximumSize = 0;
var count = 0;
var fileName = "";

// We still need a closure for accessing the correct args[] slot.
function processFile(i) {
	return function(err, contents) {
		// The counter is always increased, even in case of error.
		count++;
		if (err) {
			console.error("Error reading one of the files!");
		} else {
			if (contents.length > maximumSize ) {
				maximumSize = contents.length;
				fileName = args[i];
			}
		}
		if ( count == args.length ) {
			console.log ("The largest file is %s and its length is %d", fileName, maximumSize);	
		}
	}
}	
	
for (var i in args) {
	fs.readFile( args[i], processFile(i) );
}

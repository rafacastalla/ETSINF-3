// This is the fourth version presented last Friday.
// Although "Act6d.js" deals with all the exercise requirements,
// it will need a lot of time for providing its output if several
// files have a large size.
// In order to avoid that behaviour, we'll need to read each
// file attributes instead of their contents.
// We are not interested in directories, only in regular files.
// In order to exclude directories from our output, we should
// check the file type. In case of UNIX systems, that information
// is placed in the "mode" property. In other operating systems,
// this program may not work.
var fs = require('fs');
var args = process.argv.slice(2);
var maximumSize = 0;
var count = 0;
var fileName = "";

if (args.length < 1) {
	console.error( "Please provide a list of file names!" );
	process.exit(1);
}

function processFile(i) {
	return function(err, attribs) {
		count++;
		if (err) {
			console.error("Error opening '%s'. Reason: %s", args[i], JSON.stringify(err));
		} else {
			// A regular file has bit 15 of the "mode" property set to one and the
			// remaining bits of the file type mask set to zero.
			if (attribs.mode > 32768 && attribs.mode < 65536) {
				// The property to be used in the provided object is "size".
				if (attribs.size > maximumSize ) {
					maximumSize = attribs.size;
					fileName = args[i];
				}
			}
		}
		if ( count == args.length ) {
			console.log ("The largest regular file is %s and its length is %d bytes.", fileName, maximumSize);	
		}
	}
}	
	
for (var i in args) {
	// Instead of readFile() we need now the stat() method.
	// This method returns an object that maintains many
	// attributes of the provided file.
	fs.stat( args[i], processFile(i) );
}

// This is the version presented at the end of our Wednesday session.
// It uses a closure in order to maintain the appropriate file name.
// However, the teacher introduced an involuntary error when the
// closure was written since the printing of the output message was
// dropped from the callback and it must be inside it.
// Because of this, that message is printed before any file
// is processed and it shows the initial values for both the
// file name and size.
var fs = require('fs');
var args = process.argv.slice(2);
var maximumSize = 0;
var fileName = "";
var cont =args.length;

function processFile(i){
	return function(err, contents) {
		if (err) {
			console.error("Error reading one of the files!");
		} else {
			if (contents.length > maximumSize ) {
				maximumSize = contents.length;
				fileName = args[i];
			}
			--cont;
			if(cont==0)
			console.log ("The largest file is %s and its length is %d", fileName, maximumSize);
		}
	}
}

//args.forEach( function(i){console.log(" "+i);}
//args.forEach( (i)=>{console.log(" "+i)});

for (var i in args) {
	fs.readFile( args[i], processFile(i) );
}

// concatEldestNewest.js
// This program receives multiple file names as arguments
// from the command line. At least two arguments are needed.
// It generates a file named "output" that stores the contents
// of the oldest given file (first) plus the contents of the 
// newest one (appended to the former).
//
// We will use only asynchronous functions from the "fs" module.
// Instead of nesting multiple callbacks, we will raise events
// at the end of each step, showing how multiple asynchronous
// tasks may be sequenced in a JavaScript program.

var ev = require("events");
var ee = new ev.EventEmitter();
var fs = require("fs");
var oldestName = "";
var oldestDate = new Date().getTime();
var newestName = "";
var newestDate = 0;
var numProcessed = 0;
// Event names...
var e1 = "create";
var e2 = "append";

// Check whether we have received a valid number of arguments.
if (process.argv.length < 4) {
	console.error("At least two file names should be provided"+
		" as arguments!!");
	process.exit();
}

// If so, save the file names into a separate array.
var names = process.argv.slice(2);
var numFiles = names.length;

// Returns a callback for the fs.stat() function that
// looks for the oldest and newest files.
function lookForTimes( name ) {
	return function (err, stats) {
		// Check whether it is older.
		if (stats.mtime.getTime() < oldestDate) {
			// If so, save its properties.
			oldestDate = stats.mtime.getTime();
			oldestName = name;
		}
		// Check whether it is newer.
		if (stats.mtime.getTime() > newestDate) {
			// If so, save its properties.
			newestDate = stats.mtime.getTime();
			newestName = name;
		}
		// Increase the number of processed files.
		numProcessed++;
		// Check whether all files have been processed.
		if (numProcessed == numFiles) {
			// If so, raise the next event.
			ee.emit(e1);
		}
	}
}

// First task: Find the oldest and newest files.
for (var i=0; i < numFiles; i++) {
	fs.stat(names[i],lookForTimes(names[i]));
}

// Second task: Copy the oldest file onto "output".
function copy() {
	// Read the oldest file.
	fs.readFile(oldestName, function(err,contents) {
		// If any error happens, abort this process.
		if (err) {
			console.error("Error reading %s! %s", oldestName, err);
			process.exit();
		}
		// Try to create the output file.
		fs.writeFile("output", contents, function(err,result) {
			if (err) {
				console.error("Error copying %s! %s", oldestName, err);
				process.exit();
			}
			// The oldest file has been copied.
			// Proceed with appending the newest file!
			ee.emit(e2);
		});
	});
}

// Third task: Append the newest file onto "output".
function append() {
	// Read the newest file.
	fs.readFile(newestName, function(err,contents) {
		if (err) {
			console.error("Error reading %s! %s", oldestName, err);
			process.exit();
		}
		fs.appendFile("output", contents, function(err,result) {
			if (err) {
				console.error("Error appending %s! %s", newestName, err);
				process.exit();
			}
			console.log("Done! File 'output' holds now the contents of '%s' "
			 + "(oldest) and '%s' (newest).", oldestName, newestName);
		});
	});
}

// Set the listener for the first event.
ee.on( e1, copy );
// Set the listener for the second event.
ee.on( e2, append );

fs = require('fs');
path = require('path');
os = require('os');
var rolodex={};

function contentsToArray(contents) {
	return contents.split(os.EOL);
}
function parseArray(contents,pattern,cb) {
	for(var i in contents) {
		if (contents[i].search(pattern) > -1)
			cb(contents[i]);
	}
}

function retrieve(pattern,cb) {
	fs.readFile("rolodex", "utf8", function(err,data){
		if (err) {
			console.log("Please use the name of an existant file!!");
		} else {
			parseArray(contentsToArray(data),pattern,cb);
		}
	});
}

function processEntry(name, cb) {
	if (rolodex[name]) {
		cb(rolodex[name]);
	} else {
		retrieve( name, function (val) {
			rolodex[name] = val;
			cb(val);
		});
	}
}

function test() {
	for (var n in testNames) {
		console.log ('processing ', testNames[n]);
		processEntry(testNames[n], function generator(x) {
			return function (res) {
				console.log('processed %s. Found as: %s', testNames[x], res);
			}}(n))
	}
}

var testNames = ['a', 'b', 'c'];
test();


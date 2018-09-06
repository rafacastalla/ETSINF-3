// LLEGIR DE FITXER
function read() {
	var fs = require('fs');
	fs.readFile('etc/hosts', 'utf8', function(err, data){
		if (err) {
			return console.log(err);
		}
		console.log(data);
	});
}

// ESCRIURE EN FITXER
function write(){
	var fs = require('fs');
	fs.writeFile('/tmp/f', 'contingut del nou fitxer', 'utf8',
		function(err, data){
			if (err) {
				return console.log(err);
			}
			console.log(data);
		});
}

// ACCES A DIRECTORIS
function getFiles(){
	var fs = require('fs');

	files_ = files_ || [];
	var files = fs.readdirSyns(dir);
	for(var i in files){
		var name = dir + '/' + files[i];
		if(fs.statSync(name).isDirectory()){
			getFiles(name, files_);
		}else{
			files_.push(name);
		}
	}
	return files_;

	console.log(getFiles('.'));
}
var fs = require('fs')
var total_votos = [ ]
var votos = [ ]
fs.readdir('.', function(err, files) {
  var count = files.length
  for (var i = 0; i < files.length; i++) {
    fs.readFile(files[i], function(x) {
      return function(err, data) {
      count--;
      if ( err ) return
      if ( files[x].slice(-4) == '.txt' ){
        var j = files[x].slice(0,-4)
        votos[j] = JSON.parse(data)
        for ( k in votos[j] ) {
          if ( !total_votos[k] )
          total_votos[k] = votos[j][k]
          else
          total_votos[k] += votos[j][k]
        }
        if ( count <= 0 ) consultar(votos)
      }else return;
      }
    }(i)
  )}
})
function consultar(votos) {
console.log('\nResultados globales:')
console.log('Votos:', total_votos)
console.log("\n\nProvincia: ")
process.stdin.on("data", function(str) {
var provincia = str.slice(0,str.length-1)
var res = JSON.stringify(votos[provincia])
console.log("votos en " + provincia + ": " + res)
console.log("\nProvincia: ")
})
}

/* repl_show.js */

var repl = require('repl')
var f = function(x) {console.log(x)}
repl.start('$> ').context.show = f

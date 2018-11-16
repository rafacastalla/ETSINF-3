/* repl_client.js */

var net = require('net')
var sock = net.connect(8001)
process.stdin.pipe(sock)
sock.pipe(process.stdout)

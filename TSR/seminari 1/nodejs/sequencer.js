const zmq = require('zmq')
var pull = zmq.socket("pull"); pull.bindSync('tcp://*:1000')
var pub  = zmq.socket("pub");   pub.bindSync('tcp://*:1001')

pull.on('message',function(v,p){pub.send([v,p])}) 

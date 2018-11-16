const ev = require('events')
var emisor = new ev.EventEmitter()
var evento = {uno:'uno', dos:'dos', tres:'tres'}
var veces  = {uno:0, dos:0, tres:0}
var sep= 2000

setInterval(function() {emisor.emit(evento.uno)}, 3000)
var i = setInterval(function() {emisor.emit(evento.dos)}, sep)
setInterval(function() {emisor.emit(evento.tres)}, 10000)

function print(x) {console.log(++veces[x]+' eventos de tipo '+evento[x])}

emisor.on(evento.uno, function() {print('uno')})

emisor.on(evento.dos, function() {
	if (veces.dos >= veces.uno) 
		print('dos')
	else
		console.log('Hay mas eventos de tipo 1')
})

emisor.on(evento.tres, function() {
	print('tres')
	if (sep<18000) {
		clearInterval(i)   
		sep*=3
		i=setInterval(function() {emisor.emit(evento.dos)},sep)
	}
})
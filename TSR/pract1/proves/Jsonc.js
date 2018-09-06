var msg = JSON.stringify(
	{ "name": "mkyong",
		"age": 30,
		"address": { "street": "8th Street", "city": "New York"},
		"phone": [{ "type": "home", "number": "111-1111"},
				{ "type": "fax", "number": "222-2222" }]
	}
);

var socket = net.connect( {port:8000},
	function() { socket.write(msg); }
)
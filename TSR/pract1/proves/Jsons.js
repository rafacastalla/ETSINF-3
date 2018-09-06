var server = net.createServer(
	function(c) {
		c.on('data',
			function(data) {
				var person = JSON.parse(data);
				console.log(person.name); //mkyong
				console.log(person.address.street); //8th Street
				console.log(person.address.city); //New York
				console.log(person.phone[0].number); //111-1111
				console.log(person.phone[1].type); //fax
			}
		)
	}
);

server.listen( 8000,
	function() { //listening listener
		console.log('server bound');
	}
);
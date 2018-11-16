function table(x) {  // Prints column x of a (1..10) multiplication table
	for (var j=1; j<11; j++)
		console.log("%d * %d = %d", x, j, x*j);
	console.log("");
}

function allTables() {
	for (var i=1; i<11; i++)
		table(i);
}

allTables(table(30),table(20),table(10));
table(table(2));
table(5,4,1);

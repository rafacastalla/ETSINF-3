function table(x) {
   for (var j=1; j<11; j++) console.log("%d * %d",x,j,x*j)
   console.log("")
}
function allTables() {
	for (var i=1; i<11; i++) table(i)
}
table(table(2))

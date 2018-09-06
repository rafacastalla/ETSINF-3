	.data
	; Vector x
x:	.double 1, 2, 3, 4, 5, 6, 7, 8 
	; Vector y 
y:	.double 100, 100, 100, 100, 100, 100, 100, 100
	; Vector z 
z:	.space 64
a:	.double 2	

	.text

	dadd r1, r0, x 
	dadd r2, r0, y 
	dadd r3, r0, z 
	dadd r4, r1, 64
	l.d f0, a(r0)	
loop:	
	l.d f1, 0(r1)		; Load X
	l.d f2, 0(r2)		; Load Y
	mul.d f3, f1, f0	; a*X
	add.d f4, f2, f3	; a*X +Y
	s.d f4, 0(r3)		; Store Z
	dadd r1, r1, 8
	dadd r2, r2, 8
	dadd r3, r3, 8
	dsub r5, r4, r1
	bnez r5, loop

	trap 0

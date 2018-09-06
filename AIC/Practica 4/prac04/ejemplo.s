	.data               ; Comienzo de los datos de memoria
a:	.double 10.5
b:	.double 2
c:	.double 20

s1:	.space 8
s2:	.space 8

	.text               ; Comienzo del fragmento de código

	l.d f0, a(r0)		; Carga a
	l.d f1, b(r0)		; Carga b
	l.d f2, c(r0)		; Carga c
	add.d f4, f0, f1	; t1= a + b
	mul.d f5, f2, f4	; t2= c * t1 
	s.d f4, s1(r0)		; Guarda t1
	s.d f5, s2(r0)		; Guarda t2

	trap 0			; Final del programa

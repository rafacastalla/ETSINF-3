        ; z = a*x + y
        ; Tama�o de los vectores: 64 palabras
        ; Vector x
	.data
x:      .double 0,1,2,3,4,5,6,7,8,9
        .double 10,11,12,13,14,15,16,17,18,19
        .double 20,21,22,23,24,25,26,27,28,29
        .double 30,31,32,33,34,35,36,37,38,39
        .double 40,41,42,43,44,45,46,47,48,49
        .double 50,51,52,53,54,55,56,57,58,59
        .double 60,61,62,63

	; Vector y
y:      .double 100,100,100,100,100,100,100,100,100,100
	.double 100,100,100,100,100,100,100,100,100,100
	.double 100,100,100,100,100,100,100,100,100,100
	.double 100,100,100,100,100,100,100,100,100,100
	.double 100,100,100,100,100,100,100,100,100,100
	.double 100,100,100,100,100,100,100,100,100,100
	.double 100,100,100,100

        ; Vector z
	;   64 elementos son 512 bytes
z:      .space 512

        ; Escalar a
a:      .double 1

        ; El c�digo
	.text

start:
        dadd r1, r0, x     ; r1 contiene la direccion de x
        dadd r2, r0, y     ; r2 contiene la direccion de y
        dadd r3, r0, z     ; r3 contiene la direccion de z

        l.d f0, a(r0)      ; f0 contiene a

        dadd r4, r1, #512         ; 64 elementos son 512 bytes

loop:
        l.d f1, 0(r1)     ;elemento de x
        l.d f2, 0(r2)     ;elemento de y

        mul.d f3, f1, f0 ; aux = x * a
        add.d f3, f3, f2  ; aux = aux + y
        s.d f3, 0(r3)     ; z = aux

        dadd r1, r1, #8   ; x++
        dadd r2, r2, #8   ; y++
        dadd r3, r3, #8   ; z++

        dsub r4, r4, #8
        bnez r4, loop

        nop               ; "delay slot"

        trap #0           ; Fin de programa

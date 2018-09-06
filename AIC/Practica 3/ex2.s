        ; z = a * x + y
        ; Tamaño de los vectores: 64 palabras
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

        ; El código
	.text

start:
        dadd r1, r0, x     ; r1 contiene la direccion de x
        dadd r2, r0, y     ; r2 contiene la direccion de y
        dadd r3, r0, z     ; r3 contiene la direccion de z
        
        l.d f8, a(r0)      ; f0 contiene a
        
        dadd r4, r1, #512         ; 64 elementos son 512 bytes

loop:
        l.d f0, 0(r1)      ;elemento de x1
        l.d f2, 8(r1)      ;elemento de x2
        l.d f4, 16(r1)     ;elemento de x3
        l.d f6, 24(r1)     ;elemento de x4

        l.d f10, 0(r2)     ;elemento de y1
        l.d f12, 8(r2)     ;elemento de y2
        l.d f14, 16(r2)    ;elemento de y3
        l.d f16, 24(r2)    ;elemento de y4

        mul.d f18, f0, f8  ; aux1 = x1 * a
        mul.d f20, f2, f8  ; aux2 = x2 * a
        mul.d f22, f4, f8  ; aux3 = x3 * a
        mul.d f24, f6, f8  ; aux4 = x4 * a

        add.d f18, f18, f10; aux1 = aux1 + y1
        add.d f20, f20, f12; aux2 = aux2 + y2
        add.d f22, f22, f14; aux3 = aux3 + y3
        add.d f24, f24, f16; aux4 = aux4 + y4

        s.d f18, 0(r3)     ; z1 = aux1
        s.d f20, 8(r3)     ; z2 = aux2
        s.d f22, 16(r3)    ; z3 = aux3
        s.d f24, 24(r3)    ; z4 = aux4

        dadd r1, r1, #32   ; x++
        dadd r2, r2, #32   ; y++
        dadd r3, r3, #32   ; z++

        dsub r4, r4, #32   ; i++
        bnez r4, loop

        nop                ; "delay slot"

        trap #0            ; Fin de programa

        



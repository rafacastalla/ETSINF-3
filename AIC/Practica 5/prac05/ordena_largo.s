	.data
	; Matriz A
a:	.double 6.6, 5.7, 4.8, 3.9, 3.0, 2.1, 1.2, 11.1, 10.2, 9.3, 8.4, 0.0

	.text

        dadd r2, r0, 12           ; 12 pasadas
it_pasada:
        dadd r1, r0, a
        dadd r3, r1, 88          ; Apunta al último elemento 11 * sizeof(double)
it_elemen:
        l.d f0, 0(r1)            ; Elemento i
        l.d f1, 8(r1)            ; Elemento i+1
        c.gt.d f0, f1
        bc1f elem_orden

        s.d f0, 8(r1)            ; Intercambiar
        s.d f1, 0(r1)

elem_orden:
        dadd r1, r1, 8        
        dsub r4, r3, r1
        bnez r4, it_elemen

        dsub r2, r2, 1
        bnez r2, it_pasada

		trap 0
		

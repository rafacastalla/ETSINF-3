	.data
	; Matriz A
a:	.double 3.00, 2.00, 1.00, 0.00

	.text

        dadd r2, r0, 4           ; 4 pasadas
it_pasada:
        dadd r1, r0, a
        dadd r3, r1, 24          ; Apunta al penúltimo elemento 3 * sizeof(double)
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
end:
        trap 0
        

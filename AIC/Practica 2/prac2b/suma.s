	; suma las componentes del vector hasta que encuentra
	; una componente a 0
	; almacena el resultado en a
        .data
a:		.dword  0
y:      .dword  1,2,3,0,4,5,6,7,8
        .text
		dadd r1,r0,r0 ; r1=0
		dadd r3,r3,r0 ; r3=0
		dadd r2,r0,y  ; r2 recorre y
bucle:  dadd r1,r3,r1 ; este riesgo esta previsto
        ld r3,0(r2)   ; r3 es y[i]
        dadd r2,r2,#8
		bnez r3,bucle ; si r3<>0
		sd r1,a(r0)
final:
	; el resultado debe ser a=6

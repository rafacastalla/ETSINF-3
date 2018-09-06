		.data                   ; Comienzo de los datos de memoria
a:		.double 5
b:		.double 15
c:		.double 25

v:		.space  16

v_fin:
        
		.text                   ; Comienzo del fragmento de código

		dadd   r1, r0, v_fin
		l.d    f0, a(r0)
		l.d    f1, b(r0)
		l.d    f2, c(r0)
        
bucle:	
		dsub   r1, r1, #8
		add.d  f1, f1, f0
		c.lt.d f1, f2            ; CondFP:= true, si f2 < f4
		mul.d  f1, f1, f0
		s.d    f1, 0(r1)
		bc1t   bucle             ; Salta si CondFP = true

		sub.d  f2, f1, f0

		trap 0                   ; Final del programa

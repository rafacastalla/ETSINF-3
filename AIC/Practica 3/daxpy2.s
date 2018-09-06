  ; z = a*x + y
  ; Tamanyo de los vectores: 64 palabras
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
a:      .double 1.0

  ; El codigo
.text

start:
      dadd r1,r0,x      ; r1 contiene la direccion de x
      dadd r2,r0,y      ; r2 contiene la direccion de y
      dadd r3,r0,z      ; r2 contiene la direccion de z

      l.d f0,a(r0)      ; f0 contiene a

      dadd r4,r1,#512   ; 64 elementos son 512 bytes

loop:                   ; z = a*x + y
      l.d f2,0(r1)      ; element de x0
      l.d f4,8(r1)      ; element de x1
      l.d f6,16(r1)     ; element de x2
      l.d f8,24(r1)     ; element de x3

      l.d f10,0(r2)     ; element de y0
      l.d f12,8(r2)     ; element de y1
      l.d f14,16(r2)    ; element de y2
      l.d f16,24(r2)    ; element de y3

      mul.d f18,f0,f2    ; f18 = a*x0
      mul.d f20,f0,f4    ; f20 = a*x1
      mul.d f22,f0,f6    ; f22 = a*x2
      mul.d f24,f0,f8    ; f24 = a*x3

      add.d f18,f18,f10    ; f18 = f18 + y0
      add.d f20,f20,f12    ; f20 = f20 + y1
      add.d f22,f22,f14    ; f22 = f22 + y2
      add.d f24,f24,f16    ; f24 = f24 + y3

      s.d f18, 0(r3)      ; z0 = f18
      s.d f20, 8(r3)      ; z1 = f20
      s.d f22, 16(r3)     ; z2 = f22
      s.d f24, 24(r3)     ; z3 = f24

      dadd r1,r1,#32     ; x++
      dadd r2,r2,#32     ; y++
      dadd r3,r3,#32     ; z++

      dsub r4,r4, #32    ;i++
      bnez r4,loop

      nop               ; "delay slot"
      trap #0           ; Fin de programa

#######

CFLAGS_BISON	= -O2 -fno-strength-reduce
CFLAGS		= -O2 -fno-strength-reduce  -Wall 
# CFLAGS		= -ggdb -fno-strength-reduce -Wall
YACCCFLAGS	= -Wno-unused -Wno-parentheses
CC		= gcc
SHELL		= /bin/sh
CDEPEND		= makedepend

####### Files

HEADERS =	main.h tipos.h
PROTOTYPES =    etiquetas.hi \
		presentacion.hi \
		prediccion.hi \
		f_busqueda.hi \
		f_lanzamiento.hi \
		f_lanzamiento_sol.hi \
		f_ejecucion.hi \
		f_transferencia.hi \
		f_confirmacion.hi

SOURCES =	input.yacc.y \
		input.lex.l \
		etiquetas.c \
		presentacion.c \
		f_busqueda.c \
		f_lanzamiento.c \
		f_ejecucion.c \
		f_transferencia.c \
		main.c 

OBJECTS =	input.yacc.o \
		input.lex.o \
		etiquetas.o \
		presentacion.o \
		f_busqueda.o \
		f_lanzamiento.o \
		f_ejecucion.o \
		f_transferencia.o \
		main.o

SOL	=	f_lanzamiento_sol.o f_confirmacion.o prediccion.o

TARGET	=	mips-ooo

####### Build rules

$(TARGET):  proto $(OBJECTS) 
	$(CC) $(OBJECTS) $(SOL) -o $(TARGET) $(LFLAGS) 

proto: $(PROTOTYPES)

depend: 
	makedepend -Y -I. *.c 2> /dev/null

clean:
	rm -f $(OBJECTS) $(TARGET)
	rm -f *.yacc.[ch] *.lex.c input.yacc.output

all: clean $(TARGET) 

distclean:
	rm -f $(PROTOTYPES) $(TARGET)

### Para lex y yacc

%.o : %.c
	$(CC) -c $(CFLAGS) -o $@ $<

%.hi: %.c
	./getproto2 $< > $@

input.lex.c : input.lex.l input.yacc.h
input.yacc.c : input.yacc.y main.h tipos.h etiquetas.h
input.yacc.h : input.yacc.y

input.yacc.o : input.yacc.c
	$(CC) -c $(CFLAGS_BISON) -o $@ $<

%.lex.c: %.lex.l %.yacc.h
	lex -t $*.lex.l > $*.lex.c

%.yacc.c: %.yacc.y
	bison -v -o $*.yacc.c $*.yacc.y 

%.yacc.h: %.yacc.y
	bison -o $*.yacc.c -d $*.yacc.y

algoritmo.h: $(patsubst %.c,%.hi,$(wildcard f_*.c))

# DO NOT DELETE

etiquetas.o: etiquetas.h tipos.h etiquetas.hi main.h
f_busqueda.o: main.h tipos.h instrucciones.h prediccion.h prediccion.hi
f_busqueda.o: presentacion.h presentacion.hi
f_confirmacion.o: main.h tipos.h instrucciones.h prediccion.h prediccion.hi
f_confirmacion.o: presentacion.h presentacion.hi
f_ejecucion.o: main.h tipos.h etiquetas.h etiquetas.hi instrucciones.h
f_ejecucion.o: prediccion.h prediccion.hi presentacion.h presentacion.hi
f_lanzamiento.o: main.h tipos.h instrucciones.h prediccion.h prediccion.hi
f_lanzamiento.o: presentacion.h presentacion.hi
f_lanzamiento_sol.o: main.h tipos.h instrucciones.h prediccion.h prediccion.hi
f_lanzamiento_sol.o: presentacion.h presentacion.hi
f_lanzamiento_sol.o: algoritmo.h f_lanzamiento.hi
f_transferencia.o: main.h tipos.h instrucciones.h prediccion.h prediccion.hi
f_transferencia.o: presentacion.h presentacion.hi
input.lex.o: input.yacc.h instrucciones.h tipos.h main.h
input.yacc.o: main.h tipos.h etiquetas.h etiquetas.hi
main.o: main.h tipos.h prediccion.h prediccion.hi presentacion.h
main.o: presentacion.hi instrucciones.h algoritmo.h f_busqueda.hi
main.o: f_lanzamiento.hi f_lanzamiento_sol.hi f_ejecucion.hi f_transferencia.hi f_confirmacion.hi
prediccion.o: prediccion.h tipos.h prediccion.hi main.h instrucciones.h
prediccion.o: presentacion.h presentacion.hi
prediccion_dos_bits.o: prediccion.h tipos.h prediccion.hi main.h
prediccion_dos_bits.o: instrucciones.h presentacion.h presentacion.hi
prediccion_un_bit.o: prediccion.h tipos.h prediccion.hi main.h
prediccion_un_bit.o: instrucciones.h presentacion.h presentacion.hi
presentacion.o: tipos.h main.h instrucciones.h etiquetas.h etiquetas.hi
presentacion.o: presentacion.h presentacion.hi

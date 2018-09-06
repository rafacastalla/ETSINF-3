#######

PRAC=5

CFLAGS_BISON	= -O2 -fno-strength-reduce
CFLAGS		= -O2 -fno-strength-reduce  -Wall
LFLAGS		= -lm
# CFLAGS		= -ggdb -fno-strength-reduce -Wall
YACCCFLAGS	= -Wno-unused -Wno-parentheses
CC		= gcc
SHELL		= /bin/sh
CDEPEND		= makedepend

####### Files

HEADERS = main.h tipos.h

SOURCES=$(wildcard *_alum.c)
A_OBJECTS=$(patsubst %.c,%.o, ${SOURCES})

S_OBJECTS=$(wildcard *.c.o)

OBJECTS = ${A_OBJECTS} ${S_OBJECTS}

TARGET	=	mips-ooo

####### Build rules

$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) $(SOL) -o $(TARGET) $(LFLAGS)

depend: 
	makedepend -Y -I. *.c 2> /dev/null

all: clean $(TARGET) 

clean: 
	rm -vf *_alum.o $(TARGET)

distclean: clean

%.o : %.c
ifndef PRAC
	$(error ERROR: ejecuta make PRAC=4 o make PRAC=5)
endif
	$(CC) -c $(CFLAGS) -o $@ -D PRAC=$(PRAC) $<

# DO NOT DELETE

f_confirmacion_alum.o: main.h tipos.h instrucciones.h instrucciones.hi
f_confirmacion_alum.o: prediccion.h prediccion.hi prediccion_alum.hi
f_confirmacion_alum.o: presentacion.h presentacion.hi algoritmo.h
f_confirmacion_alum.o: f_busqueda.hi f_lanzamiento.hi f_lanzamiento_alum.hi
f_confirmacion_alum.o: f_ejecucion.hi f_transferencia.hi
f_confirmacion_alum.o: f_transferencia_alum.hi f_confirmacion.hi
f_confirmacion_alum.o: f_confirmacion_alum.hi
prediccion_alum.o: prediccion.h tipos.h prediccion.hi prediccion_alum.hi
prediccion_alum.o: main.h instrucciones.h instrucciones.hi presentacion.h
prediccion_alum.o: presentacion.hi

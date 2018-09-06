#######

CFLAGS_BISON	= -O2 -fno-strength-reduce
CFLAGS		= -O2 -fno-strength-reduce -W
YACCCFLAGS	= -Wno-unused -Wno-parentheses
CC		= gcc
SHELL		= /bin/sh
CDEPEND		= makedepend
LFLAGS	= 

####### Files

HEADERS =	main.h tipos.h
SOURCES =	main.c \
		input.yacc.y \
		input.lex.l \
		etiquetas.c \
		presentacion-html.c \
		presentacion-txt.c \
		mips.c

OBJECTS =	main.o \
		input.yacc.o \
		input.lex.o \
		etiquetas.o \
		presentacion-html.o \
		presentacion-txt.o \
		mips.o

TARGET	=	mips

####### Build rules

$(TARGET): proto $(OBJECTS)
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

%.o : %.c
	$(CC) -c $(CFLAGS) -o $@ -D PRAC=$(PRAC) $<

%.hi: %.c
	cproto $< > $@

### Para lex y yacc

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


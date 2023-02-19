reflex = ../reflex/RE-flex/src/reflex
reflexinc = ../reflex/RE-flex/include
reflexlib = ../reflex/RE-flex/lib
bison = bison

CC=gcc

CPP=g++

OBJECTS= \
   lex.yy.o \
   eprintf.o
#   polybasic.tab.o 

INCDIRS= \
   -I $(reflexinc)

LIBDIRS= \
   -L $(reflexlib)

LIBS= \
   -l reflex \
   -l quadmath

polybasic: polybasic.tab.h $(OBJECTS)
	$(CPP) $(OBJECTS) $(LIBDIRS) $(LIBS) -o polybasic

polybasic.tab.h: polybasic.tab.c

polybasic.tab.c: polybasic.y
	$(bison) -Wcounterexamples -H polybasic.y

lex.yy.cpp: polybasic.l polybasic.tab.h
	$(reflex) polybasic.l

.PHONY: clean
clean:
	rm -f lex.yy.cpp polybasic.tab.h polybasic.tab.c polybasic
	rm -f $(OBJECTS)

%.o : %.cpp
	$(CPP) -c $(INCDIRS) $<

%.o : %.c
	$(CC) -c $(INCDIRS) $<

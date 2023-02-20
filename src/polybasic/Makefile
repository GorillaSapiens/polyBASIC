reflex = ../reflex/RE-flex/src/reflex
reflexinc = ../reflex/RE-flex/include
reflexlib = ../reflex/RE-flex/lib
bison = bison

CC=gcc
CPP=g++
CFLAGS=-g

OBJECTS= \
   lex.yy.o \
   eprintf.o \
   main.o \
   polybasic.tab.o

INCDIRS= \
   -I $(reflexinc)

LIBDIRS= \
   -L $(reflexlib)

LIBS= \
   -l reflex \
   -l quadmath

polybasic: polybasic.tab.hpp $(OBJECTS)
	$(CPP) $(OBJECTS) $(LIBDIRS) $(LIBS) -o polybasic

polybasic.tab.hpp: polybasic.tab.cpp

polybasic.tab.cpp: polybasic.ypp
	$(bison) -Wcounterexamples -H polybasic.ypp

lex.yy.cpp: polybasic.l polybasic.tab.hpp
	$(reflex) --flex --bison --header-file=lex.yy.hpp polybasic.l

.PHONY: clean
clean:
	rm -f lex.yy.cpp lex.yy.hpp
	rm -f polybasic.tab.h polybasic.tab.c # why??
	rm -f polybasic.tab.cpp polybasic.tab.hpp # why???
	rm -f polybasic
	rm -f $(OBJECTS)

%.o : %.cpp
	$(CPP) $(CFLAGS) -c $(INCDIRS) $<

%.o : %.c
	$(CC) $(CFLAGS) -c $(INCDIRS) $<

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
   rational.o \
   dumptree.o \
   runtime_vars.o \
   runtime_lbls.o \
   runtime_for.o \
   runtime_data.o \
   runtime.o \
   flexdebug.o \
   hash.o \
   polybasic.tab.o

INCDIRS= \
   -I $(reflexinc)

LIBDIRS= \
   -L $(reflexlib)

LIBS= \
   -l reflex

polybasic: polybasic.tab.hpp $(OBJECTS)
	$(CPP) $(OBJECTS) $(LIBDIRS) $(LIBS) -o polybasic

polybasic.tab.hpp: polybasic.tab.cpp

polybasic.tab.cpp: polybasic.ypp
	$(bison) -Wcounterexamples -H polybasic.ypp

lex.yy.cpp: polybasic.l polybasic.tab.hpp
	$(reflex) -yy --unicode --header-file=lex.yy.hpp polybasic.l

mapping.h: mapping.pl polybasic.tab.hpp
	./mapping.pl < polybasic.tab.hpp > mapping.h

mapping2.h: mapping.h
	sed "s/enum yytokentype/int/g" mapping.h > mapping2.h

mapping3.h: mapping3.pl polybasic.ypp
	./mapping3.pl < polybasic.ypp | uniq > mapping3.h

main.o: mapping.h

flexdebug.o: mapping.h

dumptree.o: mapping2.h mapping3.h

.PHONY: todo
todo:
	./missing.pl | grep yes

.PHONY: clean
clean:
	rm -f lex.yy.cpp lex.yy.hpp
	rm -f polybasic.tab.cpp polybasic.tab.hpp
	rm -f polybasic
	rm -f mapping.h mapping2.h mapping3.h
	rm -f $(OBJECTS)

%.o : %.cpp
	$(CPP) $(CFLAGS) -c $(INCDIRS) $<

%.o : %.c
	$(CC) $(CFLAGS) -c $(INCDIRS) $<

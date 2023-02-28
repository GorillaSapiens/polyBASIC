reflex = ../reflex/RE-flex/src/reflex
reflexinc = ../reflex/RE-flex/include
reflexlib = ../reflex/RE-flex/lib
bison = bison
ucd = https://www.unicode.org/Public/UCD/latest/ucd/

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
   runtime_def.o \
   runtime_data.o \
   runtime.o \
   flexdebug.o \
   utf8casecmp.o \
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

mapping.h: mapping.pl polybasic.tab.hpp polybasic.ypp
	./mapping.pl > mapping.h

main.o: mapping.h

flexdebug.o: mapping.h

utf8casecmp.o: lowercase.h

.PHONY: todo
todo:
	./missing.pl | grep yes

lowercase.h: lowercase.pl UnicodeData.txt SpecialCasing.txt
	./lowercase.pl > lowercase.h

# see https://www.unicode.org/L2/L1999/UnicodeData.html for an explanation
# of this file format
UnicodeData.txt:
	wget $(ucd)UnicodeData.txt

SpecialCasing.txt:
	wget $(ucd)SpecialCasing.txt

.PHONY: clean
clean:
	rm -f lex.yy.cpp lex.yy.hpp
	rm -f polybasic.tab.cpp polybasic.tab.hpp
	rm -f polybasic
	rm -f mapping.h
	rm -f lowercase.h
	rm -f $(OBJECTS)

.PHONY: squeaky
squeaky:
	rm -f UnicodeData.txt SpecialCasing.txt

%.o : %.cpp
	$(CPP) $(CFLAGS) -c $(INCDIRS) $<

%.o : %.c
	$(CC) $(CFLAGS) -c $(INCDIRS) $<

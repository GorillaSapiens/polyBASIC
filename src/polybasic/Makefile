reflex = ../reflex/RE-flex/src/reflex
reflexinc = ../reflex/RE-flex/include
reflexlib = ../reflex/RE-flex/lib
bison = bison
ucd = https://www.unicode.org/Public/UCD/latest/ucd/

CC=gcc
CPP=g++
CFLAGS=-g

VERSION=0.90

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

all: polybasic errs.txt

errs.txt: *.cpp *.ypp *.l
	./eprintf.pl $^ | sort -u > errs.txt

polybasic: polybasic.tab.hpp $(OBJECTS)
	$(CPP) $(OBJECTS) $(LIBDIRS) $(LIBS) -o polybasic

polybasic.%.cpp polybasic.%.hpp : polybasic.ypp
	$(bison) -Wcounterexamples -H polybasic.ypp

lex.yy.cpp: polybasic.l polybasic.tab.hpp
	$(reflex) -yy --unicode --header-file=lex.yy.hpp polybasic.l

mapping.hpp: mapping.pl polybasic.tab.hpp polybasic.ypp
	./mapping.pl > mapping.hpp

main.o: mapping.hpp version.hpp

flexdebug.o: mapping.hpp

utf8casecmp.o: lowercase.hpp

.PHONY: todo
todo:
	./missing.pl | grep yes

lowercase.hpp: lowercase.pl UnicodeData.txt SpecialCasing.txt
	./lowercase.pl > lowercase.hpp

.PHONY: version.hpp
version.hpp:
	echo "#define VERSION \"$(VERSION)."`date +%Y.%m.%d.%H.%M.%S`"\"" > version.hpp

# see https://www.unicode.org/L2/L1999/UnicodeData.html for an explanation
# of this file format
UnicodeData.txt:
	wget $(ucd)UnicodeData.txt

SpecialCasing.txt:
	wget $(ucd)SpecialCasing.txt

.PHONY: depend
depend:
	makedepend $(INCDIRS) -Y *.cpp

.PHONY: clean
clean:
	rm -f lex.yy.cpp lex.yy.hpp
	rm -f polybasic.tab.cpp polybasic.tab.hpp
	rm -f polybasic
	rm -f mapping.hpp
	rm -f lowercase.hpp
	rm -f version.hpp
	rm -f $(OBJECTS)

.PHONY: squeaky
squeaky:
	rm -f UnicodeData.txt SpecialCasing.txt

%.o : %.cpp
	$(CPP) $(CFLAGS) -c $(INCDIRS) $<

%.o : %.c
	$(CC) $(CFLAGS) -c $(INCDIRS) $<

# DO NOT DELETE THIS LINE -- make depend depends on it.

dumptree.o: eprintf.hpp tree.hpp rational.hpp
eprintf.o: eprintf.hpp tree.hpp rational.hpp
flexdebug.o: tree.hpp rational.hpp flexdebug.hpp
hash.o: hash.hpp
main.o: eprintf.hpp tree.hpp rational.hpp dumptree.hpp runtime.hpp
main.o: flexdebug.hpp utf8casecmp.hpp
rational.o: rational.hpp
runtime.o: eprintf.hpp tree.hpp rational.hpp dumptree.hpp runtime_lbls.hpp
runtime.o: runtime_for.hpp runtime_def.hpp runtime_vars.hpp runtime_data.hpp
runtime.o: runtime.hpp
runtime_data.o: runtime_data.hpp rational.hpp
runtime_def.o: eprintf.hpp tree.hpp rational.hpp runtime_def.hpp dumptree.hpp
runtime_def.o: hash.hpp
runtime_for.o: runtime_for.hpp tree.hpp rational.hpp dumptree.hpp hash.hpp
runtime_lbls.o: runtime_lbls.hpp tree.hpp rational.hpp dumptree.hpp hash.hpp
runtime_vars.o: eprintf.hpp tree.hpp rational.hpp runtime_vars.hpp hash.hpp
utf8casecmp.o: utf8casecmp.hpp

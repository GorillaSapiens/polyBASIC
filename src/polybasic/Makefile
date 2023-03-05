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

polybasic.tab.cpp polybasic.tab.hpp : polybasic.ypp
	$(bison) -r all --debug -Wcounterexamples -H polybasic.ypp

lex.yy.cpp lex.yy.hpp: polybasic.l polybasic.tab.hpp
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
	rm -f Makefile.bak
	rm -f polybasic.output
	rm -f $(OBJECTS)

.PHONY: squeaky
squeaky:
	rm -f UnicodeData.txt SpecialCasing.txt

%.o : %.cpp
	$(CPP) $(CFLAGS) -c $(INCDIRS) $<

%.o : %.c
	$(CC) $(CFLAGS) -c $(INCDIRS) $<

# DO NOT DELETE THIS LINE -- make depend depends on it.

dumptree.o: eprintf.hpp tree.hpp rational.hpp polybasic.tab.hpp mapping.hpp
eprintf.o: eprintf.hpp tree.hpp rational.hpp
flexdebug.o: tree.hpp rational.hpp polybasic.tab.hpp flexdebug.hpp
flexdebug.o: mapping.hpp
hash.o: hash.hpp
lex.yy.o: ../reflex/RE-flex/include/reflex/matcher.h
lex.yy.o: ../reflex/RE-flex/include/reflex/absmatcher.h
lex.yy.o: ../reflex/RE-flex/include/reflex/convert.h
lex.yy.o: ../reflex/RE-flex/include/reflex/error.h
lex.yy.o: ../reflex/RE-flex/include/reflex/debug.h
lex.yy.o: ../reflex/RE-flex/include/reflex/input.h
lex.yy.o: ../reflex/RE-flex/include/reflex/utf8.h
lex.yy.o: ../reflex/RE-flex/include/reflex/traits.h
lex.yy.o: ../reflex/RE-flex/include/reflex/simd.h
lex.yy.o: ../reflex/RE-flex/include/reflex/pattern.h
lex.yy.o: ../reflex/RE-flex/include/reflex/bits.h
lex.yy.o: ../reflex/RE-flex/include/reflex/ranges.h
lex.yy.o: ../reflex/RE-flex/include/reflex/setop.h
lex.yy.o: ../reflex/RE-flex/include/reflex/flexlexer.h
lex.yy.o: ../reflex/RE-flex/include/reflex/abslexer.h tree.hpp rational.hpp
lex.yy.o: flexdebug.hpp polybasic.tab.hpp
main.o: eprintf.hpp tree.hpp rational.hpp dumptree.hpp polybasic.tab.hpp
main.o: mapping.hpp runtime.hpp flexdebug.hpp utf8casecmp.hpp version.hpp
polybasic.tab.o: eprintf.hpp tree.hpp rational.hpp dumptree.hpp lex.yy.hpp
polybasic.tab.o: safe_strdup.hpp polybasic.tab.hpp
rational.o: rational.hpp
runtime.o: eprintf.hpp tree.hpp rational.hpp polybasic.tab.hpp dumptree.hpp
runtime.o: runtime_lbls.hpp runtime_for.hpp runtime_def.hpp runtime_vars.hpp
runtime.o: runtime_data.hpp runtime.hpp
runtime_data.o: runtime_data.hpp rational.hpp
runtime_def.o: eprintf.hpp tree.hpp rational.hpp polybasic.tab.hpp
runtime_def.o: runtime_def.hpp dumptree.hpp hash.hpp
runtime_for.o: runtime_for.hpp tree.hpp rational.hpp dumptree.hpp hash.hpp
runtime_lbls.o: runtime_lbls.hpp tree.hpp rational.hpp dumptree.hpp hash.hpp
runtime_vars.o: eprintf.hpp tree.hpp rational.hpp runtime_vars.hpp
runtime_vars.o: polybasic.tab.hpp hash.hpp
utf8casecmp.o: utf8casecmp.hpp lowercase.hpp

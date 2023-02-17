reflex = ../reflex/RE-flex/src/reflex
reflexinc = ../reflex/RE-flex/include
reflexlib = ../reflex/RE-flex/lib
bison = bison

OBJECTS= \
   lex.yy.o \
   eprintf.o
#   polybasic.tab.o 

polybasic: polybasic.tab.h $(OBJECTS)
	g++ -I $(reflexinc) $(OBJECTS) -L $(reflexlib) -lreflex -o polybasic

polybasic.tab.h: polybasic.tab.c

polybasic.tab.c: polybasic.y
	$(bison) -H polybasic.y

lex.yy.cpp: polybasic.l
	$(reflex) --unicode polybasic.l

.PHONY: clean
clean:
	rm -f lex.yy.cpp polybasic.tab.h polybasic.tab.c polybasic
	rm -f $(OBJECTS)

%.o : %.cpp
	g++ -c -I $(reflexinc) $<

%.o : %.c
	gcc -c -I $(reflexinc) $<

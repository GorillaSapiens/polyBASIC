reflex = ../reflex/RE-flex/src/reflex
reflexinc = ../reflex/RE-flex/include
reflexlib = ../reflex/RE-flex/lib
bison = bison

polybasic: polybasic.tab.c polybasic.tab.h lex.yy.cpp
	g++ -I $(reflexinc) lex.yy.cpp -L $(reflexlib) -lreflex -o polybasic

polybasic.tab.h: polybasic.tab.c

polybasic.tab.c: polybasic.y
	$(bison) -H polybasic.y

lex.yy.cpp: polybasic.l
	$(reflex) --unicode polybasic.l

.PHONY: test
test:
	./do_tests.sh

.PHONY: clean
clean:
	rm -f lex.yy.cpp polybasic.tab.h polybasic.tab.c polybasic

reflex = ../RE-flex/RE-flex/src/reflex
reflexinc = ../RE-flex/RE-flex/include
reflexlib = ../RE-flex/RE-flex/lib

polybasic: lex.yy.cpp
	g++ -I $(reflexinc) lex.yy.cpp -L $(reflexlib) -lreflex -o polybasic

lex.yy.cpp: polybasic.l
	$(reflex) --unicode polybasic.l

.PHONY: test
test:
	./do_tests.sh

.PHONY: clean
clean:
	rm -f lex.yy.cpp polybasic

reflex = ../RE-flex/RE-flex/src/reflex
reflexinc = ../RE-flex/RE-flex/include
reflexlib = ../RE-flex/RE-flex/lib

pass1: lex.yy.cpp
	g++ -I $(reflexinc) lex.yy.cpp -L $(reflexlib) -lreflex -o pass1

lex.yy.cpp: pass1.l
	$(reflex) --unicode pass1.l

.PHONY: test
test:
	./do_tests.sh

.PHONY: clean
clean:
	rm -f lex.yy.cpp pass1

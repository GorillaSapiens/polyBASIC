reflex = ../RE-flex/RE-flex/src/reflex
reflexinc = ../RE-flex/RE-flex/include
reflexlib = ../RE-flex/RE-flex/lib

pass1: lex.y.cpp
	g++ -I $(reflexinc) lex.yy.cpp -L $(reflexlib) -lreflex -o pass1

lex.y.cpp: pass1.lex
	$(reflex) pass1.lex

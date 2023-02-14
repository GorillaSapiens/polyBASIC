reflex = ../RE-flex/RE-flex/src/reflex
reflexinc = ../RE-flex/RE-flex/include
reflexlib = ../RE-flex/RE-flex/lib

pass1:
	$(reflex) pass1.lex
	g++ -I $(reflexinc) lex.yy.cpp -L $(reflexlib) -lreflex -o pass1

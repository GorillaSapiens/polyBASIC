%{
   // C decls go here
%}

%locations

/* reserved words */
%token yyBASE
%token yyDATA
%token yyDEF
%token yyDIM
%token yyEND
%token yyFOR
%token yyGO
%token yyGOSUB
%token yyGOTO
%token yyIF
%token yyINPUT
%token yyLET
%token yyNEXT
%token yyON
%token yyOPTION
%token yyPRINT
%token yyRANDOMIZE
%token yyREAD
%token yyREM
%token yyRESTORE
%token yyRETURN
%token yySTEP
%token yySTOP
%token yySUB
%token yyTHEN
%token yyTO
/* function names, not many, so make 'em tokens */
%token yyABS
%token yyATN
%token yyCOS
%token yyEXP
%token yyINT
%token yyLOG
%token yyRND
%token yySGN
%token yySIN
%token yySQR
%token yyTAN
/* and other stuff */
%token yyIDENTIFIER

%%

program: /* empty */
;

%%


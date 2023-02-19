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
%token yyDBL
%token yyEXP
%token yyINT
%token yyLOG
%token yyRND
%token yySGN
%token yySIN
%token yySQR
%token yyTAN
/* and other stuff */

%token yyDVAR
%token yySVAR
%token yyIVAR
%token yyRVAR

%token yyDOUBLE
%token yySTRING
%token yyINTEGER
%token yyRATIONAL

%token yyRELATION
%token yyASSIGN

%token yyPLUSMINUS
%token yyMULTDIV

%token yyLABEL
%token yyEOL

%left yyMULTDIV
%left yyPLUSMINUS

%%

program       : stmtlist
              ;

stmtlist      : stmt
              | stmtlist stmt
              ;

stmt          : yyLABEL assignexpr yyEOL
              | assignexpr yyEOL
              ;

assignexpr    : yyDVAR yyASSIGN dvalexpr
              | yyRVAR yyASSIGN rvalexpr
              | yySVAR yyASSIGN svalexpr
              | yyIVAR yyASSIGN ivalexpr
              ;

dvalexpr      : yyABS '(' dvalexpr ')'
              | yyRND '(' ')'
              | yyATN '(' dvalexpr ')'
              | yyCOS '(' dvalexpr ')'
              | yyEXP '(' dvalexpr ')'
              | yyLOG '(' dvalexpr ')'
              | yySIN '(' dvalexpr ')'
              | yySQR '(' dvalexpr ')'
              | yyTAN '(' dvalexpr ')'
              | yyDBL '(' ivalexpr ')'
              | yyDBL '(' rvalexpr ')'
              | yyDBL '(' svalexpr ')'
              | dvalexpr yyPLUSMINUS dvalexpr
              | dvalexpr yyMULTDIV dvalexpr
              | '(' dvalexpr ')'
              ;

rvalexpr      : yyABS '(' rvalexpr ')'
              | rvalexpr yyPLUSMINUS rvalexpr
              | rvalexpr yyMULTDIV rvalexpr
              | '(' rvalexpr ')'
              ;

ivalexpr      : yyABS '(' ivalexpr ')'
              | yyINT '(' dvalexpr ')'
              | yyINT '(' rvalexpr ')'
              | yyINT '(' svalexpr ')'
              | yySGN '(' ivalexpr ')'
              | yySGN '(' dvalexpr ')'
              | yySGN '(' rvalexpr ')'
              | ivalexpr yyPLUSMINUS ivalexpr
              | ivalexpr yyMULTDIV ivalexpr
              | '(' ivalexpr ')'
              ;

svalexpr      : svalexpr '+' svalexpr
              | '(' svalexpr ')'
              ;

%%


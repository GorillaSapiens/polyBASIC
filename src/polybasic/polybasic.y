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

%token yyIPSEP

%token yyLABEL
%token yyEOL

%left yyMULTDIV
%left yyPLUSMINUS
%left '+'

%%

program       : linelist
              ;

linelist      : line
              | linelist line
              ;

line          : yyLABEL stmt yyEOL
              | stmt yyEOL
              ;

stmt          : assignexpr
              | letexpr
              | controlstmt
              | repeatstmt
              | printstmt
              | inputstmt
              | rrdata
              | randomize
              | rem
              ;

rem           : yyREM
              ;

randomize     : yyRANDOMIZE
              ;

rrdata        : yyREAD inputlist
              | yyRESTORE
              | yyDATA vallist
              ;

vallist       : yyINTEGER
              | yyDOUBLE
              | yyRATIONAL
              | yySTRING
              | vallist yyIPSEP yyINTEGER
              | vallist yyIPSEP yyDOUBLE
              | vallist yyIPSEP yyRATIONAL
              | vallist yyIPSEP yySTRING
              ;

printstmt     : yyPRINT printlist
              ;

printlist     : ivalexpr
              | dvalexpr
              | rvalexpr
              | svalexpr
              | printlist yyIPSEP ivalexpr
              | printlist yyIPSEP dvalexpr
              | printlist yyIPSEP rvalexpr
              | printlist yyIPSEP svalexpr
              ;

inputstmt     : yyINPUT inputlist
              ;

inputlist     : yyIVAR
              | yyDVAR
              | yyRVAR
              | yySVAR
              | inputlist yyIPSEP yyIVAR
              | inputlist yyIPSEP yyDVAR
              | inputlist yyIPSEP yyRVAR
              | inputlist yyIPSEP yySVAR
              ;

controlstmt   : yyGO yyTO yyLABEL
              | yyGOTO yyLABEL
              | yyGO yySUB yyLABEL
              | yyGOSUB yyLABEL
              | yyIF ivalexpr yyRELATION ivalexpr yyTHEN yyLABEL
              | yyIF dvalexpr yyRELATION dvalexpr yyTHEN yyLABEL
              | yyIF rvalexpr yyRELATION rvalexpr yyTHEN yyLABEL
              | yyIF svalexpr yyRELATION svalexpr yyTHEN yyLABEL
              | yyON ivalexpr yyGO yyTO labellist
              | yyON ivalexpr yyGOTO labellist
              | yyON ivalexpr yyGO yySUB labellist
              | yyON ivalexpr yyGOSUB labellist
              | yyRETURN
              | yySTOP
              | yyEND
              ;

repeatstmt    : yyFOR yyIVAR yyASSIGN ivalexpr yyTO ivalexpr
              | yyFOR yyIVAR yyASSIGN ivalexpr yyTO ivalexpr yySTEP ivalexpr
              | yyNEXT yyIVAR
              ;

labellist     : yyLABEL
              | labellist yyLABEL
              ;

letexpr       : yyLET yyDVAR yyASSIGN dvalexpr
              | yyLET yyRVAR yyASSIGN rvalexpr
              | yyLET yySVAR yyASSIGN svalexpr
              | yyLET yyIVAR yyASSIGN ivalexpr
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
              | yyDVAR
              ;

rvalexpr      : yyABS '(' rvalexpr ')'
              | rvalexpr yyPLUSMINUS rvalexpr
              | rvalexpr yyMULTDIV rvalexpr
              | '(' rvalexpr ')'
              | yyRVAR
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
              | yyIVAR
              ;

svalexpr      : svalexpr '+' svalexpr
              | '(' svalexpr ')'
              | yySVAR
              ;

%%


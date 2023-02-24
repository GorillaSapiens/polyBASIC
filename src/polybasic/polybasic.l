%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <errno.h>

#include "tree.h"

//#undef YY_USER_ACTION
//#define YY_USER_ACTION                                       \
//  yylloc.first_line = yylloc.last_line;                      \
//  yylloc.first_column = yylloc.last_column;                  \
//  if (yylloc.first_line == yylineno)                         \
//     yylloc.last_column += yyleng;                           \
//  else {                                                     \
//     int col;                                                \
//     for (col = 1; yytext[yyleng - col] != '\n'; ++col) {}   \
//     yylloc.last_column = col;                               \
//     yylloc.last_line = yylineno;                            \
//  }

#include "polybasic.tab.hpp"
#include "reflex/flexlexer.h"

// required fwd decls
const char *has_tuple(const char *a);
int is_reserved_label(const char *a);
enum yytokentype is_reserved_varname(char sigil, const char *a, enum yytokentype retval);
enum yytokentype is_reserved_word(const char *a);

//#define DEBUG printf
#define DEBUG
%}

%option flex bison unicode yylineno
//%option bison
//%option unicode
//%option yylineno



WHITESPACE  [ \t]+

/* ECMA-55 §6 */
/* definition of "constant" from page 7 of the ECMA-55 document */
/* NB: we have deviated by allowing escaped characters in strings */
STRING   \"(\\.|[^"\\])*\"

R_ZERO      [#][0]
R_INT       [#][+-]?[1-9][0-9]*
R_ZFRAC     [#][0][/][1-9][0-9]*
R_FRAC      [#][+-]?[1-9][0-9]*[/][1-9][0-9]*
R_FULL      [#][+-]?[0-9]+['][0-9]+[/][1-9][0-9]*
RATIONAL    {R_ZERO}|{R_INT}|{R_ZFRAC}|{R_FRAC}|{R_FULL}

INTEGER  ([+-]?[0-9]+)

DOUBLE   [+-]?(([0-9]+[.]?)|(([0-9]+)?[.][0-9]+))(E[+-]?[0-9]+)?

/* ECMA-55 §4.2 */

/* this gets a little odd, because we've had to eliminate the notion */
/* of an "unquoted string" to allow, well, everything unicode */

/* relations given by ECMA-55 §12.2, modified */
RELATION (==|!=|<>|<|>|>=|<=)

ASSIGN ":="

/* any single character passed straight up to bison */
SINGLE [-+*/()]

IPSEP [,;]

/* any valid multicharacter thing */
VARNAME  [\p{Letter}\p{IsMiscellaneousSymbolsandPictographs}\p{IsMiscellaneousSymbols}\p{IsEmoticons}\p{IsSupplementalSymbolsandPictographs}]([\p{Letter}\p{IsMiscellaneousSymbolsandPictographs}\p{IsMiscellaneousSymbols}\p{IsEmoticons}\p{IsSupplementalSymbolsandPictographs}\p{Number}_])*

// unused
// /* any single character appearing by iteslf */
// RUNE     [$%|&'?^_.]

EOL      [\r\n]{1,2}

%%

{WHITESPACE} { /* ignore */ }

{VARNAME}   {
               enum yytokentype ret = is_reserved_varname('\0', yytext, YYVARNAME);
               DEBUG("VARNAME='%s' %d\n", yytext, ret);
               return ret;
            }

{RATIONAL}  {
               DEBUG("RATIONAL=%s\n", yytext);
               return YYRATIONAL;
            }

{STRING}    {
               DEBUG("STRING=%s\n", yytext);
               return YYSTRING;
            }

{INTEGER}   {
               DEBUG("INTEGER=%s\n", yytext);
               return YYINTEGER;
            }

{DOUBLE}    {
               DEBUG("DOUBLE=%s\n", yytext);
               return YYDOUBLE;
            }

{ASSIGN}    {
               DEBUG("token = '%s' %d\n", yytext, YYASSIGN);
               return YYASSIGN;
            }

{RELATION}  {
               DEBUG("token = '%s' %d\n", yytext, YYRELATION);
               return YYRELATION;
            }

{SINGLE}    {
               DEBUG("token = '%s' %d\n", yytext, yytext[0]);
               return yytext[0];
            }

{IPSEP}     {
               DEBUG("token = '%s' %d\n", yytext, YYIPSEP);
               return YYIPSEP;
            }

{EOL}       {
               DEBUG("token = 'EOL' %d\n", YYEOL);
               return YYEOL;
            }

.           {
               printf("YYerrror %d ❮%s❯\n", yylineno, yytext);
               return YYerror;
            }

%%


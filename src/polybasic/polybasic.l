%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <errno.h>

#include "tree.hpp"
#include "flexdebug.hpp"

#undef YY_USER_ACTION
#define YY_USER_ACTION                                       \
  yylloc.first_line = yylloc.last_line;                      \
  yylloc.first_column = yylloc.last_column;                  \
  if (yylloc.first_line == yylineno)                         \
     yylloc.last_column += yyleng;                           \
  else {                                                     \
     int col;                                                \
     for (col = 1; yytext[yyleng - col] != '\n'; ++col) {}   \
     yylloc.last_column = col;                               \
     yylloc.last_line = yylineno;                            \
  }

#include <reflex/flexlexer.h>

#include "polybasic.tab.hpp"

// required fwd decls
const char *has_tuple(const char *a);
int is_reserved_label(const char *a);
enum yytokentype is_reserved_varname(char sigil, const char *a, enum yytokentype retval);
enum yytokentype is_reserved_word(const char *a);

%}

%option flex bison unicode yylineno

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

I_ZERO      ([0])
I_NONZERO   ([1-9][0-9]*)
INTEGER     {I_ZERO}|{I_NONZERO}

D_ZERO      ([0][.][0]*)
D_NONZERO   ([1-9][0-9]*[.])
D_FRAC      ([0-9]+)
D_EXP       ([Ee][+-]?[1-9][0-9]*)
DOUBLE      {D_ZERO}|({D_NONZERO}{D_FRAC}?{D_EXP}?)|([.]{D_FRAC}{D_EXP}?)

/* ECMA-55 §4.2 */

/* this gets a little odd, because we've had to eliminate the notion */
/* of an "unquoted string" to allow, well, everything unicode */

/* relations given by ECMA-55 §12.2, modified */
RELATION (==|!=|<>|<|>|>=|<=)

ASSIGN ":="

/* any single character passed straight up to bison */
/* ECMA-116 uses & for string concatenation */
SINGLE [:&-+*/^()]

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
               flexdebug(yytext, (int) ret, yylineno, yylloc.first_column);
               return ret;
            }

{RATIONAL}  {
               flexdebug(yytext, (int) YYRATIONAL, yylineno, yylloc.first_column);
               return YYRATIONAL;
            }

{STRING}    {
               flexdebug(yytext, (int) YYSTRING, yylineno, yylloc.first_column);
               return YYSTRING;
            }

{INTEGER}   {
               flexdebug(yytext, (int) YYINTEGER, yylineno, yylloc.first_column);
               return YYINTEGER;
            }

{DOUBLE}    {
               flexdebug(yytext, (int) YYDOUBLE, yylineno, yylloc.first_column);
               return YYDOUBLE;
            }

{ASSIGN}    {
               flexdebug(yytext, (int) YYASSIGN, yylineno, yylloc.first_column);
               return YYASSIGN;
            }

{RELATION}  {
               flexdebug(yytext, (int) YYRELATION, yylineno, yylloc.first_column);
               return YYRELATION;
            }

{SINGLE}    {
               flexdebug(yytext, (int) yytext[0], yylineno, yylloc.first_column);
               return yytext[0];
            }

{IPSEP}     {
               flexdebug(yytext, (int) YYIPSEP, yylineno, yylloc.first_column);
               return YYIPSEP;
            }

{EOL}       {
               flexdebug(yytext, (int) YYEOL, yylineno, yylloc.first_column);
               return YYEOL;
            }

.           {
               flexdebug(yytext, (int) yytext[0], yylineno, yylloc.first_column);
               return yytext[0];
            }
%%


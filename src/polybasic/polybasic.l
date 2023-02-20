%option flex
%option bison
%option unicode
%option yylineno

%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <errno.h>

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

#include "polybasic.tab.hpp"
#include "reflex/flexlexer.h"

// required fwd decls
const char *has_tuple(const char *a);
int is_reserved_label(const char *a);
enum yytokentype is_reserved_varname(char sigil, const char *a, enum yytokentype retval);
enum yytokentype is_reserved_word(const char *a);

%}

WHITESPACE  [ \t]

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
RELATION (==|<>|<|>|>=|<=)

ASSIGN (:=)

/* any single character passed straight up to bison */
PAREN [()]

PLUSMINUS [-+]

MULTDIV [*/]

IPSEP [,;]

/* any single character appearing by iteslf */
RUNE     [!#$%&',;?^_.]

/* any valid multicharacter thing */
DVAR     [\p{Letter}]([\p{Letter}\p{Number}_])*
IVAR     [\p{Letter}]([\p{Letter}\p{Number}_])*[%]
RVAR     [\p{Letter}]([\p{Letter}\p{Number}_])*[#]
SVAR     [\p{Letter}]([\p{Letter}\p{Number}_])*[\$]

LABEL    (^[\p{Letter}]([\p{Letter}\p{Number}_])*:)|(^[0-9]+[: \t])

EOL      [\r\n]{1,2}

%%

{WHITESPACE} { /* ignore */ }

{RVAR}      { return is_reserved_varname('#',  yytext, YYRVAR); }
{SVAR}      { return is_reserved_varname('$',  yytext, YYSVAR); }
{IVAR}      { return is_reserved_varname('%',  yytext, YYIVAR); }
{DVAR}      { return is_reserved_varname('\0', yytext, YYDVAR); }

{RATIONAL}  { return YYRATIONAL; }
{STRING}    { return YYSTRING; }
{INTEGER}   { return YYINTEGER; }
{DOUBLE}    { return YYDOUBLE; }

{ASSIGN}    { return YYASSIGN; }
{RELATION}  { return YYRELATION; }


{LABEL}     {
               if (!is_reserved_label(yytext)) {
                  return YYLABEL;
               }
               else {
                  return YYerror;
               }
            }

{PAREN}     { return yytext[0]; }

{PLUSMINUS} { return YYPLUSMINUS; }

{MULTDIV}   { return YYMULTDIV; }

{IPSEP}     { return YYIPSEP; }

{EOL}       { return YYEOL; }

.           { printf("ummm %d ❮%s❯\n", yylineno, yytext); return YYerror; }

%%


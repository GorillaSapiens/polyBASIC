%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <errno.h>

#include "polybasic.tab.h"
#include "reflex/flexlexer.h"

int mylineno = 0;

// required fwd decls
const char *has_tuple(const char *a);
int is_reserved_label(const char *a);
enum yytokentype is_reserved_word(const char *a);

%}

%o flex

WHITESPACE  [ \t]

/* ECMA-55 §6 */
/* definition of "constant" from page 7 of the ECMA-55 document */
/* NB: we have deviated by allowing escaped characters in strings */
STRING   \"(\\.|[^"\\])*\"
NUMBER   [+-]?(([0-9]+[.]?)|(([0-9]+)?[.][0-9]+))(E[+-]?[0-9]+)?
CONSTANT {STRING}|{NUMBER}

/* ECMA-55 §4.2 */

/* this gets a little odd, because we've had to eliminate the notion */
/* of an "unquoted string" to allow, well, everything unicode */

/* relations given by ECMA-55 §12.2, modified */
RELATION (==|<>|<|>|>=|<=)

ASSIGNMENT (:=)

/* any single character passed straight up to bison */
OKSINGLE [-+*/()]

/* any single character appearing by iteslf */
RUNE     [!#$%&',:;?^_.]

/* any valid multicharacter thing */
WORD     [\p{Letter}]([\p{Letter}\p{Number}_])*

LABEL    (^[\p{Letter}]([\p{Letter}\p{Number}_])*:)|(^[0-9]+[: \t])

EOL      [\r\n]{1,2}

%%

{WHITESPACE} { /* ignore */ }

{CONSTANT}   { printf("constant: ❮%s❯\n", yytext); }

{RELATION}   { printf("relation: ❮%s❯\n", yytext); }

{ASSIGNMENT} { printf("assign  : ❮%s❯\n", yytext); }

{LABEL}      {
                if (!is_reserved_label(yytext)) {
                   printf("label   : ❮%s❯\n", yytext);
                }
                else {
                   printf("ERROR   : ❮%s❯\n", yytext);
                }
             }

{WORD}      {
               const char *alias = has_tuple(yytext);
               int reserved = is_reserved_word(yytext);
               if (alias) {
                  printf("word    : ❮%s➜%s❯ %d\n", yytext, alias, reserved);
               }
               else {
                  printf("word    : ❮%s❯ %d\n", yytext, reserved);
               }
            }

{OKSINGLE}  {
               printf("oksingle: ❮%s❯\n", yytext);
               // just remember to return the character here!
            }

{EOL}       {
               mylineno++;
               printf("❮EOL❯\n");
            }

.          { printf("ummm ❮%s❯\n", yytext); }

%%

// some reserved words and their tokens
static const struct {
   const char *name;
   enum yytokentype token;
} reserved[] = {
   { "BASE", yyBASE },
   { "DATA", yyDATA },
   { "DEF", yyDEF },
   { "DIM", yyDIM },
   { "END", yyEND },
   { "FOR", yyFOR },
   { "GO", yyGO },
   { "GOSUB", yyGOSUB },
   { "GOTO", yyGOTO },
   { "IF", yyIF },
   { "INPUT", yyINPUT },
   { "LET", yyLET },
   { "NEXT", yyNEXT },
   { "ON", yyON },
   { "OPTION", yyOPTION },
   { "PRINT", yyPRINT },
   { "RANDOMIZE", yyRANDOMIZE },
   { "READ", yyREAD },
   { "REM", yyREM },
   { "RESTORE", yyRESTORE },
   { "RETURN", yyRETURN },
   { "STEP", yySTEP },
   { "STOP", yySTOP },
   { "SUB", yySUB },
   { "THEN", yyTHEN },
   { "TO", yyTO },
   { "ABS", yyABS },
   { "ATN", yyATN },
   { "COS", yyCOS },
   { "EXP", yyEXP },
   { "INT", yyINT },
   { "LOG", yyLOG },
   { "RND", yyRND },
   { "SGN", yySGN },
   { "SIN", yySIN },
   { "SQR", yySQR },
   { "TAN", yyTAN }
};

// a simple linked list of tuples
// because i'm lazy,
// efficiency is not required,
// and the OS will free them at the end

struct Tuple;
typedef struct Tuple {
   const char *english;
   const char *translation;
   struct Tuple *next;
} Tuple;

Tuple *tuple_head = NULL;

void add_tuple(const char *english, const char *translation) {
   Tuple *tuple = (struct Tuple *) malloc(sizeof(struct Tuple));
   tuple->english = strdup(english);
   tuple->translation = strdup(translation);
   tuple->next = tuple_head;
   tuple_head = tuple;
}

const char *has_tuple(const char *token) {
   for (Tuple *p = tuple_head; p; p = p->next) {
      if (!strcmp(token, p->english)) {
         return p->translation;
      }
      if (!strcmp(token, p->translation)) {
         return p->english;
      }
   }
   return NULL;
}

enum yytokentype is_reserved_word(const char *a) {
   const char *proper = NULL;

   // find the tuple that matches this word.
   for (Tuple *p = tuple_head; p; p = p->next) {
      if (!strcmp(p->translation, a)) {
         proper = p->english;
         break;
      }
      if (!strcmp(p->english, a)) {
         proper = p->translation;
         break;
      }
   }

   // now see if there are any matches
   for (int i = 0; i < (sizeof(reserved)/sizeof(reserved[0])); i++) {
      if (!strcmp(reserved[i].name, proper ? proper : a)) {
         return reserved[i].token;
      }
   }
   return (enum yytokentype) 0;
}

int is_reserved_label(const char *a) {
   // we trust the parser if there is no colon
   if (!strchr(a, ':')) {
      return 0;
   }

   // now we need to check tuples.

   // save some time, copy the token, minus the colon
   int len = strlen(a);
   char *copy = (char *) alloca(len + 1);
   strcpy(copy, a);
   copy[len - 1] = 0;

   return is_reserved_word(copy);
}

int directory_exists(const char *path) {
   DIR* dir = opendir(path);
   if (dir) {
      closedir(dir);
      return 1;
   }
   return 0;
}

char *trim(char *in) {
   while (*in && isspace(*in)) {
      in++;
   }
   if (*in) {
      char *end = in + strlen(in) - 1;
      while (end > in && isspace(*end)) {
         *end = 0;
         end--;
      }
   }
   return in;
}

void read_translations(FILE *f) {
   char buf[16384];
   while (fgets(buf, sizeof(buf), f) == buf) {
      char *s;
      if ((s = /*assignment*/ strchr(buf, '#'))) {
         *s = 0;
      }
      if ((s = /*assignment*/ strstr(buf, "<="))) {
         *s = 0;
         char *english = trim(buf);
         char *translation = trim(s+2);
         //printf("TUPLE |%s|%s|\n", a, b);
         add_tuple(english,translation);
      }
   }
}

void load_translations(const char *language) {
   const char *path = getenv("POLYBASICPATH");
   if (path == NULL) {
      fprintf(stderr,
         "POLYBASICPATH environment variable not set.\n");
      exit(-1);
   }
   if (!directory_exists(path)) {
      fprintf(stderr,
         "cannot access directory %s.\n", path);
      exit(-1);
   }

   char full_path[16384];
   snprintf(full_path, sizeof(full_path), "%s/%s.txt", path, language);

   FILE *f = fopen(full_path, "r");
   if (f) {
      read_translations(f);
      fclose(f);
   }
   else {
      fprintf(stderr,
         "unable to open %s for reading. "
         "please check POLYBASICPATH and/or language settings.\n",
         full_path);
      exit(-1);
   }
}

int main(int argc, char **argv) {
   char *language = getenv("POLYBASICLANG");
   if (language == NULL) {
      if (argc != 3) {
         fprintf(stderr,
            "POLYBASICLANG not set, and no language "
            "given on command line.  exiting.\n");
         exit(-1);
      }
      language = argv[1];
   }
   load_translations(language);

   FILE *in = NULL;

   if (argc > 1) {
      in = fopen(argv[1], "r");

      if (in == NULL) {
         fprintf(stderr,
            "unable to open file %s\n", argv[1]);
         exit(-1);
      }
   }

   // this is the part we've all been waiting for...

   yyFlexLexer foo;
   if (in) {
      foo.yylex(in);
   }
   else {
      foo.yylex();
   }

   if (in) {
      fclose(in);
   }
}


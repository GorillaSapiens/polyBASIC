%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <errno.h>

#include "reflex/flexlexer.h"

// required fwd decls
const char *has_tuple(const char *a);

%}

%o flex

/* ECMA-55 §6 */
/* definition of "constant" from page 7 of the ECMA-55 document */
/* NB: we have deviated by allowing escaped characters in strings */
STRING   \"(\\.|[^"\\])*\"
NUMBER   [+-]?(([0-9]+[.]?)|(([0-9]+)?[.][0-9]+))(E[+-]?[0-9]+)?
CONSTANT {STRING}|{NUMBER}

/* ECMA-55 §4.2 */

/* this gets a little odd, because we've had to eliminate the notion */
/* of an "unquoted string" to allow, well, everything unicode */

/* any single character appearing by iteslf */
RUNE     [!#$%&'()*,/:;<=>?^_+-.]

/* any valid multicharacter thing */
WORD     [\p{Letter}]([\p{Letter}\p{Number}_])*

CRLF     [\r\n]{1,2}

%%

{CONSTANT}   { printf("constant: ❮%s❯\n", yytext); }
{RUNE}       { printf("rune    : ❮%s❯\n", yytext); }
{WORD}       {
                const char *alias = has_tuple(yytext);
                if (alias) {
                   printf("word    : ❮%s➜%s❯\n", yytext, alias);
                }
                else {
                   printf("word    : ❮%s❯\n", yytext);
                }
             }

{CRLF}     { /* ignore */ }

.          { printf("ummm ==%s==\n", yytext); }

%%

// a simple linked list of tuples
// because i'm lazy,
// efficiency is not required,
// and the OS will free them at the end

struct Tuple;
typedef struct Tuple {
   const char *a;
   const char *b;
   struct Tuple *next;
} Tuple;

Tuple *tuple_head = NULL;

void add_tuple(const char *a, const char *b) {
   Tuple *tuple = (struct Tuple *) malloc(sizeof(struct Tuple));
   tuple->a = strdup(a);
   tuple->b = strdup(b);
   tuple->next = tuple_head;
   tuple_head = tuple;
}

const char *has_tuple(const char *a) {
   for (Tuple *p = tuple_head; p; p = p->next) {
      if (!strcmp(a, p->a)) {
         return p->b;
      }
      if (!strcmp(a, p->b)) {
         return p->a;
      }
   }
   return NULL;
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
         char *a = trim(buf);
         char *b = trim(s+2);
         //printf("TUPLE |%s|%s|\n", a, b);
         add_tuple(a,b);
      }
   }
}

void load_translations(const char *language) {
   const char *path = getenv("POLYECMA55PATH");
   if (path == NULL) {
      fprintf(stderr,
         "POLYECMA55PATH environment variable not set.\n");
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
         "please check POLYECMA55 and/or language settings.\n",
         full_path);
      exit(-1);
   }
}

int main(int argc, char **argv) {
   char *language = getenv("POLYECMA55");
   if (language == NULL) {
      if (argc != 3) {
         fprintf(stderr,
            "POLYECMA55 not set, and no language "
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


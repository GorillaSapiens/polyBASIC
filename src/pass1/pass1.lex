%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <errno.h>

#include "reflex/flexlexer.h"

%}

%o flex

STRING   \"(\\.|[^"\\])*\"
NUMBER   [+-]?[0-9]+([.]([0-9]+))?(E[+-]?[0-9]+)?

%%

{STRING}   { printf("string: ==%s==\n", yytext); }
{NUMBER}   { printf("number: ==%s==\n", yytext); }
.          { printf("ummm %s\n", yytext); }

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
      if (buf[0] != '#' && (s = /*assignment*/ strstr(buf, "<="))) {
         *s = 0;
         char *a = trim(buf);
         char *b = trim(s+2);
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

   yyFlexLexer foo;
   foo.yylex();
}


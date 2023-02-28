#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <ctype.h>
#include <errno.h>

#include "eprintf.hpp"
#include "tree.hpp"
#include "dumptree.hpp"
#include "polybasic.tab.hpp"
#include "mapping.hpp"
#include "runtime.hpp"
#include "flexdebug.hpp"
#include "utf8casecmp.hpp"

extern FILE *yyin;
extern Tree *programtree;

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
#ifdef CASE_MUST_MATCH
      if (reserved[i].name && !strcmp(reserved[i].name, proper ? proper : a)) {
         return reserved[i].token;
      }
#else
      if (reserved[i].name && !utf8casecmp(reserved[i].name, proper ? proper : a)) {
         return reserved[i].token;
      }
#endif
   }
   return (enum yytokentype) 0;
}

enum yytokentype is_reserved_varname(char sigil, const char *a, enum yytokentype retval) {
   char copy[128];
   strcpy(copy, a);
   if (sigil) {
      char *s = strchr(copy, sigil);
      if (s) {
         *s = 0;
      }
   }
   enum yytokentype token = is_reserved_word(copy);
   if (token) {
      if (!sigil) {
         return token;
      }
      else {
         return YYerror;
      }
   }
   else {
      return retval;
   }
}

int is_reserved_label(const char *a) {
   // we trust the parser if there is no pipe
   if (!strchr(a, '|')) {
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

const char *find_translations(void) {
   static const char *possibilities[] = {
      "./translations",
      "../translations",
      NULL
   };

   for (int i = 0; possibilities[i]; i++) {
      if (directory_exists(possibilities[i])) {
         return possibilities[i];
      }
   }
   return NULL;
}

void load_translations(const char *language) {
   const char *path = getenv("POLYBASICPATH");
   if (path == NULL) {
      path = find_translations();
   }
   if (!directory_exists(path)) {
      fprintf(stderr,
         "cannot access directory %s.\n", path);
      exit(-1);
   }

   char full_path[16384];
   snprintf(full_path, sizeof(full_path), "%s/%s.pbt", path, language);

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

const char *shortname(const char *arg0) {
   const char *s = strrchr(arg0, '/');
   if (s) {
      s++;
   }
   else {
      s = arg0;
   }

   return s;
}

[[ noreturn ]] void usage(const char *arg0) {
   printf("Usage: %s [-f] [-t <n>] [-l <language>] [<input.bas>]\n", shortname(arg0));
   printf("      -f : debug flex parser output, and then run program\n");
   printf("      -t : dump parse tree for line <n>, do not run program\n");
   printf("           n=0 will dump the entire tree\n");
   printf("      -l : specify language, overriding POLYBASICLANG env variable\n");
   printf("      if <input.bas> is omitted, read program from STDIN.\n");
   printf("         this is not recommended, and may not play well with INPUT statements.\n");
   exit(0);
}

[[ noreturn ]] void version(const char *arg0) {
#include "version.hpp"
   printf("%s version %s\n", shortname(arg0), VERSION);
   exit(0);
}

int main(int argc, char **argv) {
   int treedebug = -1;
   char *language = getenv("POLYBASICLANG");

   char *arg0 = argv[0];

   // skip program name
   argc--; argv++;

   while(argc && argv[0][0] == '-') {
      switch (argv[0][1]) {
         case 'f':
            flexdebug_enable = 1;
            break;
         case 't':
            treedebug = atoi(argv[1]);
            argc--; argv++;
            break;
         case 'l':
            language = argv[1];
            if (language == NULL) {
               fprintf(stderr, "-l requires a language.\n");
            }
            argc--; argv++;
            break;
         case 'v':
            version(arg0); // calls exit, never returns
            break;
         case 'g':
            guru_enabled = true;
            GURU;
            break;
         case 'h':
         case '?':
         default:
            usage(arg0); // calls exit, never returns
            break;
      }

      argc--; argv++;
   }

   if (language == NULL) {
      fprintf(stderr,
            "POLYBASICLANG not set, and no language "
            "given on command line.  exiting.\n");
      exit(-1);
   }
   load_translations(language);

   FILE *in = NULL;

   if (argv[0]) {
      in = fopen(argv[0], "r");

      if (in == NULL) {
         fprintf(stderr,
               "unable to open file %s\n", argv[0]);
         exit(-1);
      }
   }

   // this is the part we've all been waiting for...

   if (in != NULL) {
      yyin = in;
   }

   int parser_result = yyparse();

   if (in) {
      fclose(in);
   }

   if (parser_result) {
      printf("failure\n");
   }
   else if (treedebug != -1) {
      dumptree(programtree, treedebug);
   }
   else {
      runtree(programtree);
   }
}

int yywrap(void) {
   return 1;
}

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

bool void_enabled = false;

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

// returns strdup()'d mem, but we're probably
// about to exit anyway...
const char *eop2string(int op) {
   char buffer[4096];
   if (op >= ' ' && op <= '~') {
      buffer[0] = op;
      buffer[1] = 0;
      return strdup(buffer);
   }
   for (int i = 0; reserved[i].name; i++) {
      if ((int)reserved[i].token == op) {
         for (Tuple *t = tuple_head; t; t = t->next) {
            if (!strcmp(t->english, reserved[i].name) ||
                !strcmp(t->translation, reserved[i].name)) {
               sprintf(buffer, "%s/%s", t->english, t->translation);
               return strdup(buffer);
            }
         }
         return strdup(reserved[i].name);
      }
   }
   sprintf(buffer, "?%d?", op);
   return strdup(buffer);
}

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
   const char *english = NULL;

   // find the tuple that matches this word.
   for (Tuple *p = tuple_head; p; p = p->next) {
      if (!utf8casecmp(p->translation, a)) {
         english = p->english;
         break;
      }
   }

   if (!english) {
      return (enum yytokentype) 0;
   }

   // now see if there are any matches
   for (int i = 0; i < (sizeof(reserved)/sizeof(reserved[0])); i++) {
      if (reserved[i].name && !strcmp(reserved[i].name, english)) {
         return reserved[i].token;
      }
   }

   // we should never get this far!
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

   if (!strcasecmp(copy, "void")) {
      if (!void_enabled) {
         return retval;
      }
      else {
         return YYVOID;
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
   int mode = 0;
   while (fgets(buf, sizeof(buf), f) == buf) {
      if (!mode) {
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
         if (strstr(buf, "[errors]") == buf) {
            mode++;
         }
      }
      else {
         int n = strlen(buf);
         if (n) {
            if (buf[n - 1] < ' ') {
               buf[n - 1] = 0;
               n--;

               if (n) {
                  char *translation = strchr(buf, '\t');
                  if (translation) {
                     *translation++ = 0;
                     add_error(buf, translation);
                  }
               }
            }
         }
      }
   }
}

void read_errors(FILE *f) {
   char buf[16384];
   int mode = 0;
   while (fgets(buf, sizeof(buf), f) == buf) {
      if (!mode) {
         if (strstr(buf, "[errors]") == buf) {
            mode++;
         }
      }
      else {
         int n = strlen(buf);
         if (n) {
            if (buf[n - 1] < ' ') {
               buf[n - 1] = 0;
               n--;

               if (n) {
                  char *translation = strchr(buf, '\t');
                  if (translation) {
                     *translation++ = 0;
                     add_error(buf, translation);
                  }
               }
            }
         }
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
   if (!path || !directory_exists(path)) {
      GURU;
      eprintf("{ERROR}: {CANNOT ACCESS DIRECTORY} ❮%0❯%n", path);
      exit(-1);
   }

   char full_path[16384];
   snprintf(full_path, sizeof(full_path), "%s/%s.utf8", path, language);

   FILE *f = fopen(full_path, "r");
   if (f) {
      read_translations(f);
      fclose(f);
   }
   else {
      GURU;
      eprintf("{ERROR}: {UNABLE TO OPEN TO OPEN FILE FOR READING} ❮%0❯%n", full_path);
      eprintf("{PLEASE CHECK LANGUAGE SETTINGS OR ENVIRONMENT VARIABLE} 'POLYBASICPATH'%n");
      exit(-1);
   }
}

void load_errors(const char *language) {
   const char *path = getenv("POLYBASICPATH");
   if (path == NULL) {
      path = find_translations();
   }
   if (!path || !directory_exists(path)) {
      GURU;
      eprintf("{ERROR}: {CANNOT ACCESS DIRECTORY} ❮%0❯%n", path);
      exit(-1);
   }

   char full_path[16384];
   snprintf(full_path, sizeof(full_path), "%s/%s.utf8", path, language);

   FILE *f = fopen(full_path, "r");
   if (f) {
      read_errors(f);
      fclose(f);
   }
   else {
      GURU;
      eprintf("{ERROR}: {UNABLE TO OPEN TO OPEN FILE FOR READING} ❮%0❯%n", full_path);
      eprintf("{PLEASE CHECK LANGUAGE SETTINGS OR ENVIRONMENT VARIABLE} 'POLYBASICPATH'%n");
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
   printf("Usage: %s [-l <language>] [<input.bas>]\n", shortname(arg0));
   printf("      -l : specify language, overriding POLYBASICLANG env variable\n");
   printf("\n");
   printf("      if <input.bas> is omitted, read program from STDIN.\n");
   printf("         this is not recommended, and may not work well with INPUT statements.\n");
   printf("\n");
   printf("      The following additional options are also available.\n");
   printf("      -v : print version information and exit\n");
   printf("      -h : print this usage information and exit\n");
   printf("      -? : print this usage information and exit\n");
   printf("\n");
   printf("      The following additional options are intended for debugging only.\n");
   printf("      -e     : specify language used for error messages\n");
   printf("      -g     : enable 'guru mode' with additional debug output\n");
   printf("      -0     : enable the VOID keyword\n");
   printf("      -f     : debug flex parser output, and then run program\n");
   printf("      -t <n> : dump parse tree for line <n>, do not run program\n");
   printf("               n=0 will dump the entire tree\n");
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
   char *errlanguage = NULL;

   char *arg0 = argv[0];

   // skip program name
   argc--; argv++;

   while(argc && argv[0][0] == '-') {
      switch (argv[0][1]) {
         // normal options
         case 'l':
            language = argv[1];
            if (language == NULL) {
               GURU;
               eprintf("-l {OPTION REQUIRES A LANGUAGE}%n");
               exit(-1);
            }
            argc--; argv++;
            break;
         // debugging options
         case 'e':
            errlanguage = argv[1];
            if (errlanguage == NULL) {
               GURU;
               eprintf("-e {OPTION REQUIRES A LANGUAGE}%n");
               exit(-1);
            }
            argc--; argv++;
            break;
         case '0':
            void_enabled = true;
            break;
         case 'f':
            flexdebug_enabled = true;
            break;
         case 't':
            treedebug = atoi(argv[1]);
            argc--; argv++;
            break;
         case 'v':
            version(arg0); // calls exit, never returns
            break;
         case 'g':
            guru_enabled = true;
            GURU;
            printf("GURU MODE ENABLED.");
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
      GURU;
      eprintf("{ERROR}: {UNSET ENVIRONMENT VARIABLE} 'POLYBASICLANG',");
      eprintf("{AND NO LANGUAGE GIVEN ON COMMAND LINE.  EXITING.}%n");
      exit(-1);
   }
   load_translations(language);
   if (errlanguage) {
      load_errors(errlanguage);
   }

   FILE *in = NULL;

   if (argv[0]) {
      in = fopen(argv[0], "r");

      if (in == NULL) {
         GURU;
         eprintf("{ERROR}: {UNABLE TO OPEN FILE} ❮%0❯%n", argv[0]);
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
      eprintf("{FAILURE}%n");
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

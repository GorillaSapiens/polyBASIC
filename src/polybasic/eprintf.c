#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "eprintf.h"

#include <stdarg.h>

struct Error;
typedef struct Error {
   const char *tag;
   const char *types;
   const char *format;
   struct Error *next;
} Error;

Error *head = NULL;

typedef union Value {
   int i;
   double f;
   char *s;
   char c;
} Value;

void add_error(const char *tag, const char *types, const char *format) {

   // not too spicy, please...
   if (strlen(types) > 10) {
      fprintf(stderr, "TOO MANY TYPES IN ERROR:\n");
      fprintf(stderr, "   ❮%s❯\n", tag);
      fprintf(stderr, "   ❮%s❯\n", types);
      fprintf(stderr, "   ❮%s❯\n", format);
      exit(-1);
   }

   // verify the types...

   for (const char *p = types; *p; p++) {
      switch(*p) {
         case 'i':
         case 'f':
         case 's':
         case 'c':
            // we cool, do nothing
            break;
         default:
            fprintf(stderr, "INVALID TYPE ❮%c❯ IN ERROR:\n", *p);
            fprintf(stderr, "   ❮%s❯\n", tag);
            fprintf(stderr, "   ❮%s❯\n", types);
            fprintf(stderr, "   ❮%s❯\n", format);
            exit(-1);
            break;
      }
   }

   // these will all be freed on program termination
   Error *error = (Error *) malloc(sizeof(Error));
   error->tag = strdup(tag);
   error->types = strdup(types);
   error->format = strdup(format);
   error->next = head;
   head = error;
   return;
}

void eprintf(const char *tag, ...) {
   // linear search, good enough for a first pass.  sorry, not sorry
   for (Error *p = head; p; p = p->next) {
      if (!strcmp(p->tag, tag)) {
         // bazinga!
         Value *values = (Value *) malloc (sizeof(Value) * strlen(p->types));

         va_list argp;
         va_start(argp, tag);
         for (int z = 0; z < strlen(p->types); z++) {
            switch(p->types[z]) {
               case 'i':
                  values[z].i = va_arg(argp, int);
                  break;
               case 'f':
                  values[z].f = va_arg(argp, double);
                  break;
               case 's':
                  values[z].s = va_arg(argp, char *);
                  break;
               case 'c':
                  values[z].c = va_arg(argp, int);
                  break;
            }
         }
         va_end(argp);

         // do the print....
         char buf[16384];
         int spot = 0;
         for (const char *str = p->format; *str; str++) {
            if (*str != '@') {
               buf[spot++] = *str;
            }
            else if (str[1] == '@') {
               buf[spot++] = *str;
               str++;
            }
            else {
               int n = str[1] - '0';
               if (n >= 0 && n < strlen(p->types)) {
                  switch(p->types[n]) {
                     case 'i':
                        spot += sprintf(buf + spot, "%i", values[n].i);
                        str++;
                        break;
                     case 'f':
                        spot += sprintf(buf + spot, "%lf", values[n].f);
                        str++;
                        break;
                     case 's':
                        spot += sprintf(buf + spot, "%s", values[n].s);
                        str++;
                        break;
                     case 'c':
                        // TODO FIX this could be utf8 ?!?!?
                        spot += sprintf(buf + spot, "%c", values[n].c);
                        str++;
                        break;
                  }
               }
               else {
                  buf[spot++] = *str;
               }
            }
         }
         buf[spot] = 0;
         printf("%s\n", buf);

         // free everything up
         free(values);

         return;
      }
   }
}

#ifdef STANDALONE_TEST
int main(int argc, char **argv) {
   add_error("tag3", "i", "some @1 @2 @3");
   add_error("tag2", "ifcs", "@@ @f some s=@3 c=@2 f=@1 i=@0 and why not @@ and @@@");
   add_error("tag1", "i", "some %1 %2 %3");
   eprintf("tag2", 1, 3.14, 'x', "today");
}
#endif

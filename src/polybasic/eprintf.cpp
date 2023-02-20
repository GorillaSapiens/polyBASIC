#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

#include "eprintf.hpp"

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
   char failmessage[16384];
   static const char *allowed_types = "ifsc";

   // not too spicy, please...
   if (strlen(types) > 10) {
      sprintf(failmessage, "TOO MANY SUBSTITUTIONS SPECIFIED");
      goto fail;
   }

   // scan the format, to make sure types match, and we're not missing any
   {
      int bitmask = 0;
      for (const char *p = format; *p; p++) {
         if (*p == '\\') {
            p++;
            continue;
         }
         if (*p == '{' && strlen(p) > 4) { // {Nt}
            int n = p[1] - '0';
            if (n < 0 || n > 9 || n > strlen(types) - 1) {
               sprintf(failmessage, "SUBSTITUTION '%c' OUT OF RANGE", p[1]);
               goto fail;
            }
            if (!strchr(allowed_types, p[2])) {
               sprintf(failmessage, "SUBSTITUTION %d TYPE '%c' NOT ALLOWED", n, p[2]);
               goto fail;
            }
            if (p[2] != types[n]) {
               sprintf(failmessage, "SUBSTITUTION %d WRONG TYPE '%c' EXPECTED '%c'", n, p[2], types[n]);
               goto fail;
            }
            bitmask |= (1 << n);
         }
      }

      // did we get everybody?
      for (int n = 0; n < strlen(types); n++) {
         if (!(bitmask & (1 << n))) {
            sprintf(failmessage, "SUBSTITUTION %d MISSING.", n);
            goto fail;
         }
      }
   }

   // if we got this far, everything is good!

   // these will all be freed on program termination
   {
      Error *error = (Error *) malloc(sizeof(Error));
      error->tag = strdup(tag);
      error->types = strdup(types);
      error->format = strdup(format);
      error->next = head;
      head = error;
   }
   return;

   fail:
      fprintf(stderr, "%s:\n", failmessage);
      fprintf(stderr, "   ❮%s❯\n", tag);
      fprintf(stderr, "   ❮%s❯\n", types);
      fprintf(stderr, "   ❮%s❯\n", format);
      //exit(-1);
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
            if (*str == '\\') {
               buf[spot++] = str[1];
               if (str[1] != 0) {
                  str++;
               }
            }
            else if (*str != '{') {
               buf[spot++] = *str;
            }
            else {
               if (strlen(str) >= 4) {
                  int n = str[1] - '0';
                  if (n >= 0 && n < strlen(p->types)) {
                     switch(p->types[n]) {
                        case 'i':
                           spot += sprintf(buf + spot, "%i", values[n].i);
                           str += 3;
                           break;
                        case 'f':
                           spot += sprintf(buf + spot, "%lf", values[n].f);
                           str += 3;
                           break;
                        case 's':
                           spot += sprintf(buf + spot, "%s", values[n].s);
                           str += 3;
                           break;
                        case 'c':
                           // TODO FIX this could be utf8 ?!?!?
                           spot += sprintf(buf + spot, "%c", values[n].c);
                           str += 3;
                           break;
                     }
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
   add_error("err_003", "i", "some {1i} {2c} {3q}");
   add_error("err_002", "ifcs", "\\{} \\{f some s={3s} c={2c} f={1f} i={0i} and why not \\{\\{ and \\{\\{\\{");
   add_error("err_001", "i", "some {1} {2c} {3}");
   eprintf("err_002", 1, 3.14, 'x', "today");
}
#endif

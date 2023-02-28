#include <stdio.h>
#include <string.h>
#include "utf8casecmp.h"
#include "lowercase.hpp"

static void lc(const char *src, char *dst) {
   while (*src) {
      int match = 0;
      for (int i = 0; lcmap[i].utcase; i++) {
         if (!strncmp(src, lcmap[i].utcase, strlen(lcmap[i].utcase))) {
            strcpy(dst, lcmap[i].lcase);
            dst += strlen(lcmap[i].lcase);
            src += strlen(lcmap[i].utcase);
            match = 1;
            break;
         }
      }
      if (!match) {
         *dst++ = *src++;
      }
   }
   *dst = 0;
}

// this is gonna be.... slow...
int utf8casecmp(const char *l, const char *r) {
   int i = 0;

   char nleft[1024];
   lc(l, nleft);

   char nright[1024];
   lc(r, nright);

   return strcmp(nleft, nright);
}

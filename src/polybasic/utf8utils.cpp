#include <stdio.h>
#include <string.h>

#include "utf8utils.hpp"
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

// caution, returns pointer to static buffer
const char *int2utf8(int64_t ord) {
   static unsigned char buffer[8];
   unsigned char *p = buffer;

   // U+0000   U+007F   0xxxxxxx
   if (ord < 0x80) {
      *p++ = ord;
      *p = 0;
   }

   // U+0080   U+07FF   110xxxxx 10xxxxxx
   else if (ord < 0x800) {
      *p++ = 0xC0 | ((ord >> 6) & 0x1F);
      *p++ = 0x80 | (ord & 0x3F); 
      *p = 0;
   }

   // U+0800   U+FFFF   1110xxxx 10xxxxxx 10xxxxxx
   else if (ord < 0x10000) {
      *p++ = 0xE0 | ((ord >> 12) & 0x0F);
      *p++ = 0x80 | ((ord >> 6) & 0x3F);
      *p++ = 0x80 | (ord & 0x3F); 
      *p = 0;
   }

   // U+10000  U+10FFFF 11110xxx 10xxxxxx 10xxxxxx 10xxxxxx
   else if (ord < 0x1FFFFF) {
      *p++ = 0xF0 | ((ord >> 18) & 0x07);
      *p++ = 0x80 | ((ord >> 12) & 0x3F);
      *p++ = 0x80 | ((ord >> 6) & 0x3F);
      *p++ = 0x80 | (ord & 0x3F);
      *p = 0;
   }

   return (const char *) buffer;
}

#ifdef STANDALONE_TEST
#include <stdio.h>

void show(int64_t ord) {
   const char *p = int2utf8(ord);
   printf("%06lX\n", ord);
   while (*p) {
      printf("%02X ", ((int)*p) & 0xFF);
      p++;
   }
   printf("\n");
}

int main(int argc, char**argv) {
   const char *p;

   // 1 byte
   show(0x7F);

   // 2 bytes
   show(0x80);
   show(0x7FF);

   // 3 bytes
   show(0x800);
   show(0xFFFF);

   // 4 bytes
   show(0x10000);
   show(0x10FFFF);
}
#endif

#include "hash.hpp"

unsigned long hash(const char *sstr) {
   const unsigned char *str = (const unsigned char *)sstr;
   unsigned long hash = 5381;
   int c;

   while (c = *str++)
      hash = ((hash << 5) + hash) ^ c; // hash(i - 1) * 33 ^ str[i]

   return hash;
}


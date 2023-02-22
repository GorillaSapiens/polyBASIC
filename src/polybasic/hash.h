#ifndef _INCLUDE_HASH_H_
#define _INCLUDE_HASH_H_

unsigned long hash(const char *sstr) {
   const unsigned char *str = (const unsigned char *)sstr;
   unsigned long hash = 5381;
   int c;

   while (c = *str++)
      hash = ((hash << 5) + hash) ^ c; // hash(i - 1) * 33 ^ str[i]

   return hash;
}

#endif

#include "runtime_for.h"
#include "dumptree.h"
#include "hash.h"

#define HASH_SIZE 65536
static Tree *fors[HASH_SIZE];

int is_for_defined(const char *p) {
   unsigned long h = hash(p);

   for (unsigned long i = 0; i < HASH_SIZE; i++) {
      unsigned long j = (i + h) % HASH_SIZE;
      if (fors[j] != NULL && !strcmp(p, fors[j]->sval)) {
         return 1;
      }
   }
   return 0;
}

int set_for(Tree *n) {
   unsigned long h = hash(n->sval);

   for (unsigned long i = 0; i < HASH_SIZE; i++) {
      unsigned long j = (i + h) % HASH_SIZE;
      if (fors[j] != NULL && !strcmp(n->sval, fors[j]->sval)) {
         return 0;
      }
      if (fors[j] == NULL) {
         fors[j] = n;
         return 1;
      }
   }
   return 0;
}

Tree *get_for(const char *p) {
   unsigned long h = hash(p);

   for (unsigned long i = 0; i < HASH_SIZE; i++) {
      unsigned long j = (i + h) % HASH_SIZE;
      if (fors[j] != NULL && !strcmp(p, fors[j]->sval)) {
         return fors[j];
      }
   }
   return NULL;
}

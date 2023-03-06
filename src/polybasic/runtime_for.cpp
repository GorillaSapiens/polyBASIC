#include "runtime_for.hpp"
#include "dumptree.hpp"
#include "hash.hpp"

#define HASH_SIZE 65536
static Tree *fors[HASH_SIZE];

int set_for(Tree *n) {
   unsigned long h = hash(V_AS_S(n->value));

   for (unsigned long i = 0; i < HASH_SIZE; i++) {
      unsigned long j = (i + h) % HASH_SIZE;
      if (fors[j] != NULL && !strcmp(V_AS_S(n->value), V_AS_S(fors[j]->value))) {
         return 0;
      }
      if (fors[j] == NULL) {
         fors[j] = n;
         return 1;
      }
   }
   return 0;
}

Tree *get_for(const char *p, bool remove) {
   unsigned long h = hash(p);

   for (unsigned long i = 0; i < HASH_SIZE; i++) {
      unsigned long j = (i + h) % HASH_SIZE;
      if (fors[j] != NULL && !strcmp(p, V_AS_S(fors[j]->value))) {
         if (remove) {
            fors[j] = NULL;
         }
         return fors[j];
      }
   }
   return NULL;
}

#include "runtime_def.h"
#include "dumptree.h"
#include "hash.h"

#define HASH_SIZE 65536
static Tree *defs[HASH_SIZE];

int is_def_defined(const char *p) {
   unsigned long h = hash(p);

   for (unsigned long i = 0; i < HASH_SIZE; i++) {
      unsigned long j = (i + h) % HASH_SIZE;
      if (defs[j] != NULL && !strcmp(p, defs[j]->sval)) {
         return 1;
      }
   }
   return 0;
}

int set_def(Tree *n) {
   unsigned long h = hash(n->sval);

   for (unsigned long i = 0; i < HASH_SIZE; i++) {
      unsigned long j = (i + h) % HASH_SIZE;
      if (defs[j] != NULL && !strcmp(n->sval, defs[j]->sval)) {
         return 0;
      }
      if (defs[j] == NULL) {
         defs[j] = n;
         return 1;
      }
   }
   return 0;
}

Tree *get_def(const char *p) {
   unsigned long h = hash(p);

   for (unsigned long i = 0; i < HASH_SIZE; i++) {
      unsigned long j = (i + h) % HASH_SIZE;
      if (defs[j] != NULL && !strcmp(p, defs[j]->sval)) {
         return defs[j];
      }
   }
   return NULL;
}

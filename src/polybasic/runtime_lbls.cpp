#include "runtime_lbls.hpp"
#include "dumptree.hpp"
#include "hash.hpp"

#define HASH_SIZE 65536
static Tree *lbls[HASH_SIZE];

int is_lbl_defined(const char *p) {
   unsigned long h = hash(p);

   for (unsigned long i = 0; i < HASH_SIZE; i++) {
      unsigned long j = (i + h) % HASH_SIZE;
      if (lbls[j] != NULL && !strcmp(p, lbls[j]->label)) {
         return 1;
      }
   }
   return 0;
}

int set_label(Tree *n) {
   unsigned long h = hash(n->label);

   for (unsigned long i = 0; i < HASH_SIZE; i++) {
      unsigned long j = (i + h) % HASH_SIZE;
      if (lbls[j] != NULL && !strcmp(n->label, lbls[j]->label)) {
         return 0;
      }
      if (lbls[j] == NULL) {
         lbls[j] = n;
         return 1;
      }
   }
   return 0;
}

Tree *get_label(const char *p) {
   if (!p) {
      return NULL;
   }

   unsigned long h = hash(p);

   for (unsigned long i = 0; i < HASH_SIZE; i++) {
      unsigned long j = (i + h) % HASH_SIZE;
      if (lbls[j] != NULL && !strcmp(p, lbls[j]->label)) {
         return lbls[j];
      }
   }
   return NULL;
}

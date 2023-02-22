#include "runtime_lbls.h"

#define HASH_SIZE 65536
Lbl *lbls[HASH_SIZE];

static unsigned long hash(const char *sstr) {
   const unsigned char *str = (const unsigned char *)sstr;
   unsigned long hash = 5381;
   int c;

   while (c = *str++)
      hash = ((hash << 5) + hash) ^ c; // hash(i - 1) * 33 ^ str[i]

   return hash;
}

int is_lbl_defined(const char *p) {
   unsigned long h = hash(p);

   for (unsigned long i = 0; i < HASH_SIZE; i++) {
      unsigned long j = (i + h) % HASH_SIZE;
      if (lbls[j] != NULL && !strcmp(p, lbls[j]->name)) {
         return 1;
      }
   }
   return 0;
}

int set_label(const char *p, Tree *n) {
   unsigned long h = hash(p);

   for (unsigned long i = 0; i < HASH_SIZE; i++) {
      unsigned long j = (i + h) % HASH_SIZE;
      if (lbls[j] != NULL && !strcmp(p, lbls[j]->name)) {
         return 0;
      }
      if (lbls[j] == NULL) {
         lbls[j] = (Lbl *)malloc(sizeof(Lbl));
         lbls[j]->name = strdup(p);
         return 1;
      }
   }
   return 0;
}

Tree *get_label(const char *p) {
   unsigned long h = hash(p);

   for (unsigned long i = 0; i < HASH_SIZE; i++) {
      unsigned long j = (i + h) % HASH_SIZE;
      if (lbls[j] != NULL && !strcmp(p, lbls[j]->name)) {
         return lbls[j]->tree;
      }
   }
   return NULL;
}

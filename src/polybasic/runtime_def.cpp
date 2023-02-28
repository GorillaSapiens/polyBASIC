#include "tree.h"
#include "polybasic.tab.hpp"
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

// lots of helper functions to detect cycles

int dfc_h3(const char *p) {
   unsigned long h = hash(p);

   for (unsigned long i = 0; i < HASH_SIZE; i++) {
      unsigned long j = (i + h) % HASH_SIZE;
      if (defs[j] != NULL && !strcmp(p, defs[j]->sval)) {
         return j;
      }
   }
   return -1;
}

static void dfc_h2(char *visited, Tree *tree) {
   if (!tree) {
      return;
   }

   if (tree->op == YYDEFCALL) {
      int callee = dfc_h3(tree->sval);
      if (callee >= 0) {
         if (visited[callee]) {
            fprintf(stderr, "FN DEF CYCLE DETECTED:\n");
            for (int i = 0; i < HASH_SIZE; i++) {
               if (visited[i]) {
                  fprintf(stderr, "   LINE %d DEF %s\n", defs[i]->line, defs[i]->sval);
               }
            }
            exit(-1);
         }
         else {
            visited[callee] = 1;
            dfc_h2(visited, defs[callee]);
         }
      }
   }
   dfc_h2(visited, tree->left);
   dfc_h2(visited, tree->middle);
   dfc_h2(visited, tree->right);
}

static void dfc_h1(int i) {
   char visited[HASH_SIZE] = { 0 };
   if (defs[i]) {
      visited[i] = 1;
      dfc_h2(visited, defs[i]);
   }
}

void def_check_cycle(void) {
   for (int i = 0; i < HASH_SIZE; i++) {
      dfc_h1(i);
   }
}

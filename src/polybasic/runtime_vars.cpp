#include <string.h>
#include <stdlib.h>
#include "runtime_vars.h"
#include "hash.h"

#define HASH_SIZE 65536
static Var *vars[HASH_SIZE];

int is_var_defined(const char *p) {
   unsigned long h = hash(p);

   for (unsigned long i = 0; i < HASH_SIZE; i++) {
      unsigned long j = (i + h) % HASH_SIZE;
      if (vars[j] != NULL && !strcmp(p, vars[j]->name)) {
         return 1;
      }
   }
   return 0;
}

int set_value(const char *p, double d) {
   unsigned long h = hash(p);

   for (unsigned long i = 0; i < HASH_SIZE; i++) {
      unsigned long j = (i + h) % HASH_SIZE;
      if (vars[j] != NULL && !strcmp(p, vars[j]->name)) {
         if (vars[j]->typ == 'r') {
            delete vars[j]->rval;
         }
         else if (vars[j]->typ == 's') {
            free((void *)(vars[j]->sval));
         }
         free(vars[j]);
         vars[j] = NULL;
      }
      if (vars[j] == NULL) {
         vars[j] = (Var *)malloc(sizeof(Var));
         vars[j]->name = strdup(p);
         vars[j]->typ = 'd';
         vars[j]->dval = d;
         return 1;
      }
   }
   return 0;
}

int set_value(const char *p, int64_t i) {
   unsigned long h = hash(p);

   for (unsigned long i = 0; i < HASH_SIZE; i++) {
      unsigned long j = (i + h) % HASH_SIZE;
      if (vars[j] != NULL && !strcmp(p, vars[j]->name)) {
         if (vars[j]->typ == 'r') {
            delete vars[j]->rval;
         }
         else if (vars[j]->typ == 's') {
            free((void *)(vars[j]->sval));
         }
         free(vars[j]);
         vars[j] = NULL;
      }
      if (vars[j] == NULL) {
         vars[j] = (Var *)malloc(sizeof(Var));
         vars[j]->name = strdup(p);
         vars[j]->typ = 'i';
         vars[j]->ival = i;
         return 1;
      }
   }
   return 0;
}

int set_value(const char *p, Rational *r) {
   unsigned long h = hash(p);

   for (unsigned long i = 0; i < HASH_SIZE; i++) {
      unsigned long j = (i + h) % HASH_SIZE;
      if (vars[j] != NULL && !strcmp(p, vars[j]->name)) {
         if (vars[j]->typ == 'r') {
            delete vars[j]->rval;
         }
         else if (vars[j]->typ == 's') {
            free((void *)(vars[j]->sval));
         }
         free(vars[j]);
         vars[j] = NULL;
      }
      if (vars[j] == NULL) {
         vars[j] = (Var *)malloc(sizeof(Var));
         vars[j]->name = strdup(p);
         vars[j]->typ = 'r';
         vars[j]->rval = new Rational(*r);
         return 1;
      }
   }
   return 0;
}

int set_value(const char *p, const char *s) {
   unsigned long h = hash(p);

   for (unsigned long i = 0; i < HASH_SIZE; i++) {
      unsigned long j = (i + h) % HASH_SIZE;
      if (vars[j] != NULL && !strcmp(p, vars[j]->name)) {
         if (vars[j]->typ == 'r') {
            delete vars[j]->rval;
         }
         else if (vars[j]->typ == 's') {
            free((void *)(vars[j]->sval));
         }
         free(vars[j]);
         vars[j] = NULL;
      }
      if (vars[j] == NULL) {
         vars[j] = (Var *)malloc(sizeof(Var));
         vars[j]->name = strdup(p);
         vars[j]->typ = 's';
         vars[j]->sval = strdup(s);
         return 1;
      }
   }
   return 0;
}

Var *get_value(const char *p) {
   unsigned long h = hash(p);

   for (unsigned long i = 0; i < HASH_SIZE; i++) {
      unsigned long j = (i + h) % HASH_SIZE;
      if (vars[j] != NULL && !strcmp(p, vars[j]->name)) {
         return vars[j];
      }
   }
   return NULL;
}

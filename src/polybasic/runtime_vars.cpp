#include <string.h>
#include <stdlib.h>
#include "runtime_vars.h"

#define HASH_SIZE 65536
Var *vars[HASH_SIZE];

static unsigned long hash(const char *sstr) {
   const unsigned char *str = (const unsigned char *)sstr;
   unsigned long hash = 5381;
   int c;

   while (c = *str++)
      hash = ((hash << 5) + hash) ^ c; // hash(i - 1) * 33 ^ str[i]

   return hash;
}

int is_defined(const char *p) {
   unsigned long h = hash(p);

   for (int i = 0; i < HASH_SIZE; i++) {
      if (vars[i+h] != NULL && !strcmp(p, vars[i+h]->name)) {
         return 1;
      }
   }
   return 0;
}

int set_value(const char *p, double d) {
   unsigned long h = hash(p);

   for (int i = 0; i < HASH_SIZE; i++) {
      if (vars[i+h] != NULL && !strcmp(p, vars[i+h]->name)) {
         if (vars[i+h]->typ == 'r') {
            delete vars[i+h]->rval;
         }
         else if (vars[i+h]->typ == 's') {
            free((void *)(vars[i+h]->sval));
         }
         free(vars[i+h]);
         vars[i+h] = NULL;
      }
      if (vars[i+h] == NULL) {
         vars[i+h] = (Var *)malloc(sizeof(Var));
         vars[i+h]->name = strdup(p);
         vars[i+h]->typ = 'd';
         vars[i+h]->dval = d;
         return 1;
      }
   }
   return 0;
}

int set_value(const char *p, int64_t i) {
   unsigned long h = hash(p);

   for (int i = 0; i < HASH_SIZE; i++) {
      if (vars[i+h] != NULL && !strcmp(p, vars[i+h]->name)) {
         if (vars[i+h]->typ == 'r') {
            delete vars[i+h]->rval;
         }
         else if (vars[i+h]->typ == 's') {
            free((void *)(vars[i+h]->sval));
         }
         free(vars[i+h]);
         vars[i+h] = NULL;
      }
      if (vars[i+h] == NULL) {
         vars[i+h] = (Var *)malloc(sizeof(Var));
         vars[i+h]->name = strdup(p);
         vars[i+h]->typ = 'i';
         vars[i+h]->ival = i;
         return 1;
      }
   }
   return 0;
}

int set_value(const char *p, Rational *r) {
   unsigned long h = hash(p);

   for (int i = 0; i < HASH_SIZE; i++) {
      if (vars[i+h] != NULL && !strcmp(p, vars[i+h]->name)) {
         if (vars[i+h]->typ == 'r') {
            delete vars[i+h]->rval;
         }
         else if (vars[i+h]->typ == 's') {
            free((void *)(vars[i+h]->sval));
         }
         free(vars[i+h]);
         vars[i+h] = NULL;
      }
      if (vars[i+h] == NULL) {
         vars[i+h] = (Var *)malloc(sizeof(Var));
         vars[i+h]->name = strdup(p);
         vars[i+h]->typ = 'r';
         vars[i+h]->rval = new Rational(*r);
         return 1;
      }
   }
   return 0;
}

int set_value(const char *p, const char *s) {
   unsigned long h = hash(p);

   for (int i = 0; i < HASH_SIZE; i++) {
      if (vars[i+h] != NULL && !strcmp(p, vars[i+h]->name)) {
         if (vars[i+h]->typ == 'r') {
            delete vars[i+h]->rval;
         }
         else if (vars[i+h]->typ == 's') {
            free((void *)(vars[i+h]->sval));
         }
         free(vars[i+h]);
         vars[i+h] = NULL;
      }
      if (vars[i+h] == NULL) {
         vars[i+h] = (Var *)malloc(sizeof(Var));
         vars[i+h]->name = strdup(p);
         vars[i+h]->typ = 's';
         vars[i+h]->sval = strdup(s);
         return 1;
      }
   }
   return 0;
}

Var *get_value(const char *p) {
   unsigned long h = hash(p);

   for (int i = 0; i < HASH_SIZE; i++) {
      if (vars[i+h] != NULL && !strcmp(p, vars[i+h]->name)) {
         return vars[i+h];
      }
   }
   return NULL;
}

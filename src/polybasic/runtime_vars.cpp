#include <string.h>
#include <stdlib.h>

#include "eprintf.hpp"
#include "runtime_vars.hpp"
#include "hash.hpp"

#define HASH_SIZE 65536
static Var *vars[HASH_SIZE];

static Varbound *bounds[HASH_SIZE];

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

int set_value(const char *p, Val value) {
   unsigned long h = hash(p);

   for (unsigned long i = 0; i < HASH_SIZE; i++) {
      unsigned long j = (i + h) % HASH_SIZE;
      if (vars[j] != NULL && !strcmp(p, vars[j]->name)) {
         if (vars[j]->value.typ == 'r') {
            delete vars[j]->value.rval;
         }
         else if (vars[j]->value.typ == 's') {
            free((void *)(vars[j]->value.sval));
         }
         free(vars[j]);
         vars[j] = NULL;
      }
      if (vars[j] == NULL) {
         vars[j] = (Var *)malloc(sizeof(Var));
         vars[j]->name = strdup(p);
         vars[j]->value = value;
         if (value.typ == 'r') {
            vars[j]->value.rval = new Rational(*value.rval);
         }
         else if (value.typ == 's') {
            vars[j]->value.sval = strdup(value.sval);
         }
         return 1;
      }
   }
   return 0;
}

int set_value(const char *p, Tree *result) {
   Val value;
   switch (result->op) {
      case YYDOUBLE:
         value.typ = 'd';
         value.dval = result->dval;
         break;
      case YYINTEGER:
         value.typ = 'i';
         value.ival = result->ival;
         break;
      case YYRATIONAL:
         value.typ = 'r';
         value.rval = result->rval;
         break;
      case YYSTRING:
         value.typ = 's';
         value.sval = result->sval;
         break;
      default:
         GURU;
         eprintf("SOURCE %0:%1, UNRECOGNIZED VARIABLE TYPE ❮%2❯%n", result->line, result->col, result->op);
         break;
   }
   return set_value(p, value);
}

const Val *get_value(const char *p) {
   unsigned long h = hash(p);

   for (unsigned long i = 0; i < HASH_SIZE; i++) {
      unsigned long j = (i + h) % HASH_SIZE;
      if (vars[j] != NULL && !strcmp(p, vars[j]->name)) {
         return &(vars[j]->value);
      }
   }
   return NULL;
}

int is_bound_defined(const char *p) {
   unsigned long h = hash(p);

   for (unsigned long i = 0; i < HASH_SIZE; i++) {
      unsigned long j = (i + h) % HASH_SIZE;
      if (bounds[j] != NULL && !strcmp(p, bounds[j]->name)) {
         return 1;
      }
   }
   return 0;
}

void set_bound(const char *p, int line, int dimensions, int64_t upper1, int64_t upper2) {
   unsigned long h = hash(p);

   for (unsigned long i = 0; i < HASH_SIZE; i++) {
      unsigned long j = (i + h) % HASH_SIZE;
      if (bounds[j] == NULL) {
         bounds[j] = (Varbound *)malloc(sizeof(Varbound));
         bounds[j]->name = strdup(p);
         bounds[j]->line = line;
         bounds[j]->dimensions = dimensions;
         bounds[j]->upper1 = upper1;
         bounds[j]->upper2 = upper2;
         return;
      }
   }
}

const Varbound *get_varbound(const char *p) {
   unsigned long h = hash(p);

   for (unsigned long i = 0; i < HASH_SIZE; i++) {
      unsigned long j = (i + h) % HASH_SIZE;
      if (bounds[j] != NULL && !strcmp(p, bounds[j]->name)) {
         return bounds[j];
      }
   }
   return NULL;
}

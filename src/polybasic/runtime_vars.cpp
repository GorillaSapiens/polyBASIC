#include <string.h>
#include <stdlib.h>

#include "eprintf.hpp"
#include "runtime_vars.hpp"
#include "hash.hpp"

extern const char *eop2string(int op);

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

int set_value(const char *p, Value value) {
   unsigned long h = hash(p);

   for (unsigned long i = 0; i < HASH_SIZE; i++) {
      unsigned long j = (i + h) % HASH_SIZE;
      if (vars[j] != NULL && !strcmp(p, vars[j]->name)) {
         delete vars[j];
         vars[j] = NULL;
      }
      if (vars[j] == NULL) {
         vars[j] = new Var(p, value);
         return 1;
      }
   }
   return 0;
}

int set_value(const char *p, Tree *result) {
   int ret = 0;

   switch (result->op) {
      case YYDOUBLE:
      case YYINTEGER:
      case YYRATIONAL:
      case YYSTRING:
         ret = set_value(p, result->value);
         break;
      default:
         GURU;
         // test case voidsetvalue
         eprintf("{ERROR}: @%0:%1, {UNRECOGNIZED VARIABLE TYPE} ❮%2❯%n",
            result->line, result->col, eop2string(result->op));
         exit(-1);
         break;
   }
   return ret;
}

const Value *get_value(const char *p) {
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

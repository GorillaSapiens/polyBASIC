#ifndef _INCLUDE_RUNTIME_VARS_H_
#define _INCLUDE_RUNTIME_VARS_H_

#include <stdint.h>

#include "tree.hpp"
#include "rational.hpp"
#include "polybasic.tab.hpp"

typedef struct Varbound {
   const char *name;
   int line;
   int dimensions;
   int64_t upper1;
   int64_t upper2;
} Varbound;

typedef struct Var {
   const char *name;
   Value value;

   Var(const char *n, const Value &v) : value(v) {
      name = n ? strdup(n) : NULL;
   }
   ~Var() {
      if (name) {
         free((void *)name);
      }
   }
} Var;

int is_var_defined(const char *p);

int set_value(const char *p, Value value);

int set_value(const char *p, Tree *result);

const Value *get_value(const char *p);

int is_bound_defined(const char *p);

void set_bound(const char *p,
               int line,
               int dimensions,
               int64_t upper1,
               int64_t upper2);

const Varbound *get_varbound(const char *p);

#endif


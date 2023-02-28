#ifndef _INCLUDE_RUNTIME_VARS_H_
#define _INCLUDE_RUNTIME_VARS_H_

#include <stdint.h>

#include "tree.hpp"
#include "rational.hpp"
#include "polybasic.tab.hpp"

typedef struct Val {
   char typ;
   union {
      double dval;
      int64_t ival;
      Rational *rval;
      const char *sval;
   };
} Val;

typedef struct Varbound {
   const char *name;
   int line;
   int dimensions;
   int64_t upper1;
   int64_t upper2;
} Varbound;

typedef struct Var {
   const char *name;
   Val value;
} Var;

int is_var_defined(const char *p);

int set_value(const char *p, Val value);

int set_value(const char *p, Tree *result);

const Val *get_value(const char *p);

int is_bound_defined(const char *p);

void set_bound(const char *p,
               int line,
               int dimensions,
               int64_t upper1,
               int64_t upper2);

const Varbound *get_varbound(const char *p);

#endif


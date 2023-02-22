#ifndef _INCLUDE_RUNTIME_VARS_H_
#define _INCLUDE_RUNTIME_VARS_H_

#include <stdint.h>
#include "rational.h"

typedef struct Val {
   char typ;
   union {
      double dval;
      int64_t ival;
      Rational *rval;
      const char *sval;
   };
} Val;

typedef struct Var {
   const char *name;
   Val value;
} Var;

int is_var_defined(const char *p);

int set_value(const char *p, Val value);

const Val *get_value(const char *p);

#endif


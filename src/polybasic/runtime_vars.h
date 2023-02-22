#ifndef _INCLUDE_RUNTIME_VARS_H_
#define _INCLUDE_RUNTIME_VARS_H_

#include <stdint.h>
#include "rational.h"

typedef struct Var {
   const char *name;
   char typ;
   union {
      double dval;
      int64_t ival;
      Rational *rval;
      const char *sval;
   };
} Var;

int is_var_defined(const char *p);

int set_value(const char *p, double d);

int set_value(const char *p, int64_t i);

int set_value(const char *p, Rational *r);

int set_value(const char *p, const char *s);

Var *get_value(const char *p);

#endif


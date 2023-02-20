#ifndef _INCLUDE_TREE_H_
#define _INCLUDE_TREE_H_

#include "rational.h"

struct Tree;
typedef struct Tree {
   int line;
   int col;

   int typ;
   int op;

   union {
      double dval;
      int64_t ival;
      Rational *rval;
      const char *sval;
   };

   struct Tree *left;
   struct Tree *right;
} Tree;

#endif
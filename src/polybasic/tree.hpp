#ifndef _INCLUDE_TREE_H_
#define _INCLUDE_TREE_H_

#include "rational.hpp"

struct Tree;
typedef struct Tree {
   int line;
   int col;

   int op;
   const char *label;

   char valt;
   union {
      double dval;
      int64_t ival;
      Rational *rval;
      const char *sval;
   };

   struct Tree *left;
   struct Tree *middle;
   struct Tree *right;

   struct Tree *next;
} Tree;

#endif

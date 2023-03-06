#ifndef _INCLUDE_TREE_H_
#define _INCLUDE_TREE_H_

#include <variant>

#include "safe_strdup.hpp"
#include "rational.hpp"

using std::variant;

#define V_V 0
#define V_D 1
#define V_I 2
#define V_R 3
#define V_S 4

#define V_AS_D(x) (std::get<double>(x))
#define V_AS_I(x) (std::get<int64_t>(x))
#define V_AS_R(x) (std::get<Rational *>(x))
#define V_AS_S(x) (std::get<const char *>(x))

typedef variant<char,
                int64_t,
                double,
                Rational *,
                const char *> ValueBase;

class Value : public ValueBase
{
   public:

   ValueBase &base(void) {
      return *this;
   }

   void vacate(void) {
      if (index() == V_R) {
         Rational *r = V_AS_R(*this);
         if (r) {
            delete r;
         }
      }
      else if (index() == V_S) {
         const char *p = V_AS_S(*this);
         if (p) {
            free((void *)p);
         }
      }

      base() = (char) 0;
   }

   Value() {
   }

   Value(const Value &value) { // copy constructor
      if (index() == V_R) {
         Rational *r = V_AS_R(value);
         if (r) {
            base() = new Rational(*r);
         }
         else {
            base() = (Rational *) NULL;
         }
      }
      else if (index() == V_S) {
         const char *p = V_AS_S(value);
         if (p) {
            base() = (const char *) strdup(p);
         }
         else {
            base() = (const char *) NULL;
         }
      }
   }

   Value& operator=(const Value& other) { // assignment operator
      vacate();

      base() = ((Value &)other).base();

      if (index() == V_R) {
         Rational *r = new Rational(*V_AS_R(other));
         base() = r;
      }
      else if (index() == V_S) {
         const char *p = strdup(V_AS_S(other));
         base() = p;
      }

      return *this;
   }

   ~Value() {
      vacate();
   }
};

struct Tree;
typedef struct Tree {
   int line;
   int col;

   int op;
   const char *label;

   Value value;

   struct Tree *left;
   struct Tree *middle;
   struct Tree *right;

   struct Tree *next;

   Tree() {
      line   = 0;
      col    = 0;
      op     = 0;
      label  = NULL;
      left   = NULL;
      middle = NULL;
      right  = NULL;
      next   = NULL;
   }

   Tree(const Tree &tree) { // copy constructor
      line   = tree.line;
      col    = tree.col;
      op     = tree.op;
      label  = strdup(tree.label);
      value  = tree.value;
      left   = tree.left;
      middle = tree.middle;
      right  = tree.right;
      next   = tree.next;
   }

   Tree& operator=(const Tree& other) { // assignment operator
      line   = other.line;
      col    = other.col;
      op     = other.op;
      label  = strdup(other.label);
      value  = other.value;
      left   = other.left;
      middle = other.middle;
      right  = other.right;
      next   = other.next;
      return *this;
   }

   ~Tree() {
      if (label) {
         free((void *)label);
      }
   }

} Tree;

#endif

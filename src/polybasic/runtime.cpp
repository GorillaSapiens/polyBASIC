#include <math.h>
#include <time.h>

#include "tree.h"
#include "polybasic.tab.hpp"
#include "dumptree.h"
#include "runtime_lbls.h"
#include "runtime_for.h"
#include "runtime_vars.h"
#include "runtime_data.h"
#include "runtime.h"

static void register_labels(Tree *root) {
   while (root) {
      if (root->label) {
         if (is_lbl_defined(root->label)) {
            Tree *prev = get_label(root->label);
            // TODO FIX localize this message
            printf("ERRROR: label '%s' at line %i col %i already defined.\n"
                   "        previous definition at line %i col %i\n",
               root->label, root->line, root->col, prev->line, prev->col);
            exit(-1);
         }
         else {
            set_label(root);
         }
      }
      root = root->next;
   }
}

static void register_for(Tree *root) {
   while (root) {
      if (root->op == YYFOR && root->sval) {
         if (is_for_defined(root->sval)) {
            Tree *prev = get_for(root->sval);
            // TODO FIX localize this message
            printf("ERRROR: for statement on '%s' at line %i col %i already defined.\n"
                   "        previous definition at line %i col %i\n",
               root->label, root->line, root->col, prev->line, prev->col);
            exit(-1);
         }
         else {
            set_for(root);
         }
      }
      root = root->next;
   }
}

static void register_data(Tree *root) {
   while (root) {
      if (root->op == YYDATA) {
         for (Tree *data = root->right; data; data = data->middle) {
            switch (data->op) {
               case YYDOUBLE:
                  add_data(data->dval);
                  break;
               case YYINTEGER:
                  add_data(data->ival);
                  break;
               case YYRATIONAL:
                  add_data(data->rval);
                  break;
               case YYSTRING:
                  add_data(data->sval);
                  break;
            }
         }
      }
      root = root->next;
   }
}

// make a deep copy, substituting variables along the way
Tree *deep_copy(Tree *subtree) {
   Tree *copy = (Tree *) malloc(sizeof(Tree));
   memcpy(copy, subtree, sizeof(Tree));

// don't copy labels, we'd just have to free them later
//   if (subtree->label) {
//      copy->label = strdup(subtree->label);
//   }

   if (copy->op == YYSTRING) {
      copy->sval = strdup(subtree->sval);
   }
   else if (copy->op == YYRATIONAL) {
      copy->rval = new Rational(*(subtree->rval));
   }
   else if (copy->op == YYVARNAME) {
      const Val *val = get_value(subtree->sval);
      if (!val) {
         fprintf(stderr, "WARNING: line %d col %d, '%s' has no value\n",
            copy->line, copy->col, copy->sval);
         exit(-1);
      }
      else {
         if (val->typ == 'd') {
            copy->op = YYDOUBLE;
            copy->dval = val->dval;
         }
         else if (val->typ == 'i') {
            copy->op = YYINTEGER;
            copy->ival = val->ival;
         }
         else if (val->typ == 'r') {
            copy->op = YYRATIONAL;
            copy->rval = new Rational(*(val->rval));
         }
         else if (val->typ == 's') {
            copy->op = YYSTRING;
            copy->sval = strdup(val->sval);
         }
      }
   }

   if (subtree->left) { copy->left = deep_copy(subtree->left); }
   if (subtree->middle) { copy->middle = deep_copy(subtree->middle); }
   if (subtree->right) { copy->right = deep_copy(subtree->right); }
   copy->next = NULL; // if (subtree->next) { copy->next = deep_copy(subtree->next); }

   return copy;
}

void upgrade_to_number(Tree *p) {
   if (p->op == YYSTRING) {
      const char *s = p->sval;
      if (strchr((char *)s, '#') == s) {
         p->op = YYRATIONAL;
         p->rval = new Rational(s);
      }
      else if (strchr((char *)s, '.') || strchr((char *)s, 'E')) {
         p->op = YYDOUBLE;
         // TODO FIX does this work????
         p->dval = atof(s);
      }
      else {
         p->op = YYINTEGER;
         p->ival = atoll(s);
      }
      free((void *)s);
   }
}

void upgrade_to_rational(Tree *p) {
   if (p->op == YYINTEGER) {
      int64_t ival = p->ival;
      int8_t sign = 1;
      if (ival < 0) {
         sign = -1;
         ival = -ival;
      }
      p->op = YYRATIONAL;
      p->rval = new Rational(sign, ival, 0, 1);
   }
}

void upgrade_to_double(Tree *p) {
   if (p->op == YYINTEGER) {
      int64_t ival = p->ival;
      p->op = YYDOUBLE;
      p->dval = (double) ival;
   }
   else if (p->op == YYRATIONAL) {
      Rational *deleteme = p->rval;
      double dval = (double)(*(p->rval));
      p->op = YYDOUBLE;
      p->dval = dval;
      delete deleteme;
   }
}

Tree *evaluate(Tree *p) {
   if (p->op == YYDOUBLE) {
      return p;
   }
   if (p->op == YYINTEGER) {
      return p;
   }
   if (p->op == YYRATIONAL) {
      return p;
   }
   if (p->op == YYSTRING) {
      return p;
   }

   if (p->left) {
      p->left = evaluate(p->left);
   }
   if (p->middle) {
      p->middle = evaluate(p->middle);
   }
   if (p->right) {
      p->right = evaluate(p->right);
   }

   if (p->op == YYABS) {
      Tree *freeme = p->left;
      if (p->left->op == YYSTRING) {
         upgrade_to_number(p->left);
      }
      if (p->left->op == YYDOUBLE) {
         p->left->dval = fabs(p->left->dval);
      }
      else if (p->left->op == YYINTEGER) {
         p->left->ival = llabs(p->left->ival);
      }
      else if (p->left->op == YYRATIONAL) {
         p->left->rval->abs();
      }
      memcpy(p, p->left, sizeof(Tree));
      free(freeme);
   }
   else if (p->op == YYATN) {
      Tree *freeme = p->left;
      if (p->left->op == YYSTRING) {
         upgrade_to_number(p->left);
      }
      if (p->left->op == YYDOUBLE) {
         p->left->dval = atan(p->left->dval);
      }
      else if (p->left->op == YYINTEGER) {
         p->left->op = YYDOUBLE;
         p->left->dval = atan((double)p->left->ival);
      }
      else if (p->left->op == YYRATIONAL) {
         p->left->op = YYDOUBLE;
         Rational *deleteme = p->left->rval;
         p->left->dval = atan((double)*(p->left->rval));
         delete deleteme;
      }
      memcpy(p, p->left, sizeof(Tree));
      free(freeme);
   }
   else if (p->op == YYCOS) {
      Tree *freeme = p->left;
      if (p->left->op == YYSTRING) {
         upgrade_to_number(p->left);
      }
      if (p->left->op == YYDOUBLE) {
         p->left->dval = cos(p->left->dval);
      }
      else if (p->left->op == YYINTEGER) {
         p->left->op = YYDOUBLE;
         p->left->dval = cos((double)p->left->ival);
      }
      else if (p->left->op == YYRATIONAL) {
         p->left->op = YYDOUBLE;
         Rational *deleteme = p->left->rval;
         p->left->dval = cos((double)*(p->left->rval));
         delete deleteme;
      }
      memcpy(p, p->left, sizeof(Tree));
      free(freeme);
   }
   else if (p->op == YYDBL) {
      Tree *freeme = p->left;
      p->op = YYDOUBLE;
      if (p->left->op == YYSTRING) {
         p->dval = atof(p->left->sval);
      }
      if (p->left->op == YYDOUBLE) {
         p->dval = p->left->dval;
      }
      else if (p->left->op == YYINTEGER) {
         p->dval = (double) p->left->ival;
      }
      else if (p->left->op == YYRATIONAL) {
         Rational *deleteme = p->left->rval;
         p->dval = (double) (*(p->left->rval));
         delete deleteme;
      }
      free(freeme);
   }
   else if (p->op == YYEXP) {
      Tree *freeme = p->left;
      if (p->left->op == YYSTRING) {
         upgrade_to_number(p->left);
      }
      if (p->left->op == YYDOUBLE) {
         p->left->dval = pow(M_E,(p->left->dval));
      }
      else if (p->left->op == YYINTEGER) {
         p->left->op = YYDOUBLE;
         p->left->dval = pow(M_E,((double)p->left->ival));
      }
      else if (p->left->op == YYRATIONAL) {
         p->left->op = YYDOUBLE;
         Rational *deleteme = p->left->rval;
         p->left->dval = pow(M_E,((double)*(p->left->rval)));
         delete deleteme;
      }
      memcpy(p, p->left, sizeof(Tree));
      free(freeme);
   }
   else if (p->op == YYINT) {
      Tree *freeme = p->left;
      if (p->left->op == YYSTRING) {
         upgrade_to_number(p->left);
      }
      if (p->left->op == YYDOUBLE) {
         p->left->dval = floor(p->left->dval);
      }
      else if (p->left->op == YYINTEGER) {
         p->left->ival = (int)floor((double)p->left->ival);
      }
      else if (p->left->op == YYRATIONAL) {
         p->left->rval->floor();
      }
      memcpy(p, p->left, sizeof(Tree));
      free(freeme);
   }
   else if (p->op == YYLOG) {
      Tree *freeme = p->left;
      if (p->left->op == YYSTRING) {
         upgrade_to_number(p->left);
      }
      if (p->left->op == YYDOUBLE) {
         p->left->dval = log(p->left->dval);
      }
      else if (p->left->op == YYINTEGER) {
         p->left->op = YYDOUBLE;
         p->left->dval = log((double)p->left->ival);
      }
      else if (p->left->op == YYRATIONAL) {
         p->left->op = YYDOUBLE;
         Rational *deleteme = p->left->rval;
         p->left->dval = log((double)*(p->left->rval));
         delete deleteme;
      }
      memcpy(p, p->left, sizeof(Tree));
      free(freeme);
   }
   else if (p->op == YYRND) {
      p->op = YYDOUBLE;
      p->dval = (double)rand() / (double)RAND_MAX;
   }
   else if (p->op == YYRANDOMIZE) {
      time_t t = time(NULL);
      p->op = YYINTEGER;
      p->ival = t;
   }
   else if (p->op == YYSGN) {
      Tree *freeme = p->left;
      int sign = 0;
      if (p->left->op == YYSTRING) {
         upgrade_to_number(p->left);
      }
      if (p->left->op == YYDOUBLE) {
         if (p->left->dval > 0) { sign = 1; }
         if (p->left->dval < 0) { sign = -1; }
         p->left->op = YYINTEGER;
         p->left->ival = sign;
      }
      else if (p->left->op == YYINTEGER) {
         if (p->left->ival > 0) { sign = 1; }
         if (p->left->ival < 0) { sign = -1; }
         p->left->ival = sign;
      }
      else if (p->left->op == YYRATIONAL) {
         Rational *deleteme = p->left->rval;
         p->left->op = YYINTEGER;
         p->left->ival = p->left->rval->sgn();
         delete deleteme;
      }
      memcpy(p, p->left, sizeof(Tree));
      free(freeme);
   }
   else if (p->op == YYSIN) {
      Tree *freeme = p->left;
      if (p->left->op == YYSTRING) {
         upgrade_to_number(p->left);
      }
      if (p->left->op == YYDOUBLE) {
         p->left->dval = sin(p->left->dval);
      }
      else if (p->left->op == YYINTEGER) {
         p->left->op = YYDOUBLE;
         p->left->dval = sin((double)p->left->ival);
      }
      else if (p->left->op == YYRATIONAL) {
         p->left->op = YYDOUBLE;
         Rational *deleteme = p->left->rval;
         p->left->dval = sin((double)*(p->left->rval));
         delete deleteme;
      }
      memcpy(p, p->left, sizeof(Tree));
      free(freeme);
   }
   else if (p->op == YYSQR) {
      Tree *freeme = p->left;
      if (p->left->op == YYSTRING) {
         upgrade_to_number(p->left);
      }
      if (p->left->op == YYDOUBLE) {
         p->left->dval = sqrt(p->left->dval);
      }
      else if (p->left->op == YYINTEGER) {
         p->left->op = YYDOUBLE;
         p->left->dval = sqrt((double)p->left->ival);
      }
      else if (p->left->op == YYRATIONAL) {
         p->left->op = YYDOUBLE;
         Rational *deleteme = p->left->rval;
         p->left->dval = sqrt((double)*(p->left->rval));
         delete deleteme;
      }
      memcpy(p, p->left, sizeof(Tree));
      free(freeme);
   }
   else if (p->op == YYTAN) {
      Tree *freeme = p->left;
      if (p->left->op == YYSTRING) {
         upgrade_to_number(p->left);
      }
      if (p->left->op == YYDOUBLE) {
         p->left->dval = tan(p->left->dval);
      }
      else if (p->left->op == YYINTEGER) {
         p->left->op = YYDOUBLE;
         p->left->dval = tan((double)p->left->ival);
      }
      else if (p->left->op == YYRATIONAL) {
         p->left->op = YYDOUBLE;
         Rational *deleteme = p->left->rval;
         p->left->dval = tan((double)*(p->left->rval));
         delete deleteme;
      }
      memcpy(p, p->left, sizeof(Tree));
      free(freeme);
   }

   if (p->left && p->right ) {
      if (p->op == '+' ||
            p->op == '-' ||
            p->op == '*' ||
            p->op == '/' ||
            p->op == '^' ||
            p->op == '&') {

         // ECMA-116 uses '&' ; for other types we'll just treat it like a '+'

         if ((p->left->op != p->right->op) || 
             (p->left->op == YYSTRING && p->op != '&')) {
            // in a mismatch, try to make strings into numbers
            if (p->left->op == YYSTRING) {
               upgrade_to_number(p->left);
            }
            if (p->right->op == YYSTRING) {
               upgrade_to_number(p->right);
            }

            if (p->left->op == YYRATIONAL && p->right->op == YYINTEGER) {
               upgrade_to_rational(p->right);
            }
            else if (p->left->op == YYINTEGER && p->right->op == YYRATIONAL) {
               upgrade_to_rational(p->left);
            }

            if (p->left->op == YYRATIONAL && p->right->op == YYDOUBLE) {
               upgrade_to_double(p->left);
            }
            else if (p->left->op == YYDOUBLE && p->right->op == YYRATIONAL) {
               upgrade_to_double(p->right);
            }

            if (p->left->op == YYINTEGER && p->right->op == YYDOUBLE) {
               upgrade_to_double(p->left);
            }
            else if (p->left->op == YYDOUBLE && p->right->op == YYINTEGER) {
               upgrade_to_double(p->right);
            }
         }

         if (p->left && p->right && p->left->op == p->right->op) {
            switch(p->left->op) {
               case YYDOUBLE:
                  switch(p->op) {
                     case '+':
                     case '&':
                        p->dval = p->left->dval + p->right->dval;
                        break;
                     case '-':
                        p->dval = p->left->dval - p->right->dval;
                        break;
                     case '*':
                        p->dval = p->left->dval * p->right->dval;
                        break;
                     case '/':
                        p->dval = p->left->dval / p->right->dval;
                        break;
                     case '^':
                        p->dval = pow(p->left->dval,p->right->dval);
                        break;
                     default:
                        fprintf(stderr, "INTERNAL ERROR %s:%d\n", __FILE__, __LINE__);
                        fprintf(stderr, "SOURCE %d:%d, UNRECOGNIZED MATH OP '%d'\n", p->line, p->col, p->op);
                        exit(-1);
                        break;
                  }
                  p->op = YYDOUBLE;
                  free(p->left);
                  p->left = NULL;
                  free(p->right);
                  p->right = NULL;
                  break;
               case YYINTEGER:
                  switch(p->op) {
                     case '+':
                     case '&':
                        p->ival = p->left->ival + p->right->ival;
                        break;
                     case '-':
                        p->ival = p->left->ival - p->right->ival;
                        break;
                     case '*':
                        p->ival = p->left->ival * p->right->ival;
                        break;
                     case '/':
                        p->ival = p->left->ival / p->right->ival;
                        break;
                     case '^':
                        p->ival = (int64_t) pow(p->left->ival,p->right->ival);
                        break;
                     default:
                        fprintf(stderr, "INTERNAL ERROR %s:%d\n", __FILE__, __LINE__);
                        fprintf(stderr, "SOURCE %d:%d, UNRECOGNIZED MATH OP '%d'\n", p->line, p->col, p->op);
                        exit(-1);
                        break;
                  }
                  p->op = YYINTEGER;
                  free(p->left);
                  p->left = NULL;
                  free(p->right);
                  p->right = NULL;
                  break;
               case YYRATIONAL:
                  switch(p->op) {
                     case '+':
                     case '&':
                        p->rval = new Rational (*(p->left->rval) + *(p->right->rval));
                        p->op = YYRATIONAL;
                        break;
                     case '-':
                        p->rval = new Rational (*(p->left->rval) - *(p->right->rval));
                        p->op = YYRATIONAL;
                        break;
                     case '*':
                        p->rval = new Rational (*(p->left->rval) * *(p->right->rval));
                        p->op = YYRATIONAL;
                        break;
                     case '/':
                        p->rval = new Rational (*(p->left->rval) / *(p->right->rval));
                        p->op = YYRATIONAL;
                        break;
                     case '^':
                        p->dval = pow((double)(*(p->left->rval)), (double) (*(p->right->rval)));
                        p->op = YYDOUBLE;
                        break;
                     default:
                        fprintf(stderr, "INTERNAL ERROR %s:%d\n", __FILE__, __LINE__);
                        fprintf(stderr, "SOURCE %d:%d, UNRECOGNIZED MATH OP '%d'\n", p->line, p->col, p->op);
                        exit(-1);
                        break;
                  }
                  delete p->left->rval;
                  free(p->left);
                  p->left = NULL;
                  delete p->right->rval;
                  free(p->right);
                  p->right = NULL;
                  break;
               case YYSTRING:
                  switch(p->op) {
                     case '&':
                        p->sval = (char *) malloc(strlen(p->left->sval) + strlen(p->right->sval) + 1);
                        sprintf((char *) p->sval, "%s%s", p->left->sval, p->right->sval);
                        p->op = YYSTRING;
                        break;
                     default:
                        fprintf(stderr, "INTERNAL ERROR %s:%d\n", __FILE__, __LINE__);
                        fprintf(stderr, "SOURCE %d:%d, STRING MATH LOGIC ERROR\n", p->line, p->col);
                        exit(-1);
                        break;
                  }
                  free((void *)p->left->sval);
                  free((void *)p->left);
                  p->left = NULL;
                  free((void *)p->right->sval);
                  free((void *)p->right);
                  p->right = NULL;
                  break;
            }
         }
         else {
            fprintf(stderr, "INTERNAL ERROR %s:%d\n", __FILE__, __LINE__);
            fprintf(stderr, "SOURCE %d:%d, OPERAND MISMATCH '%p:%d' '%p:%d'\n",
               p->line, p->col,
               p->left, p->left ? p->left->op : -1,
               p->right, p->right ? p->right->op : -1);
            exit(-1);
         }
      }
   }

   return p;
}

#define OP2NUM(x) ((((x)[0]) << 8) | ((x)[1]))

bool is_double_relation_true(Tree *left, const char *op, Tree *right) {
   switch(OP2NUM(op)) {
      case OP2NUM("=="):
         return left->dval == right->dval;
         break;
      case OP2NUM("<>"):
      case OP2NUM("!="): // let's be kind to C programmers...
         return left->dval != right->dval;
         break;
      case OP2NUM(">="):
         return left->dval >= right->dval;
         break;
      case OP2NUM("<="):
         return left->dval <= right->dval;
         break;
      case OP2NUM(">"):
         return left->dval > right->dval;
         break;
      case OP2NUM("<"):
         return left->dval < right->dval;
         break;
   }
   return false;
}

bool is_integer_relation_true(Tree *left, const char *op, Tree *right) {
   switch(OP2NUM(op)) {
      case OP2NUM("=="):
         return left->ival == right->ival;
         break;
      case OP2NUM("<>"):
      case OP2NUM("!="): // let's be kind to C programmers...
         return left->ival != right->ival;
         break;
      case OP2NUM(">="):
         return left->ival >= right->ival;
         break;
      case OP2NUM("<="):
         return left->ival <= right->ival;
         break;
      case OP2NUM(">"):
         return left->ival > right->ival;
         break;
      case OP2NUM("<"):
         return left->ival < right->ival;
         break;
   }
   return false;
}

bool is_rational_relation_true(Tree *left, const char *op, Tree *right) {
   switch(OP2NUM(op)) {
      case OP2NUM("=="):
         return *(left->rval) == *(right->rval);
         break;
      case OP2NUM("<>"):
      case OP2NUM("!="): // let's be kind to C programmers...
         return *(left->rval) != *(right->rval);
         break;
      case OP2NUM(">="):
         return *(left->rval) >= *(right->rval);
         break;
      case OP2NUM("<="):
         return *(left->rval) <= *(right->rval);
         break;
      case OP2NUM(">"):
         return *(left->rval) > *(right->rval);
         break;
      case OP2NUM("<"):
         return *(left->rval) < *(right->rval);
         break;
   }
   return false;
}

bool is_string_relation_true(Tree *left, const char *op, Tree *right) {
   int result = strcmp(left->sval, right->sval);
   switch(OP2NUM(op)) {
      case OP2NUM("=="):
         return result == 0;
         break;
      case OP2NUM("<>"):
      case OP2NUM("!="): // let's be kind to C programmers...
         return result != 0;
         break;
      case OP2NUM(">="):
         return result >= 0;
         break;
      case OP2NUM("<="):
         return result <= 0;
         break;
      case OP2NUM(">"):
         return result > 0;
         break;
      case OP2NUM("<"):
         return result < 0;
         break;
   }
   return false;
}

bool is_relation_true(Tree *left, const char *op, Tree *right) {
   // assumes left and right are the same type!
   switch (left->op) {
      case YYDOUBLE:
         return is_double_relation_true(left, op, right);
         break;
      case YYINTEGER:
         return is_integer_relation_true(left, op, right);
         break;
      case YYRATIONAL:
         return is_rational_relation_true(left, op, right);
         break;
      case YYSTRING:
         return is_string_relation_true(left, op, right);
         break;
   }
   return false;
}

#define GOSUB_STACKSIZE 1024
void run(Tree *p) {
   Tree *gosub_stack[GOSUB_STACKSIZE];
   int gosub_spot = 0;

   while (p) {
      Tree *np = p->next;
      switch (p->op) {
         case YYASSIGN:
         case YYLET:
            {
               int inuse = is_var_defined(p->left->sval);
               if (p->op == YYASSIGN && !inuse) {
                  fprintf(stderr, "WARNING: variable '%s' not in use line %d col %d, consider using LET\n",
                     p->left->sval, p->left->line, p->left->col);
               }
               else if (p->op == YYLET && inuse) {
                  fprintf(stderr, "WARNING: variable '%s' already in use line %d col %d\n",
                     p->left->sval, p->left->line, p->left->col);
               }
               Tree *result = evaluate(deep_copy(p->right));
               set_value(p->sval, result);
               free((void *)result);
            }
            break;
         case YYPRINT:
            {
               Tree *result = evaluate(deep_copy(p));
               for (Tree *mid = result->middle; mid; mid = mid->middle) {
                  switch (mid->op) {
                     case YYDOUBLE:
                        printf("%f ", mid->dval);
                        break;
                     case YYINTEGER:
                        printf("%li ", mid->ival);
                        break;
                     case YYRATIONAL:
                        {
                           char buf[1024];
                           mid->rval->print(buf);
                           printf("%s ", buf);
                        }
                        break;
                     case YYSTRING:
                        printf("%s ", mid->sval);
                        break;
                     default:
                        fprintf(stderr, "INTERNAL ERROR %s:%d\n", __FILE__, __LINE__);
                        fprintf(stderr, "SOURCE %d:%d, UNRECOGNIZED MID OP %d\n",
                           p->line, p->col, mid->op);
                        break;
                  }
               }
               printf("\n");
            }
            break;
         case YYFOR:
            {
               Tree *result = evaluate(deep_copy(p->left));
               set_value(p->sval, result);
            }
            break;
         case YYNEXT:
            {
               Tree *fore = get_for(p->sval);
               if (!fore) {
                  fprintf(stderr, "INTERNAL ERROR %s:%d\n", __FILE__, __LINE__);
                  fprintf(stderr, "SOURCE %d:%d, UNRECOGNIZED NEXT TARGET %s\n",
                     p->line, p->col, p->sval);
                  exit(-1);
               }
               Tree *start = evaluate(deep_copy(fore->left));
               Tree *fini = evaluate(deep_copy(fore->right));
               const Val *valuep = get_value(fore->sval);
               Val value = *valuep;
               switch(value.typ) {
                  case 'd':
                     {
                        double step = 1.0;
                        if (fini->dval < start->dval) {
                           step = -1.0;
                        }
                        if (fore->middle) {
                           Tree *middle = evaluate(deep_copy(fore->middle));
                           step = middle->dval;
                        }
                        value.dval += step;
                        set_value(fore->sval, value);
                        if (step > 0.0 && value.dval <= fini->dval) {
                           np = fore->next;
                        }
                        else if (step < 0.0 && value.dval >= fini->dval) {
                           np = fore->next;
                        }
                     }
                     break;
                  case 'i':
                     {
                        int64_t step = 1;
                        if (fini->ival < start->ival) {
                           step = -1.0;
                        }
                        if (fore->middle) {
                           Tree *middle = evaluate(deep_copy(fore->middle));
                           step = middle->ival;
                        }
                        value.ival += step;
                        set_value(fore->sval, value);
                        if (step > 0 && value.ival <= fini->ival) {
                           np = fore->next;
                        }
                        else if (step < 0 && value.ival >= fini->ival) {
                           np = fore->next;
                        }
                     }
                     break;
                  case 'r':
                     {
                        Rational value_rval = *(value.rval);
                        Rational step = Rational(1,1,0,1);
                        if (fini->rval < start->rval) {
                           step = Rational(-1,1,0,1);
                        }
                        if (fore->middle) {
                           Tree *middle = evaluate(deep_copy(fore->middle));
                           step = *(middle->rval);
                        }
                        value_rval = value_rval + step;
                        value.rval = new Rational(value_rval);
                        set_value(fore->sval, value);
                        if (step.sgn() > 0 && value_rval <= *(fini->rval)) {
                           np = fore->next;
                        }
                        else if (step.sgn() < 0 && value_rval >= *(fini->rval)) {
                           np = fore->next;
                        }
                     }
                     break;
                  case 's':
                     // punt, this is just stupid
                     break;
               }
            }
            break;
         case YYSTOP: // why are there two of these???
         case YYEND:  // when they both do the same things???
            exit(0);
            break;
         case YYGOTO:
            {
               Tree *t = get_label(p->sval);
               if (!t) {
                  fprintf(stderr, "INTERNAL ERROR %s:%d\n", __FILE__, __LINE__);
                  fprintf(stderr, "SOURCE %d:%d, UNRECOGNIZED GOTO TARGET '%s'\n",
                     p->line, p->col, p->sval);
                  exit(-1);
               }
               np = t;
            }
            break;
         case YYGOSUB:
            {
               Tree *t = get_label(p->sval);
               if (!t) {
                  fprintf(stderr, "INTERNAL ERROR %s:%d\n", __FILE__, __LINE__);
                  fprintf(stderr, "SOURCE %d:%d, UNRECOGNIZED GOSUB TARGET %s\n",
                     p->line, p->col, p->sval);
                  exit(-1);
               }

               gosub_stack[gosub_spot++] = np;
               if (gosub_spot == GOSUB_STACKSIZE) {
                  fprintf(stderr, "INTERNAL ERROR %s:%d\n", __FILE__, __LINE__);
                  fprintf(stderr, "SOURCE %d:%d, GOSUB STACK OVERFLOW\n", p->line, p->col);
                  exit(-1);
               }

               np = t;
            }
            break;
         case YYRETURN:
            {
               gosub_spot--;
               if (gosub_spot < 0) {
                  fprintf(stderr, "INTERNAL ERROR %s:%d\n", __FILE__, __LINE__);
                  fprintf(stderr, "SOURCE %d:%d, GOSUB STACK UNDERFLOW\n", p->line, p->col);
                  exit(-1);
               }
               np = gosub_stack[gosub_spot];
            }
            break;
         case YYIF:
            {
               Tree *left = evaluate(deep_copy(p->left));
               Tree *right = evaluate(deep_copy(p->right));
               Tree *target = get_label(p->middle->sval);
               if (!target) {
                  fprintf(stderr, "INTERNAL ERROR %s:%d\n", __FILE__, __LINE__);
                  fprintf(stderr, "SOURCE %d:%d, UNKNOWN IF TARGET '%s'\n", p->line, p->col, p->sval);
                  exit(-1);
               }
               if (left->op != right->op) {
                  // in a mismatch, try to make strings into numbers
                  if (p->left->op == YYSTRING) {
                     upgrade_to_number(p->left);
                  }
                  if (p->right->op == YYSTRING) {
                     upgrade_to_number(p->right);
                  }

                  if (p->left->op == YYRATIONAL && p->right->op == YYINTEGER) {
                     upgrade_to_rational(p->right);
                  }
                  else if (p->left->op == YYINTEGER && p->right->op == YYRATIONAL) {
                     upgrade_to_rational(p->left);
                  }

                  if (p->left->op == YYRATIONAL && p->right->op == YYDOUBLE) {
                     upgrade_to_double(p->left);
                  }
                  else if (p->left->op == YYDOUBLE && p->right->op == YYRATIONAL) {
                     upgrade_to_double(p->right);
                  }

                  if (p->left->op == YYINTEGER && p->right->op == YYDOUBLE) {
                     upgrade_to_double(p->left);
                  }
                  else if (p->left->op == YYDOUBLE && p->right->op == YYINTEGER) {
                     upgrade_to_double(p->right);
                  }
               }

               if (left->op == right->op) {
                  if (is_relation_true(left, p->sval, right)) {
                     np = target;
                  }
               }
               else {
                  fprintf(stderr, "INTERNAL ERROR %s:%d\n", __FILE__, __LINE__);
                  fprintf(stderr, "SOURCE %d:%d, LEFT/RIGHT OP MISMATCH %d %d\n", p->line, p->col, left->op, right->op);
                  exit(-1);
               }
            }
            break;
         case YYON:
            {
               Tree *result = evaluate(deep_copy(p->left));
               int i = -1;
               switch (result->op) {
                  case YYDOUBLE:
                     i = (int) result->dval;
                     break;
                  case YYINTEGER:
                     i = (int) result->ival;
                     break;
                  case YYRATIONAL:
                     i = (int) ((double)(*result->rval));
                     break;
                  case YYSTRING:
                     i = atoi(result->sval);
                     break;
                  default:
                     fprintf(stderr, "INTERNAL ERROR %s:%d\n", __FILE__, __LINE__);
                     fprintf(stderr, "SOURCE %d:%d, UNHANDLED OP %d\n", p->line, p->left->col, result->op);
                     exit(-1);
                     break;
               }
               if (i < 0) {
                  fprintf(stderr, "INTERNAL ERROR %s:%d\n", __FILE__, __LINE__);
                  fprintf(stderr, "SOURCE %d:%d, NEGATIVED INDEX %d\n", p->line, p->left->col, i);
                  exit(-1);
               }
               int oi = i;
               Tree *label = p->right;
               while (i && label) {
                  i--;
                  label = label->middle;
               }
               if (i || label == NULL) {
                  fprintf(stderr, "INTERNAL ERROR %s:%d\n", __FILE__, __LINE__);
                  fprintf(stderr, "SOURCE %d:%d, INDEX %d OUT OF RANGE\n", p->line, p->left->col, oi);
                  exit(-1);
               }
               Tree *target = get_label(label->sval);
               if (!target) {
                  fprintf(stderr, "INTERNAL ERROR %s:%d\n", __FILE__, __LINE__);
                  fprintf(stderr, "SOURCE %d:%d, UNDEFINED TARGET '%s'\n", p->line, label->col, label->sval);
                  exit(-1);
               }
               if (p->ival) { // GOSUB
                  gosub_stack[gosub_spot++] = np;
                  if (gosub_spot == GOSUB_STACKSIZE) {
                     fprintf(stderr, "INTERNAL ERROR %s:%d\n", __FILE__, __LINE__);
                     fprintf(stderr, "SOURCE %d:%d, GOSUB STACK OVERFLOW\n", p->line, p->col);
                     exit(-1);
                  }
               }
               np = target;
            }
            break;
         case YYREM:
            {
               // do... nothing...
               // this is here so the default case doesn't howl at REM statements
               // go figure.
            }
            break;
         case YYDATA:
            {
               // as above, for REM
            }
            break;
         case YYRESTORE:
            {
               rewind_data();
            }
            break;
         case YYREAD:
            {
               for (Tree *varname = p->right; varname; varname = varname->middle) {
                  Val value;
                  value.typ = next_data_type();
                  switch(value.typ) {
                     case 'd':
                        get_data(value.dval);
                        set_value(varname->sval, value);
                        break;
                     case 'i':
                        get_data(value.ival);
                        set_value(varname->sval, value);
                        break;
                     case 'r':
                        get_data(value.rval);
                        set_value(varname->sval, value);
                        break;
                     case 's':
                        get_data(value.sval);
                        set_value(varname->sval, value);
                        break;
                     default:
                        fprintf(stderr, "INTERNAL ERROR %s:%d\n", __FILE__, __LINE__);
                        fprintf(stderr, "SOURCE %d:%d, DATA READ OVERFLOW\n", p->line, p->col);
                        exit(-1);
                        break;
                  }
               }
            }
            break;
         default:
            fprintf(stderr, "!!!! src:%d op %d line %d col %d\n", __LINE__, p->op, p->line, p->col);
            exit(-1);
            break;
      }
      p = np;
   }
}

void runtree(Tree *root) {
   register_labels(root);
   register_for(root);
   register_data(root);
   run(root);
}


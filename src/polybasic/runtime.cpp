#include <math.h>

#include "tree.h"
#include "polybasic.tab.hpp"
#include "dumptree.h"
#include "runtime_lbls.h"
#include "runtime_for.h"
#include "runtime_vars.h"
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

Tree i2r(Tree t) {
   int i = t.ival;
   char sign = 1;
   if (i < 0) {
      i = -i;
      sign = -1;
   }
   Tree ret;
   ret.op = YYRATIONAL;
   ret.rval = new Rational(sign, i, 0, 1);
   return ret;
}

Tree i2d(Tree t) {
   t.op = YYDOUBLE;
   t.dval = (double) t.ival;
   return t;
}

Tree r2d(Tree t) {
   t.op = YYDOUBLE;
   t.dval = (double) (*t.rval);
   return t;
}

Tree s2d(Tree t) {
   t.op = YYDOUBLE;
   t.dval = atof(t.sval);
   return t;
}

Tree s2i(Tree t) {
   t.op = YYINTEGER;
   t.ival = atoll(t.sval);
   return t;
}

Tree s2r(Tree t) {
   t.op = YYRATIONAL;
   t.rval = new Rational(t.sval);
   return t;
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
   subtree->next = NULL;

   return copy;
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
   else if (p->op == YYEXP) {
      Tree *freeme = p->left;
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
      p->left->dval = (double)rand() / (double)RAND_MAX;
   }
   else if (p->op == YYSGN) {
      Tree *freeme = p->left;
      int sign = 0;
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
          p->op == '/') {

         if (p->left->op != p->right->op) {
         }
      }
   }

   return p;
}

Tree evaluate(Tree p) {
   Tree ret, left, right;
   memset((void *)&ret, 0, sizeof(ret));
   ret.op = '?'; // the unknown mystery type

   if (p.left->op != YYDOUBLE ||
       p.left->op != YYINTEGER ||
       p.left->op != YYRATIONAL ||
       p.left->op != YYSTRING) {
      left = *(p.left);
      left = evaluate(left);
      p.left = &left;
   }

   if (p.right->op != YYDOUBLE ||
       p.right->op != YYINTEGER ||
       p.right->op != YYRATIONAL ||
       p.right->op != YYSTRING) {
      right = *(p.right);
      right = evaluate(right);
      p.right =&right;
   }

   switch(p.op) {
      case YYDOUBLE:
      case YYINTEGER:
      case YYRATIONAL:
      case YYSTRING:
         return p;
         break;
      case '+':
         {
            Tree left = *p.left;
            Tree right = *p.right;

            if (left.op != right.op) {
               // in a mismatch, try to make strings into numbers
               if (left.op == YYSTRING && right.op != YYSTRING) {
                  if(strchr(left.sval, '#') == left.sval) {
                     left = s2r(left);
                  }
                  else if (strchr(left.sval, '.') || strchr(left.sval, 'E')) {
                     left = s2d(left);
                  }
                  else {
                     left = s2i(left);
                  }
               }
               else if (left.op != YYSTRING && right.op == YYSTRING) {
                  if(strchr(right.sval, '#') == right.sval) {
                     right = s2r(right);
                  }
                  else if (strchr(right.sval, '.') || strchr(right.sval, 'E')) {
                     right = s2d(right);
                  }
                  else {
                     right = s2i(right);
                  }
               }

               if (left.op == YYRATIONAL && right.op == YYINTEGER) {
                  right = i2r(right);
               }
               else if (left.op == YYINTEGER && right.op == YYRATIONAL) {
                  left = i2r(left);
               }
               else if (left.op == YYRATIONAL && right.op == YYDOUBLE) {
                  left = r2d(left);
               }
               else if (left.op == YYDOUBLE && right.op == YYRATIONAL) {
                  right = r2d(right);
               }
               else if (left.op == YYINTEGER && right.op == YYDOUBLE) {
                  left = i2d(left);
               }
               else if (left.op == YYDOUBLE && right.op == YYINTEGER) {
                  right = i2d(right);
               }
            }

            if (left.op == right.op) {
               switch(left.op) {
                  case YYDOUBLE:
                     ret.op = YYDOUBLE;
                     ret.dval = left.dval + right.dval;
                     break;
                  case YYINTEGER:
                     ret.op = YYINTEGER;
                     ret.ival = left.ival + right.ival;
                     break;
                  case YYRATIONAL:
                     ret.op = YYRATIONAL;
                     ret.rval = new Rational (*(left.rval) + *(right.rval));
                     break;
                  case YYSTRING:
                     ret.op = YYSTRING;
                     ret.sval = (char *) malloc(strlen(left.sval) + strlen(right.sval) + 1);
                     sprintf((char *) ret.sval, "%s%s", left.sval, right.sval);
                     break;
               }
            }
            return ret;
         }
         break;
      case '-':
         {
            Tree left = *p.left;
            Tree right = *p.right;

            if (left.op != right.op) {
               // in a mismatch, try to make strings into numbers
               if (left.op == YYSTRING && right.op != YYSTRING) {
                  if(strchr(left.sval, '#') == left.sval) {
                     left = s2r(left);
                  }
                  else if (strchr(left.sval, '.') || strchr(left.sval, 'E')) {
                     left = s2d(left);
                  }
                  else {
                     left = s2i(left);
                  }
               }
               else if (left.op != YYSTRING && right.op == YYSTRING) {
                  if(strchr(right.sval, '#') == right.sval) {
                     right = s2r(right);
                  }
                  else if (strchr(right.sval, '.') || strchr(right.sval, 'E')) {
                     right = s2d(right);
                  }
                  else {
                     right = s2i(right);
                  }
               }

               if (left.op == YYRATIONAL && right.op == YYINTEGER) {
                  right = i2r(right);
               }
               else if (left.op == YYINTEGER && right.op == YYRATIONAL) {
                  left = i2r(left);
               }
               else if (left.op == YYRATIONAL && right.op == YYDOUBLE) {
                  left = r2d(left);
               }
               else if (left.op == YYDOUBLE && right.op == YYRATIONAL) {
                  right = r2d(right);
               }
               else if (left.op == YYINTEGER && right.op == YYDOUBLE) {
                  left = i2d(left);
               }
               else if (left.op == YYDOUBLE && right.op == YYINTEGER) {
                  right = i2d(right);
               }
            }

            if (left.op == right.op) {
               switch(left.op) {
                  case YYDOUBLE:
                     ret.op = YYDOUBLE;
                     ret.dval = left.dval - right.dval;
                     break;
                  case YYINTEGER:
                     ret.op = YYINTEGER;
                     ret.ival = left.ival - right.ival;
                     break;
                  case YYRATIONAL:
                     ret.op = YYRATIONAL;
                     ret.rval = new Rational (*(left.rval) - *(right.rval));
                     break;
                  case YYSTRING:
                     fprintf(stderr, "WARNING: string subtraction line %d col %d\n", left.line, left.col);
                     ret.op = YYSTRING;
                     ret.sval = (char *) malloc(strlen(left.sval) + strlen(right.sval) + 2);
                     sprintf((char *) ret.sval, "%s-%s", left.sval, right.sval);
                     break;
               }
            }
            return ret;
         }
         break;
      case '*':
         {
            Tree left = *p.left;
            Tree right = *p.right;

            if (left.op != right.op) {
               // in a mismatch, try to make strings into numbers
               if (left.op == YYSTRING && right.op != YYSTRING) {
                  if(strchr(left.sval, '#') == left.sval) {
                     left = s2r(left);
                  }
                  else if (strchr(left.sval, '.') || strchr(left.sval, 'E')) {
                     left = s2d(left);
                  }
                  else {
                     left = s2i(left);
                  }
               }
               else if (left.op != YYSTRING && right.op == YYSTRING) {
                  if(strchr(right.sval, '#') == right.sval) {
                     right = s2r(right);
                  }
                  else if (strchr(right.sval, '.') || strchr(right.sval, 'E')) {
                     right = s2d(right);
                  }
                  else {
                     right = s2i(right);
                  }
               }

               if (left.op == YYRATIONAL && right.op == YYINTEGER) {
                  right = i2r(right);
               }
               else if (left.op == YYINTEGER && right.op == YYRATIONAL) {
                  left = i2r(left);
               }
               else if (left.op == YYRATIONAL && right.op == YYDOUBLE) {
                  left = r2d(left);
               }
               else if (left.op == YYDOUBLE && right.op == YYRATIONAL) {
                  right = r2d(right);
               }
               else if (left.op == YYINTEGER && right.op == YYDOUBLE) {
                  left = i2d(left);
               }
               else if (left.op == YYDOUBLE && right.op == YYINTEGER) {
                  right = i2d(right);
               }
            }

            if (left.op == right.op) {
               switch(left.op) {
                  case YYDOUBLE:
                     ret.op = YYDOUBLE;
                     ret.dval = left.dval * right.dval;
                     break;
                  case YYINTEGER:
                     ret.op = YYINTEGER;
                     ret.ival = left.ival * right.ival;
                     break;
                  case YYRATIONAL:
                     ret.op = YYRATIONAL;
                     ret.rval = new Rational (*(left.rval) * *(right.rval));
                     break;
                  case YYSTRING:
                     fprintf(stderr, "WARNING: string multiplication line %d col %d\n", left.line, left.col);
                     ret.op = YYSTRING;
                     ret.sval = (char *) malloc(strlen(left.sval) + strlen(right.sval) + 2);
                     sprintf((char *) ret.sval, "%s*%s", left.sval, right.sval);
                     break;
               }
            }
            return ret;
         }
         break;
      case '/':
         {
            Tree left = *p.left;
            Tree right = *p.right;

            if (left.op != right.op) {
               // in a mismatch, try to make strings into numbers
               if (left.op == YYSTRING && right.op != YYSTRING) {
                  if(strchr(left.sval, '#') == left.sval) {
                     left = s2r(left);
                  }
                  else if (strchr(left.sval, '.') || strchr(left.sval, 'E')) {
                     left = s2d(left);
                  }
                  else {
                     left = s2i(left);
                  }
               }
               else if (left.op != YYSTRING && right.op == YYSTRING) {
                  if(strchr(right.sval, '#') == right.sval) {
                     right = s2r(right);
                  }
                  else if (strchr(right.sval, '.') || strchr(right.sval, 'E')) {
                     right = s2d(right);
                  }
                  else {
                     right = s2i(right);
                  }
               }

               if (left.op == YYRATIONAL && right.op == YYINTEGER) {
                  right = i2r(right);
               }
               else if (left.op == YYINTEGER && right.op == YYRATIONAL) {
                  left = i2r(left);
               }
               else if (left.op == YYRATIONAL && right.op == YYDOUBLE) {
                  left = r2d(left);
               }
               else if (left.op == YYDOUBLE && right.op == YYRATIONAL) {
                  right = r2d(right);
               }
               else if (left.op == YYINTEGER && right.op == YYDOUBLE) {
                  left = i2d(left);
               }
               else if (left.op == YYDOUBLE && right.op == YYINTEGER) {
                  right = i2d(right);
               }
            }

            if (left.op == right.op) {
               switch(left.op) {
                  case YYDOUBLE:
                     ret.op = YYDOUBLE;
                     ret.dval = left.dval / right.dval;
                     break;
                  case YYINTEGER:
                     ret.op = YYINTEGER;
                     ret.ival = left.ival / right.ival;
                     break;
                  case YYRATIONAL:
                     ret.op = YYRATIONAL;
                     ret.rval = new Rational (*(left.rval) / *(right.rval));
                     break;
                  case YYSTRING:
                     fprintf(stderr, "WARNING: string division line %d col %d\n", left.line, left.col);
                     ret.op = YYSTRING;
                     ret.sval = (char *) malloc(strlen(left.sval) + strlen(right.sval) + 2);
                     sprintf((char *) ret.sval, "%s/%s", left.sval, right.sval);
                     break;
               }
            }
            return ret;
         }
         break;
      default:
         printf("DEFAULT %d %s\n", p.op, p.sval ? p.sval : "<nil>");
         break;
   }

   return ret;
}

void run(Tree *p) {
   while (p) {
      switch (p->op) {
         case '*':
            fprintf(stderr, "src:%d op %d line %d col %d\n", __LINE__, p->op, p->line, p->col);
            dumpline(p);
            break;
         case '+':
            fprintf(stderr, "src:%d op %d line %d col %d\n", __LINE__, p->op, p->line, p->col);
            dumpline(p);
            break;
         case '-':
            fprintf(stderr, "src:%d op %d line %d col %d\n", __LINE__, p->op, p->line, p->col);
            dumpline(p);
            break;
         case '/':
            fprintf(stderr, "src:%d op %d line %d col %d\n", __LINE__, p->op, p->line, p->col);
            dumpline(p);
            break;
         case YYABS:
            fprintf(stderr, "src:%d op %d line %d col %d\n", __LINE__, p->op, p->line, p->col);
            dumpline(p);
            break;
         case YYASSIGN:
            {
               int inuse = is_var_defined(p->left->sval);
               if (!inuse) {
                  fprintf(stderr, "WARNING: variable '%s' not in use line %d col %d, consider using LET\n",
                     p->left->sval, p->left->line, p->left->col);
               }
               Tree *result = evaluate(deep_copy(p->right));
assert(0);
            }
            break;
         case YYATN:
            fprintf(stderr, "src:%d op %d line %d col %d\n", __LINE__, p->op, p->line, p->col);
            dumpline(p);
            break;
         case YYBLABEL:
            fprintf(stderr, "src:%d op %d line %d col %d\n", __LINE__, p->op, p->line, p->col);
            dumpline(p);
            break;
         case YYCOS:
            fprintf(stderr, "src:%d op %d line %d col %d\n", __LINE__, p->op, p->line, p->col);
            dumpline(p);
            break;
         case YYDATA:
            fprintf(stderr, "src:%d op %d line %d col %d\n", __LINE__, p->op, p->line, p->col);
            dumpline(p);
            break;
         case YYDBL:
            fprintf(stderr, "src:%d op %d line %d col %d\n", __LINE__, p->op, p->line, p->col);
            dumpline(p);
            break;
         case YYDOUBLE:
            fprintf(stderr, "src:%d op %d line %d col %d\n", __LINE__, p->op, p->line, p->col);
            dumpline(p);
            break;
         case YYEND:
            fprintf(stderr, "src:%d op %d line %d col %d\n", __LINE__, p->op, p->line, p->col);
            dumpline(p);
            break;
         case YYEXP:
            fprintf(stderr, "src:%d op %d line %d col %d\n", __LINE__, p->op, p->line, p->col);
            dumpline(p);
            break;
         case YYFOR:
            fprintf(stderr, "src:%d op %d line %d col %d\n", __LINE__, p->op, p->line, p->col);
            dumpline(p);
            break;
         case YYGOSUB:
            fprintf(stderr, "src:%d op %d line %d col %d\n", __LINE__, p->op, p->line, p->col);
            dumpline(p);
            break;
         case YYGOTO:
            fprintf(stderr, "src:%d op %d line %d col %d\n", __LINE__, p->op, p->line, p->col);
            dumpline(p);
            break;
         case YYIF:
            fprintf(stderr, "src:%d op %d line %d col %d\n", __LINE__, p->op, p->line, p->col);
            dumpline(p);
            break;
         case YYINPUT:
            fprintf(stderr, "src:%d op %d line %d col %d\n", __LINE__, p->op, p->line, p->col);
            dumpline(p);
            break;
         case YYINT:
            fprintf(stderr, "src:%d op %d line %d col %d\n", __LINE__, p->op, p->line, p->col);
            dumpline(p);
            break;
         case YYINTEGER:
            fprintf(stderr, "src:%d op %d line %d col %d\n", __LINE__, p->op, p->line, p->col);
            dumpline(p);
            break;
         case YYLABEL:
            fprintf(stderr, "src:%d op %d line %d col %d\n", __LINE__, p->op, p->line, p->col);
            dumpline(p);
            break;
         case YYLET:
            fprintf(stderr, "src:%d op %d line %d col %d\n", __LINE__, p->op, p->line, p->col);
            dumpline(p);
            break;
         case YYLOG:
            fprintf(stderr, "src:%d op %d line %d col %d\n", __LINE__, p->op, p->line, p->col);
            dumpline(p);
            break;
         case YYNEXT:
            fprintf(stderr, "src:%d op %d line %d col %d\n", __LINE__, p->op, p->line, p->col);
            dumpline(p);
            break;
         case YYPRINT:
            fprintf(stderr, "src:%d op %d line %d col %d\n", __LINE__, p->op, p->line, p->col);
            dumpline(p);
            break;
         case YYRANDOMIZE:
            fprintf(stderr, "src:%d op %d line %d col %d\n", __LINE__, p->op, p->line, p->col);
            dumpline(p);
            break;
         case YYRAT:
            fprintf(stderr, "src:%d op %d line %d col %d\n", __LINE__, p->op, p->line, p->col);
            dumpline(p);
            break;
         case YYRATIONAL:
            fprintf(stderr, "src:%d op %d line %d col %d\n", __LINE__, p->op, p->line, p->col);
            dumpline(p);
            break;
         case YYREAD:
            fprintf(stderr, "src:%d op %d line %d col %d\n", __LINE__, p->op, p->line, p->col);
            dumpline(p);
            break;
         case YYRELATION:
            fprintf(stderr, "src:%d op %d line %d col %d\n", __LINE__, p->op, p->line, p->col);
            dumpline(p);
            break;
         case YYREM:
            fprintf(stderr, "src:%d op %d line %d col %d\n", __LINE__, p->op, p->line, p->col);
            dumpline(p);
            break;
         case YYRETURN:
            fprintf(stderr, "src:%d op %d line %d col %d\n", __LINE__, p->op, p->line, p->col);
            dumpline(p);
            break;
         case YYRND:
            fprintf(stderr, "src:%d op %d line %d col %d\n", __LINE__, p->op, p->line, p->col);
            dumpline(p);
            break;
         case YYSGN:
            fprintf(stderr, "src:%d op %d line %d col %d\n", __LINE__, p->op, p->line, p->col);
            dumpline(p);
            break;
         case YYSIN:
            fprintf(stderr, "src:%d op %d line %d col %d\n", __LINE__, p->op, p->line, p->col);
            dumpline(p);
            break;
         case YYSQR:
            fprintf(stderr, "src:%d op %d line %d col %d\n", __LINE__, p->op, p->line, p->col);
            dumpline(p);
            break;
         case YYSTOP:
            fprintf(stderr, "src:%d op %d line %d col %d\n", __LINE__, p->op, p->line, p->col);
            dumpline(p);
            break;
         case YYSTR:
            fprintf(stderr, "src:%d op %d line %d col %d\n", __LINE__, p->op, p->line, p->col);
            dumpline(p);
            break;
         case YYSTRING:
            fprintf(stderr, "src:%d op %d line %d col %d\n", __LINE__, p->op, p->line, p->col);
            dumpline(p);
            break;
         case YYTAN:
            fprintf(stderr, "src:%d op %d line %d col %d\n", __LINE__, p->op, p->line, p->col);
            dumpline(p);
            break;
         case YYVARNAME:
            fprintf(stderr, "src:%d op %d line %d col %d\n", __LINE__, p->op, p->line, p->col);
            dumpline(p);
            break;
         default:
            fprintf(stderr, "unrecognized op %d line %d col %d\n", p->op, p->line, p->col);
            dumpline(p);
            exit(-1);
            break;
      }
      p = p->next;
   }
}

void runtree(Tree *root) {
   register_labels(root);
   register_for(root);
   run(root);
}


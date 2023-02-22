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

Tree evaluate(Tree p) {
   Tree ret;
   memset((void *)&ret, 0, sizeof(ret));
   ret.op = '?'; // the unknown mystery type

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
               Tree res = evaluate(*(p->right));
               Val val;
               switch(res.op) {
                  case YYDOUBLE:
                     val.typ = 'd';
                     val.dval = res.dval;
                     break;
                  case YYINTEGER:
                     val.typ = 'i';
                     val.ival = res.ival;
                     break;
                  case YYRATIONAL:
                     val.typ = 'r';
                     val.rval = res.rval;
                     break;
                  case YYSTRING:
                     val.typ = 's';
                     val.sval = res.sval;
                     break;
               }
               set_value(p->left->sval, val);
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


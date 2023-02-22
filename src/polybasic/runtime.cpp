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
printf("------------\n");
                     dumpline(p.left);
                     dumpline(p.right);
printf("------------\n");
            if (p.left->op == p.right->op) {
               switch(p.left->op) {
                  case YYDOUBLE:
                     ret.op = YYDOUBLE;
                     ret.dval = p.left->dval + p.right->dval;
                     break;
                  case YYINTEGER:
                     ret.op = YYINTEGER;
                     ret.ival = p.left->ival + p.right->ival;
                     break;
                  case YYRATIONAL:
                     ret.op = YYRATIONAL;
                     ret.rval = new Rational (*(p.left->rval) + *(p.right->rval));
                     break;
                  case YYSTRING:
                     ret.op = YYSTRING;
                     ret.sval = (char *) malloc(strlen(p.left->sval) + strlen(p.right->sval) + 1);
                     sprintf((char *) ret.sval, "%s%s", p.left->sval, p.right->sval);
                     break;
               }
printf("------------\n");
                     dumpline(&ret);
printf("------------\n");
               exit(0);
            }
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


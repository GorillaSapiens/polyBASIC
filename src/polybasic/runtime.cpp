#include "tree.h"
#include "polybasic.tab.hpp"
#include "dumptree.h"
#include "runtime_lbls.h"
#include "runtime_for.h"
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
            fprintf(stderr, "src:%d op %d line %d col %d\n", __LINE__, p->op, p->line, p->col);
            dumpline(p);
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


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

void runtree(Tree *root) {
   register_labels(root);
   register_for(root);
}


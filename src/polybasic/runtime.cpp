#include "dumptree.h"
#include "runtime_lbls.h"
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
//            dumptree(prev);
            exit(-1);
         }
         else {
            set_label(root);
         }
      }
      root = root->next;
   }
}

void runtree(Tree *root) {
//  dumptree(root);
   register_labels(root);
}


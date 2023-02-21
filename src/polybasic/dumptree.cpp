
#include "rational.h"
#include "tree.h"

#include "mapping2.h"

void dump_tree(Tree *root) {
   const char *opname = NULL;

    for (int i = 0; reserved[i].name; i++) {
       if (reserved[i].token == root->op) {
          opname = reserved[i].name;
          break;
       }
    }

   if (opname) {
      printf("%p :: line %d col %d, op=%s(%d)\n", root, root->line, root->col, opname ? opname : "<nil>", root->op);
   }
   else {
      printf("%p :: line %d col %d, op=%c(%d)\n", root, root->line, root->col, root->op, root->op);
   }
   printf("   label:'%s'\n", root->label ? root->label : "<nil>");

if (opname) {
#include "mapping3.h"
}

   printf("   left =%p\n", root->left);
   printf(" middle =%p\n", root->middle);
   printf("  right =%p\n", root->right);
   //printf("   prev =%p\n", root->prev);
   printf("   next =%p\n", root->next);
   printf("=====\n");

   if (root->left) { dump_tree(root->left); }
   if (root->middle) { dump_tree(root->middle); }
   if (root->right) { dump_tree(root->right); }
   if (root->next) { dump_tree(root->next); }
   //if (root->prev) { dump_tree(root->prev); }
}

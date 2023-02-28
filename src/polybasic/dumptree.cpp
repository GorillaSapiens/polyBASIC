#include "eprintf.hpp"
#include "tree.hpp"
#include "polybasic.tab.hpp"
#include "rational.hpp"
#include "mapping.hpp"

static void dumpval(Tree *root, char valtype) {
   switch(valtype) {
      case 'd':
         {
            char buf[1024];
            sprintf(buf, "%g", root->dval);
            if (!strchr(buf, '.')) {
               strcat(buf, ".0");
            }
            printf("%s", buf);
         }
         break;
      case 'i':
         printf("ival=%li\n", root->ival);
         break;
      case 'r':
         {
            char buf[1024];
            root->rval->shortprint(buf, sizeof(buf));
            printf("rval=\"%s\"\n", buf);
         }
         break;
      case 's':
         printf("sval='%s'\n", root->sval ? root->sval : "<null>");
         break;
   }
}

static void dumpthing(Tree *root, bool andnext) {
   const char *opname = NULL;

   if (!root) {
      printf("root=<nil>\n");
      return;
   }

   int index = -1;
   for (int i = 0; reserved[i].name; i++) {
      if (reserved[i].token == root->op) {
         index = i;
         opname = reserved[i].name;
         break;
      }
   }

   if (opname) {
      printf("%p :: line %d col %d, op=%s(%d)\n", root, root->line, root->col, opname ? opname : "<nil>", root->op);
      if (reserved[index].valprint) {
         dumpval(root, reserved[index].valprint);
      }
   }
   else {
      printf("%p :: line %d col %d, op=%c(%d)\n", root, root->line, root->col, root->op, root->op);
   }
   printf("   label:'%s'\n", root->label ? root->label : "<nil>");

   printf("   left =%p\n", root->left);
   printf(" middle =%p\n", root->middle);
   printf("  right =%p\n", root->right);
   //printf("   prev =%p\n", root->prev);
   printf("   next =%p\n", root->next);
   printf("=====\n");

   if (root->left) { dumpthing(root->left, andnext); }
   if (root->middle) { dumpthing(root->middle, andnext); }
   if (root->right) { dumpthing(root->right, andnext); }
   if (andnext && root->next) { dumpthing(root->next, andnext); }
}

void dumptree(Tree *root, int line) {
   if (line == 0) {
      dumpthing(root, true);
   }
   else {
      while (root && root->line != line) {
         root = root->next;
      }
      if (root) {
         dumpthing(root, false);
      }
      else {
         GURU;
         eprintf("ERROR: NO PARSE TREE FOR LINE %0%n", line);
      }
   }
}

void dumpline(Tree *root) {
   dumpthing(root, false);
}

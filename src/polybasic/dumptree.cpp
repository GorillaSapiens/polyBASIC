#include "eprintf.hpp"
#include "tree.hpp"
#include "polybasic.tab.hpp"
#include "rational.hpp"
#include "mapping.hpp"

static void dumpvalue(Tree *root) {
   switch(root->value.index()) {
      case V_V:
         {
            printf("   value:[void]\n");
         }
         break;
      case V_D:
         {
            char buf[1024];
            sprintf(buf, "%g", V_AS_D(root->value));
            if (!strchr(buf, '.')) {
               strcat(buf, ".0");
            }
            printf("   value:[double] %s\n", buf);
         }
         break;
      case V_I:
         printf("   value:[int] %li\n", V_AS_I(root->value));
         break;
      case V_R:
         {
            char buf[1024];
            V_AS_R(root->value).shortprint(buf, sizeof(buf));
            printf("   value:[rational] %s\n", buf);
         }
         break;
      case V_S:
         {
            const char *p = V_AS_S(root->value);
            printf("   value:[string] %s\n", p ? p : "<null>");
         }
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
   }
   else {
      printf("%p :: line %d col %d, op=%c(%d)\n", root, root->line, root->col, root->op, root->op);
   }
   dumpvalue(root);

   printf("   label:'%s'\n", root->label ? root->label : "<nil>");

   printf("   left =%p\n", root->left);
   printf(" middle =%p\n", root->middle);
   printf("  right =%p\n", root->right);
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

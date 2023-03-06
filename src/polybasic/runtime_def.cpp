#include "eprintf.hpp"
#include "tree.hpp"
#include "polybasic.tab.hpp"
#include "runtime_def.hpp"
#include "dumptree.hpp"
#include "hash.hpp"

#define HASH_SIZE 65536
static Tree *defs[HASH_SIZE];

int is_def_defined(const char *p) {
   unsigned long h = hash(p);

   for (unsigned long i = 0; i < HASH_SIZE; i++) {
      unsigned long j = (i + h) % HASH_SIZE;
      if (defs[j] != NULL && !strcmp(p, V_AS_S(defs[j]->value))) {
         return 1;
      }
   }
   return 0;
}

int set_def(Tree *n) {
   unsigned long h = hash(V_AS_S(n->value));

   for (unsigned long i = 0; i < HASH_SIZE; i++) {
      unsigned long j = (i + h) % HASH_SIZE;
      if (defs[j] != NULL && !strcmp(V_AS_S(n->value), V_AS_S(defs[j]->value))) {
         return 0;
      }
      if (defs[j] == NULL) {
         defs[j] = n;
         return 1;
      }
   }
   return 0;
}

Tree *get_def(const char *p) {
   unsigned long h = hash(p);

   for (unsigned long i = 0; i < HASH_SIZE; i++) {
      unsigned long j = (i + h) % HASH_SIZE;
      if (defs[j] != NULL && !strcmp(p, V_AS_S(defs[j]->value))) {
         return defs[j];
      }
   }
   return NULL;
}

// lots of helper functions to detect cycles

static int paths_yet = 0;

class Path {
      int path[HASH_SIZE];
      int spot;
   public:
      Path();
      Path(const Path &other);
      void dump(void);
      void treedive(Tree *t);
      int add(int id);
};

Path::Path() {
   spot = 0;
}

Path::Path(const Path &other) {
   spot = other.spot;
   memcpy(path, other.path, sizeof(path));
}

void Path::dump(void) {
   if (!paths_yet) {
      paths_yet = 1;
      GURU;
      // test case cycle_def
      eprintf("{ERROR}: {DEFINITION CYCLE DISCOVERED}%n");
   }
   fprintf(stderr, "   ");
   for (int i = 0; i < spot; i++) {
      GURU;
      // test case cycle_def
      eprintf("❮%0❯ @%1:%2 ->%b",
         V_AS_S(defs[path[i]]->value),
         defs[path[i]]->line, defs[path[i]]->col);
   }
   GURU;
   // test case cycle_def
   eprintf("❮%0❯ @%1:%2%n",
      V_AS_S(defs[path[0]]->value),
      defs[path[0]]->line, defs[path[0]]->col);
}

void Path::treedive(Tree *t) {
   if (t) {
      if (t->op == YYEFAD) {
         for (int i = 0; i < HASH_SIZE; i++) {
            if (defs[i] && !strcmp(V_AS_S(defs[i]->value), V_AS_S(t->value))) {
               Path copy(*this);
               copy.add(i);
            }
         }
      }
      treedive(t->left);
      treedive(t->middle);
      treedive(t->right);
   }
}

int Path::add(int id) {
   if (spot) {
      if (spot && id == path[0]) {
         for (int i = 0; i < spot; i++) {
            if (path[i] < id) {
               return -1; // cycle, but we're not lowest
            }
         }
         dump();
         return 1; // cycle, and we're lowest
      }
      for (int i = 0; i < spot; i++) {
         if (path[i] == id) {
            return -1; // cycle, but doesn't start at path[0]
         }
      }
   }
   path[spot++] = id;
   treedive(defs[id]);
   return 0; // no cycle
}

void def_check_cycle(void) {
   paths_yet = 0;
   for (int i = 0; i < HASH_SIZE; i++) {
      if (defs[i]) {
         Path p;
         p.add(i);
      }
   }
   if (paths_yet) {
      exit(-1);
   }
}

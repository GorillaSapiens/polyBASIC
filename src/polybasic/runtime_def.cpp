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
      if (defs[j] != NULL && !strcmp(p, defs[j]->sval)) {
         return 1;
      }
   }
   return 0;
}

int set_def(Tree *n) {
   unsigned long h = hash(n->sval);

   for (unsigned long i = 0; i < HASH_SIZE; i++) {
      unsigned long j = (i + h) % HASH_SIZE;
      if (defs[j] != NULL && !strcmp(n->sval, defs[j]->sval)) {
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
      if (defs[j] != NULL && !strcmp(p, defs[j]->sval)) {
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
      eprintf("ERROR: DEFINITION CYCLE DISCOVERED\n");
   }
   fprintf(stderr, "   ");
   for (int i = 0; i < spot; i++) {
      GURU;
      eprintf("❮%0❯ at %1:%2 -> ",
         defs[path[i]]->sval, defs[path[i]]->line, defs[path[i]]->col);
   }
   GURU;
   eprintf("❮%0❯ at %1:%2\n",
      defs[path[0]]->sval, defs[path[0]]->line, defs[path[0]]->col);
}

void Path::treedive(Tree *t) {
   if (t) {
      if (t->op == YYDEFCALL) {
         for (int i = 0; i < HASH_SIZE; i++) {
            if (defs[i] && !strcmp(defs[i]->sval, t->sval)) {
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

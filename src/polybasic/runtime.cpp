#include <stdio.h>
#include <math.h>
#include <float.h>
#include <time.h>

#include "eprintf.hpp"
#include "tree.hpp"
#include "polybasic.tab.hpp"
#include "dumptree.hpp"
#include "runtime_lbls.hpp"
#include "runtime_for.hpp"
#include "runtime_def.hpp"
#include "runtime_vars.hpp"
#include "runtime_data.hpp"
#include "runtime.hpp"
#include "main.hpp"
#include "utf8utils.hpp"

static int64_t option_base = 0;
static int64_t option_upper = 10; // default upper array bound per ECMA-55

static void register_labels(Tree *root) {
   while (root) {
      if (root->label) {
         if (is_lbl_defined(root->label)) {
            Tree *prev = get_label(root->label);
            GURU;
            // test case multiple_integer_label multiple_string_label
            eprintf("{ERROR}: @%0:%1, {LABEL ALREADY DEFINED}, ❮%2❯ @%3:%4%n",
               root->line, root->col, root->label, prev->line, prev->col);
            exit(-1);
         }
         else {
            set_label(root);
         }
      }
      root = root->next;
   }
}

static void register_option_base(Tree *root) {
   while (root) {
      if (root->op == YYBASE) {
         // ECMA-55 allows only 0 or 1
         // if it ain't 0, it's a 1
         if (root->ival != 0) {
            option_base = 1;
            // and the first one wins,
            // subsequent ones lose
            return;
         }
      }
      root = root->next;
   }
}

static void register_arrays(Tree *root) {
   while (root) {
      if (root->op == YYDIM) {
         for (Tree *list = root->right; list; list = list->middle) {
            if (is_bound_defined(list->sval)) {
               const Varbound *vb = get_varbound(list->sval);
               GURU;
               // test case multiple_dim
               eprintf("{ERROR}: @%0:%1, {ARRAY ALREADY DEFINED} ❮%2❯ @%3%n",
                  list->line, list->col, list->sval, vb->line);
               exit(-1);
            }
            else {
               if (list->right) {
                  set_bound(list->sval, list->line, 2, list->left->ival, list->right->ival);
               }
               else {
                  set_bound(list->sval, list->line, 1, list->left->ival, 0);
               }
            }
         }
      }

      root = root->next;
   }
}

static void register_def(Tree *root) {
   while (root) {
      if (root->op == YYDEF && root->sval) {
         if (is_def_defined(root->sval)) {
            Tree *prev = get_def(root->sval);
            GURU;
            // test case multiple_def
            eprintf("{ERROR}: @%0:%1 {FUNCTION DEFINITION MULTIPLY DEFINED} ❮%2❯ @%3:%4%n",
               root->line, root->col, root->sval, prev->line, prev->col);
            exit(-1);
         }
         else {
            set_def(root);
         }
      }
      root = root->next;
   }
   def_check_cycle();
}

static void register_data(Tree *root) {
   while (root) {
      if (root->op == YYDATA) {
         for (Tree *data = root->right; data; data = data->middle) {
            switch (data->op) {
               case YYDOUBLE:
                  add_data(data->dval);
                  break;
               case YYINTEGER:
                  add_data(data->ival);
                  break;
               case YYRATIONAL:
                  add_data(data->rval);
                  break;
               case YYSTRING:
                  add_data(data->sval);
                  break;
            }
         }
      }
      root = root->next;
   }
}

void upgrade_to_number(Tree *p) {
   if (p->op == YYSTRING) {
      const char *s = p->sval;
      if (void_enabled && !strcasecmp(s, "void")) {
         p->op = YYVOID;
         p->valt = 'v';
         p->ival = 0;
      }
      else if (strchr((char *)s, '#') == s) {
         p->op = YYRATIONAL;
         p->valt = 'r';
         p->rval = new Rational(s);
      }
      else if (strchr((char *)s, '.') || strchr((char *)s, 'E')) {
         p->op = YYDOUBLE;
         p->valt = 'd';
         p->dval = atof(s);
      }
      else {
         p->op = YYINTEGER;
         p->valt = 'i';
         p->ival = atoll(s);
      }
      free((void *)s);
   }
}

void upgrade_to_rational(Tree *p) {
   if (p->op == YYINTEGER) {
      int64_t ival = p->ival;
      int8_t sign = 1;
      if (ival < 0) {
         sign = -1;
         ival = -ival;
      }
      p->op = YYRATIONAL;
      p->valt = 'r';
      p->rval = new Rational(sign, ival, 0, 1);
   }
   else if (p->op == YYDOUBLE) {
      p->op = YYRATIONAL;
      p->valt = 'r';
      p->rval = new Rational(p->dval);
   }
}

void upgrade_to_double(Tree *p) {
   if (p->op == YYINTEGER) {
      int64_t ival = p->ival;
      p->op = YYDOUBLE;
      p->valt = 'd';
      p->dval = (double) ival;
   }
   else if (p->op == YYRATIONAL) {
      Rational *deleteme = p->rval;
      double dval = (double)(*(p->rval));
      p->op = YYDOUBLE;
      p->valt = 'd';
      p->dval = dval;
      delete deleteme;
   }
}

void upgrade_to_integer(Tree *p) {
   if (p->op == YYDOUBLE) {
      p->op = YYINTEGER;
      p->valt = 'i';
      p->ival = (int64_t) floor(p->dval);
   }
   else if (p->op == YYRATIONAL) {
      Rational *deleteme = p->rval;
      double dval = (double)(*(p->rval));
      p->op = YYINTEGER;
      p->valt = 'i';
      p->ival = (int64_t) floor(dval);
      delete deleteme;
   }
}

void upgrade_to_string(Tree *p) {
   if (p->op != YYSTRING) {
      char buf[1024];
      if (p->op == YYDOUBLE) {
         snprintf(buf, sizeof(buf), "%g", p->dval);
         if (!strchr(buf, '.')) {
            strcat(buf, ".0");
         }
         p->op = YYSTRING;
         p->sval = strdup(buf);
      }
      else if (p->op == YYINTEGER) {
         snprintf(buf, sizeof(buf), "%ld", p->ival);
         p->op = YYSTRING;
         p->sval = strdup(buf);
      }
      else if (p->op == YYRATIONAL) {
         Rational *deleteme = p->rval;
         deleteme->shortprint(buf, sizeof(buf));
         p->op = YYSTRING;
         p->sval = strdup(buf);
         delete deleteme;
      }
   }
}

int paramcount(Tree *tree) {
   int ret = 0;
   while (tree != NULL) {
      tree = tree->middle;
      ret++;
   }
   return ret;
}

#if 0
Tree *deep_copy_defcall(Tree *defcall, Tree *params, Tree *values) {
   Tree *def = get_def(defcall->sval);
   if (!def) {
      GURU;
      // test case unrecognized_defcall
      eprintf("{ERROR}: @%0:%1, {UNRECOGNIZED FUNCTION DEFINITION} ❮%2❯%n",
         defcall->line, defcall->col, defcall->sval);
      exit(-1);
   }
   int defcount = paramcount(def->left);
   int callcount = paramcount(defcall->left);
   if (defcount != callcount) {
      GURU;
      // test case param_mismatch1 param_mismatch2
      eprintf("{ERROR}: @%0:%1, {FUNCTION DEFINITION PARAMETER MISMATCH} ❮%2❯ %3<>%4%n",
         defcall->line, defcall->col, defcall->sval, defcount, callcount);
      exit(-1);
   }

   // TODO FIX so much leaky memory here...

   // evaluate parameters
   Tree *head = NULL;
   Tree *tail = NULL;
   for (Tree *mid = defcall->left; mid; mid = mid->middle) {
      Tree *tmp = evaluate(deep_copy(mid, params, values));
      if (!head) {
         head = tail = tmp;
      }
      else {
         tail->middle = tmp;
         tail = tmp;
      }
   }

   Tree *ret = evaluate(deep_copy(def->right, def->left, head));
   if (defcall->middle) { ret->middle = deep_copy(defcall->middle); }
   return ret;
}
#endif

// make a deep copy
Tree *deep_copy(Tree *subtree) {
   Tree *copy = (Tree *) malloc(sizeof(Tree));
   memcpy(copy, subtree, sizeof(Tree));

   // don't copy labels, we'd just have to free them later

   if (subtree->left) { copy->left = deep_copy(subtree->left); }
   if (subtree->middle) { copy->middle = deep_copy(subtree->middle); }
   if (subtree->right) { copy->right = deep_copy(subtree->right); }

   if (copy->valt == 's') {
      copy->sval = strdup(subtree->sval);
   }
   else if (copy->valt == 'r') {
      copy->rval = new Rational(*(subtree->rval));
   }

   copy->next = NULL;

   return copy;
}

#if 0
   else if (copy->op == YYARRAYREF) {
      if (copy->left) {
         copy->left = evaluate(copy->left);
         if (copy->left->op == YYSTRING) {
            upgrade_to_number(copy->left);
         }
         if (copy->left->op == YYDOUBLE) {
            copy->left->ival = (int64_t)floor(copy->left->dval);
            copy->left->op = YYINTEGER;
         }
         else if (copy->left->op == YYINTEGER) {
            copy->left->ival = (int64_t)floor((double)copy->left->ival);
         }
         else if (copy->left->op == YYRATIONAL) {
            Rational *deleteme = copy->left->rval;
            copy->left->ival = (int64_t) copy->left->rval->floor();
            copy->left->op = YYINTEGER;
            delete deleteme;
         }
      }
      if (copy->right) {
         copy->right = evaluate(copy->right);
         if (copy->right->op == YYSTRING) {
            upgrade_to_number(copy->right);
         }
         if (copy->right->op == YYDOUBLE) {
            copy->right->ival = (int64_t)floor(copy->right->dval);
            copy->right->op = YYINTEGER;
         }
         else if (copy->right->op == YYINTEGER) {
            copy->right->ival = (int64_t)floor((double)copy->right->ival);
         }
         else if (copy->right->op == YYRATIONAL) {
            Rational *deleteme = copy->right->rval;
            copy->right->ival = (int64_t) copy->right->rval->floor();
            copy->right->op = YYINTEGER;
            delete deleteme;
         }
      }
   }
#endif

#if 0
   if (copy->op == YYVARNAME || copy->op == YYARRAYREF) {
      char varname[1024];
      if (copy->op == YYVARNAME) {
         sprintf(varname, "%s", subtree->sval);
      }
      else { // YYARRAYREF
         if (copy->right) {
            // TODO FIX bounds check these based on DIM?
            sprintf(varname, "%s(%ld,%ld)", subtree->sval, copy->left->ival, copy->right->ival);
            free(copy->left);
            copy->left = NULL;
            free(copy->right);
            copy->right = NULL;
         }
         else {
            // TODO FIX bounds check these based on DIM?
            sprintf(varname, "%s(%ld)", subtree->sval, copy->left->ival);
            free(copy->left);
            copy->left = NULL;
         }
      }

      int found = 0;
      if (params != NULL && values != NULL) {
         Tree *p = params;
         Tree *v = values;

         while (p) {
            if (!strcmp(p->sval, varname)) {
               found = 1;
               if (v->op == YYDOUBLE) {
                  copy->op = YYDOUBLE;
                  copy->dval = v->dval;
               }
               else if (v->op == YYINTEGER) {
                  copy->op = YYINTEGER;
                  copy->ival = v->ival;
               }
               else if (v->op == YYRATIONAL) {
                  copy->op = YYRATIONAL;
                  copy->rval = new Rational(*(v->rval));
               }
               else if (v->op == YYSTRING) {
                  copy->op = YYSTRING;
                  copy->sval = strdup(v->sval);
               }
               break;
            }
            p = p->middle;
            v = v->middle;
         }
      }
      if (!found) {
         const Val *val = get_value(varname);
         if (!val) {
            GURU;
            // no test case
            eprintf("{ERROR}: @%0:%1, {VARIABLE HAS NO VALUE} ❮%2❯%n",
                  copy->line, copy->col, varname);
            exit(-1);
         }
         else {
            if (val->typ == 'd') {
               copy->op = YYDOUBLE;
               copy->dval = val->dval;
            }
            else if (val->typ == 'i') {
               copy->op = YYINTEGER;
               copy->ival = val->ival;
            }
            else if (val->typ == 'r') {
               copy->op = YYRATIONAL;
               copy->rval = new Rational(*(val->rval));
            }
            else if (val->typ == 's') {
               copy->op = YYSTRING;
               copy->sval = strdup(val->sval);
            }
         }
      }
   }
#endif

#define BUILTINFUNC(name, args) void builtin_ ## name(Tree *p)

BUILTINFUNC(ABS, 1) {
   Tree *freeme = p->right;

   upgrade_to_number(p->right);

   if (p->right->op == YYDOUBLE) {
      p->right->dval = fabs(p->right->dval);
   }
   else if (p->right->op == YYINTEGER) {
      p->right->ival = llabs(p->right->ival);
   }
   else if (p->right->op == YYRATIONAL) {
      *(p->right->rval) = p->right->rval->abs();
   }

   Tree *middle = p->middle;
   memcpy(p, p->right, sizeof(Tree));
   p->middle = middle;

   free(freeme);
}

BUILTINFUNC(ATN, 1) {
   Tree *freeme = p->right;
   upgrade_to_number(p->right);
   upgrade_to_double(p->right);
   p->right->dval = atan(p->right->dval);

   Tree *middle = p->middle;
   memcpy(p, p->right, sizeof(Tree));
   p->middle = middle;

   free(freeme);
}

BUILTINFUNC(CHR, 1) {
   Tree *freeme = p->right;
   upgrade_to_number(p->right);
   upgrade_to_integer(p->right);

   p->right->op = YYSTRING;
   p->right->sval = strdup(int2utf8(p->right->ival));

   Tree *middle = p->middle;
   memcpy(p, p->right, sizeof(Tree));
   p->middle = middle;

   free(freeme);
}

BUILTINFUNC(COS, 1) {
   Tree *freeme = p->right;
   upgrade_to_number(p->right);
   upgrade_to_double(p->right);
   p->right->dval = cos(p->right->dval);

   Tree *middle = p->middle;
   memcpy(p, p->right, sizeof(Tree));
   p->middle = middle;

   free(freeme);
}

BUILTINFUNC(DBL, 1) {
   Tree *freeme = p->right;
   upgrade_to_number(p->right);
   upgrade_to_double(p->right);

   Tree *middle = p->middle;
   memcpy(p, p->right, sizeof(Tree));
   p->middle = middle;

   free(freeme);
}

BUILTINFUNC(EXP, 1) {
   Tree *freeme = p->right;
   upgrade_to_number(p->right);
   upgrade_to_double(p->right);
   p->right->dval = pow(M_E,p->right->dval);

   Tree *middle = p->middle;
   memcpy(p, p->right, sizeof(Tree));
   p->middle = middle;

   free(freeme);
}

BUILTINFUNC(INT, 1) {
   Tree *freeme = p->right;
   upgrade_to_number(p->right);
   upgrade_to_integer(p->right);

   Tree *middle = p->middle;
   memcpy(p, p->right, sizeof(Tree));
   p->middle = middle;

   free(freeme);
}

BUILTINFUNC(RAT, 1) {
   Tree *freeme = p->right;
   upgrade_to_number(p->right);
   upgrade_to_rational(p->right);

   Tree *middle = p->middle;
   memcpy(p, p->right, sizeof(Tree));
   p->middle = middle;

   free(freeme);
}

BUILTINFUNC(STR, 1) {
   Tree *freeme = p->right;
   upgrade_to_string(p->right);

   Tree *middle = p->middle;
   memcpy(p, p->right, sizeof(Tree));
   p->middle = middle;

   free(freeme);
}

BUILTINFUNC(LOG, 1) {
   Tree *freeme = p->right;
   upgrade_to_number(p->right);
   upgrade_to_double(p->right);
   p->right->dval = log(p->right->dval);

   Tree *middle = p->middle;
   memcpy(p, p->right, sizeof(Tree));
   p->middle = middle;

   free(freeme);
}

BUILTINFUNC(RND, 1) {
   Tree *freeme = p->right;
   upgrade_to_number(p->right);
   upgrade_to_double(p->right);
   p->right->dval = (double)rand()/(double)(RAND_MAX/(p->right->dval));

   Tree *middle = p->middle;
   memcpy(p, p->right, sizeof(Tree));
   p->middle = middle;

   free(freeme);
}

BUILTINFUNC(RANDOMIZE, 0) {
   time_t t = time(NULL);
   srand(t);
   p->op = YYINTEGER;
   p->ival = t;
}

BUILTINFUNC(SGN, 1) {
   Tree *freeme = p->right;
   upgrade_to_number(p->right);
   upgrade_to_integer(p->right);
   if (p->right->ival < 0) {
      p->right->ival = -1;
   }
   else if (p->right->ival > 0) {
      p->right->ival = 1;
   }
   else {
      p->right->ival = 0;
   }

   Tree *middle = p->middle;
   memcpy(p, p->right, sizeof(Tree));
   p->middle = middle;

   free(freeme);
}

BUILTINFUNC(SIN, 1) {
   Tree *freeme = p->right;
   upgrade_to_number(p->right);
   upgrade_to_double(p->right);
   p->right->dval = sin(p->right->dval);

   Tree *middle = p->middle;
   memcpy(p, p->right, sizeof(Tree));
   p->middle = middle;

   free(freeme);
}

BUILTINFUNC(SQR, 1) {
   Tree *freeme = p->right;
   upgrade_to_number(p->right);
   upgrade_to_double(p->right);
   p->right->dval = sqrt(p->right->dval);

   Tree *middle = p->middle;
   memcpy(p, p->right, sizeof(Tree));
   p->middle = middle;

   free(freeme);
}

BUILTINFUNC(TAB, 1) {
   Tree *freeme = p->right;
   upgrade_to_number(p->right);
   upgrade_to_integer(p->right);

   char buffer[128];
   sprintf(buffer, "\x1b[%ldG", p->right->ival);
   p->right->op = YYSTRING;
   p->right->sval = strdup(buffer);

   Tree *middle = p->middle;
   memcpy(p, p->right, sizeof(Tree));
   p->middle = middle;

   free(freeme);
}

BUILTINFUNC(TAN, 1) {
   Tree *freeme = p->right;
   upgrade_to_number(p->right);
   upgrade_to_double(p->right);
   p->right->dval = tan(p->right->dval);

   Tree *middle = p->middle;
   memcpy(p, p->right, sizeof(Tree));
   p->middle = middle;

   free(freeme);
}

typedef void (*BFptr)(Tree *);
typedef struct Builtin {
   const char *name;
   int args;
   BFptr fptr;
} Builtin;

Builtin builtins[] = {
#include "builtins.hpp"
   { NULL, 0, NULL }
};

Builtin *get_builtin(const char *name) {
   const char *translation = has_tuple(name);

   if (!translation) {
      return NULL;
   }

   for (int i = 0; builtins[i].name; i++) {
      if (!utf8casecmp(builtins[i].name, translation)) {
         return (builtins + i);
      }
   }

   return NULL; // shouldn't happen?  but could?
}

char *get_var_array_name(Tree *p) {
   Varbound *vb = (Varbound *) get_varbound(p->sval);
   int count = paramcount(p->right);

   if (!vb) {
      set_bound(p->sval, p->line, count, 10, 10);
      vb = (Varbound *) get_varbound(p->sval);
   }

   if (vb) {
      if (vb->dimensions == 0 && count > 0) {
         GURU;
         // test case varbounds3 vardim3
         eprintf("{ERROR}: @%0:%1, {VARIABLE USED AS ARRAY} ❮%2❯ @%3%n",
               p->line, p->col, p->sval, vb->line);
         exit(-1);
      }
      if (count == 0 && vb->dimensions > 0) {
         GURU;
         // test case vardim1 vardim2
         eprintf("{ERROR}: @%0:%1, {ARRAY USED AS VARIABLE} ❮%2❯ @%3%n",
               p->line, p->col, p->sval, vb->line);
         exit(-1);
      }
      if (count != vb->dimensions) {
         GURU;
         // test case varbounds4 vardim4
         eprintf("{ERROR}: @%0:%1, {ARRAY INDEX SIZE MISMATCH} ❮%2❯ DIM%3 @%4%n",
               p->line, p->col, p->sval, vb->dimensions, vb->line);
         exit(-1);
      }
      if (vb->dimensions == 1 && (p->right->ival < option_base || p->right->ival > vb->upper1)) {
         GURU;
         // test case varbounds
         eprintf("{ERROR}: @%0:%1, {ARRAY INDEX OUT OF BOUNDS} ❮%2❯(%5) ❮%2❯(%3..%4) @%6%n",
               p->line, p->col, p->sval, option_base, vb->upper1, p->right->ival, vb->line);
         exit(-1);
      }
      if (vb->dimensions == 2 &&
            (p->right->ival < option_base || p->right->ival > vb->upper1 ||
             p->right->middle->ival < option_base || p->right->middle->ival > vb->upper2)) {
         GURU;
         // test case varbounds1 varbounds2
         eprintf("{ERROR}: @%0:%1, {ARRAY INDEX OUT OF BOUNDS} ❮%2❯(%6,%7) ❮%2❯(%3..%4,%3..%5) @%8%n",
               p->line, p->col, p->sval, option_base, vb->upper1, vb->upper2,
               p->right->ival, p->right->middle->ival, vb->line);
         exit(-1);
      }
   }

   if (p->right) { // an array
      int n = 0;
      char buf[4096];
      sprintf(buf, "%s(", p->sval);

      for (Tree *tree = p->right; tree; tree = tree->middle) {
         upgrade_to_number(tree);
         upgrade_to_integer(tree);
         if (tree->op != YYINTEGER) {
            GURU;
            // test case voidarraysubscript
            eprintf("{ERROR}: @%0:%1, {ARRAY SUBSCRIPT NOT A NUMBER} ❮%2❯(%3) ❮%4❯%n",
                  p->line, p->col, p->sval, n, eop2string(tree->op));
            exit(-1);
         }
         if (tree->middle) {
            sprintf(buf + strlen(buf), "%ld,", tree->ival);
         }
         else {
            sprintf(buf + strlen(buf), "%ld)", tree->ival);
         }
         n++;
      }

      return strdup(buf);
   }
   else { // a variable
      return strdup(p->sval);
   }
}

Tree *get_param(const char *s, Tree *params, Tree *vals) {
   while (params && vals) {
      if (!strcmp(s, params->sval)) {
         return vals;
      }
      params = params->middle;
      vals = vals->middle;
   }
   return NULL;
}

Tree *evaluate(Tree *p, Tree *params = NULL, Tree *vals = NULL) {
   Tree *tmp;

   if (p->left) {
      p->left = evaluate(p->left, params, vals);
   }
   if (p->middle) {
      p->middle = evaluate(p->middle, params, vals);
   }
   if (p->right) {
      p->right = evaluate(p->right, params, vals);
   }

   if (p->op == YYDOUBLE) {
      return p;
   }
   if (p->op == YYINTEGER) {
      return p;
   }
   if (p->op == YYRATIONAL) {
      return p;
   }
   if (p->op == YYSTRING) {
      return p;
   }

   if (p->op == YYEFAD) {
      Builtin *builtin = get_builtin(p->sval);
      if (builtin) { // it's a builtin function
         int count = 0;
         for (Tree *tree = p->right; tree; tree = tree->middle) {
            count++;
         }
         if (count != builtin->args) {
            GURU;
            // test case builtinparamcount
            eprintf("{ERROR}: @%0:%1, {INCORRECT NUMBER OF PARAMETERS} ❮%2❯ %3<>%4%n",
               p->line, p->col, has_tuple(p->sval), count, builtin->args);
            exit(-1);
         }
         builtin->fptr(p);
      }
      else if (is_def_defined(p->sval)) {
         Tree *deftree = get_def(p->sval);

         int defcount = paramcount(deftree->left);
         int callcount = paramcount(p->right);

         if (defcount != callcount) {
            GURU;
            // test case param_mismatch1 param_mismatch2
            eprintf("{ERROR}: @%0:%1, {FUNCTION DEFINITION PARAMETER MISMATCH} ❮%2❯ %3<>%4%n",
               p->line, p->col, p->sval, defcount, callcount);
            exit(-1);
         }

         Tree *expression = deep_copy(deftree->right);
         Tree *val = evaluate(expression, deftree->left, p->right);
         // TODO FIX do we need to free anything up???
         p->op = val->op;
         p->valt = val->valt;
         switch (val->op) {
            case YYDOUBLE:
               p->dval = val->dval;
               break;
            case YYINTEGER:
               p->ival = val->ival;
               break;
            case YYRATIONAL:
               p->rval = new Rational(*(val->rval));
               break;
            case YYSTRING:
               p->sval = strdup(val->sval);
               break;
            default:
               GURU;
               // test case defreturnsvoid
               eprintf("{ERROR}: @%0:%1, {UNKNOWN OP IN PARAMETER SUBSTITUTION} ❮%2❯%n",
                  p->line, p->col, eop2string(val->op));
               exit(-1);
               break;
         }
         // TODO FIX: do we need to null or free p->left or p->right???
      }
      else if (params && (tmp = /*assignment */ get_param(p->sval, params, vals))) {
         // parameter substitution from a defcall
         Tree *val = tmp;
         // TODO FIX do we need to free anything up???
         p->op = val->op;
         p->valt = val->valt;
         switch (val->op) {
            case YYDOUBLE:
               p->dval = val->dval;
               break;
            case YYINTEGER:
               p->ival = val->ival;
               break;
            case YYRATIONAL:
               p->rval = new Rational(*(val->rval));
               break;
            case YYSTRING:
               p->sval = strdup(val->sval);
               break;
            default:
               GURU;
               // test case defgivenvoid
               eprintf("{ERROR}: @%0:%1, {UNKNOWN OP IN PARAMETER SUBSTITUTION} ❮%2❯%n",
                  p->line, p->col, eop2string(val->op));
               exit(-1);
               break;
         }
         // TODO FIX: do we need to null or free p->left or p->right???
      }
      else { // array or variable
         char *s = get_var_array_name(p);
         const Val *val = get_value(s);
         if (val) {
            if (p->right) {
               // TODO FIX // free p->right?!?!?
               p->right = NULL;
            }

            switch (val->typ) {
               case 'd':
                  p->op = YYDOUBLE;
                  p->valt = 'd';
                  p->dval = val->dval;
                  break;
               case 'i':
                  p->op = YYINTEGER;
                  p->valt = 'i';
                  p->ival = val->ival;
                  break;
               case 'r':
                  p->op = YYRATIONAL;
                  p->valt = 'r';
                  p->rval = new Rational(*(val->rval));
                  break;
               case 's':
                  p->op = YYSTRING;
                  p->valt = 's';
                  p->sval = strdup(val->sval);
                  break;
            }
         }
         else {
            GURU;
            // test case no_value
            eprintf("{ERROR}: @%0:%1, {VARIABLE OR ARRAY HAS NO VALUE} ❮%2❯%n",
               p->line, p->col, s);
            exit(-1);
         }
         free(s);
      }
   }

   if (p->op == YYLVAL) {
      Builtin *builtin = get_builtin(p->sval);
      if (builtin) { // it's a builtin function
         GURU;
         // test case assigntobuiltin
         eprintf("{ERROR}: @%0:%1, {CANNOT ASSIGN TO FUNCTION} ❮%2❯%n",
            p->line, p->col, has_tuple(p->sval));
         exit(-1);
      }
      else if (is_def_defined(p->sval)) {
         GURU;
         // test case assigntodef
         eprintf("{ERROR}: @%0:%1, {CANNOT ASSIGN TO DEFINITION} ❮%2❯%n",
            p->line, p->col, p->sval);
         exit(-1);
      }
      else { // variable or array
         char *s = get_var_array_name(p);

         p->valt = 's';
         p->sval = s;
         // TODO FIX // free p->right?!?!?
         p->right = NULL;
      }
   }

#if 0
FNORD
   else if (p->op == YYTAB) {
   }
#endif
   if (strchr("+-*/^&", p->op)) {
      if (p->left && p->right ) {
         if ((p->left->op != p->right->op) ||
               (p->left->op == YYSTRING && p->op != '&')) {
            // in a mismatch, try to make strings into numbers
            if (p->left->op == YYSTRING) {
               upgrade_to_number(p->left);
            }
            if (p->right->op == YYSTRING) {
               upgrade_to_number(p->right);
            }

            if (p->left->op == YYRATIONAL && p->right->op == YYINTEGER) {
               upgrade_to_rational(p->right);
            }
            else if (p->left->op == YYINTEGER && p->right->op == YYRATIONAL) {
               upgrade_to_rational(p->left);
            }

            if (p->left->op == YYRATIONAL && p->right->op == YYDOUBLE) {
               upgrade_to_double(p->left);
            }
            else if (p->left->op == YYDOUBLE && p->right->op == YYRATIONAL) {
               upgrade_to_double(p->right);
            }

            if (p->left->op == YYINTEGER && p->right->op == YYDOUBLE) {
               upgrade_to_double(p->left);
            }
            else if (p->left->op == YYDOUBLE && p->right->op == YYINTEGER) {
               upgrade_to_double(p->right);
            }
         }

         if (p->left->op == p->right->op) {
            switch(p->left->op) {
               case YYDOUBLE:
                  switch(p->op) {
                     case '+':
                        p->dval = p->left->dval + p->right->dval;
                        break;
                     case '-':
                        p->dval = p->left->dval - p->right->dval;
                        break;
                     case '*':
                        p->dval = p->left->dval * p->right->dval;
                        break;
                     case '/':
                        p->dval = p->left->dval / p->right->dval;
                        break;
                     case '^':
                        p->dval = pow(p->left->dval,p->right->dval);
                        break;
                     default:
                        GURU;
                        // test case double_amp
                        eprintf("{ERROR}: @%0:%1, {UNRECOGNIZED DOUBLE MATH OPERATION} ❮%2❯%n",
                              p->line, p->col, eop2string(p->op));
                        exit(-1);
                        break;
                  }
                  p->op = YYDOUBLE;
                  free(p->left);
                  p->left = NULL;
                  free(p->right);
                  p->right = NULL;
                  break;
               case YYINTEGER:
                  switch(p->op) {
                     case '+':
                        p->ival = p->left->ival + p->right->ival;
                        break;
                     case '-':
                        p->ival = p->left->ival - p->right->ival;
                        break;
                     case '*':
                        p->ival = p->left->ival * p->right->ival;
                        break;
                     case '/':
                        p->ival = p->left->ival / p->right->ival;
                        break;
                     case '^':
                        p->ival = (int64_t) pow(p->left->ival,p->right->ival);
                        break;
                     default:
                        GURU;
                        // test case integer_amp
                        eprintf("{ERROR}: @%0:%1, {UNRECOGNIZED INTEGER MATH OPERATION} ❮%2❯%n",
                              p->line, p->col, eop2string(p->op));
                        exit(-1);
                        break;
                  }
                  p->op = YYINTEGER;
                  free(p->left);
                  p->left = NULL;
                  free(p->right);
                  p->right = NULL;
                  break;
               case YYRATIONAL:
                  switch(p->op) {
                     case '+':
                        p->rval = new Rational (*(p->left->rval) + *(p->right->rval));
                        p->op = YYRATIONAL;
                        break;
                     case '-':
                        p->rval = new Rational (*(p->left->rval) - *(p->right->rval));
                        p->op = YYRATIONAL;
                        break;
                     case '*':
                        p->rval = new Rational (*(p->left->rval) * *(p->right->rval));
                        p->op = YYRATIONAL;
                        break;
                     case '/':
                        p->rval = new Rational (*(p->left->rval) / *(p->right->rval));
                        p->op = YYRATIONAL;
                        break;
                     case '^':
                        p->dval = pow((double)(*(p->left->rval)), (double) (*(p->right->rval)));
                        p->op = YYDOUBLE;
                        break;
                     default:
                        GURU;
                        // test case rational_amp
                        eprintf("{ERROR}: @%0:%1, {UNRECOGNIZED RATIONAL MATH OPERATION} ❮%2❯%n",
                              p->line, p->col, eop2string(p->op));
                        exit(-1);
                        break;
                  }
                  delete p->left->rval;
                  free(p->left);
                  p->left = NULL;
                  delete p->right->rval;
                  free(p->right);
                  p->right = NULL;
                  break;
               case YYSTRING:
                  switch(p->op) {
                     case '&':
                        p->valt = 's';
                        p->sval = (char *) malloc(strlen(p->left->sval) + strlen(p->right->sval) + 1);
                        sprintf((char *) p->sval, "%s%s", p->left->sval, p->right->sval);
                        p->op = YYSTRING;
                        break;
                     default:
                        GURU;
                        // no test case, strings are converted to numbers
                        eprintf("{ERROR}: @%0:%1, {STRING MATH LOGIC ERROR}%n", p->line, p->col);
                        exit(-1);
                        break;
                  }
                  free((void *)p->left->sval);
                  free((void *)p->left);
                  p->left = NULL;
                  free((void *)p->right->sval);
                  free((void *)p->right);
                  p->right = NULL;
                  break;
               default:
                  GURU;
                  // test case voidmath2 badstringmath
                  eprintf("{ERROR}: @%0:%1, {UNRECOGNIZED MATH TYPE} ❮%2❯%n",
                        p->line, p->col, eop2string(p->left->op));
                  exit(-1);
                  break;
            }
         }
         else {
            GURU;
            // test case voidmath
            eprintf("{ERROR}: @%0:%1, {OPERAND MISMATCH} ❮%2❯ ❮%3❯%n",
               p->line, p->col,
               eop2string(p->left ? p->left->op : -1),
               eop2string(p->right ? p->right->op : -1));
            exit(-1);
         }
      }
      else if (!p->left && p->right && p->op == '-') {
         switch (p->right->op) {
            case YYDOUBLE:
               p->dval = -(p->right->dval);
               p->op = YYDOUBLE;
               free(p->right);
               p->right = NULL;
               break;
            case YYINTEGER:
               p->ival = -(p->right->ival);
               p->op = YYINTEGER;
               free(p->right);
               p->right = NULL;
               break;
            case YYRATIONAL:
               {
                  Rational *deleteme = p->right->rval;
                  p->rval = new Rational(-(*p->right->rval));
                  p->op = YYRATIONAL;
                  delete deleteme;
                  free(p->right);
                  p->right = NULL;
               }
               break;
            case YYSTRING:
            default:
               GURU;
               // test case voidnegation stringnegation
               eprintf("{ERROR}: @%0:%1, {OPERAND MISMATCH} ❮%2❯ ❮%3❯%n",
                  p->line, p->col,
                  eop2string(p->op),
                  eop2string(p->right ? p->right->op : -1));
               exit(-1);
               break;
         }
      }
      else if (!p->left && p->right && p->op == '+') {
         switch (p->right->op) {
            case YYDOUBLE:
            case YYINTEGER:
            case YYRATIONAL:
               {
                  Tree *right = p->right;
                  memcpy(p, p->right, sizeof(Tree));
                  free(right);
               }
               break;
            case YYSTRING:
            default:
               GURU;
               // test case voidpositive stringpositive
               eprintf("{ERROR}: @%0:%1, {OPERAND MISMATCH} ❮%2❯ ❮%3❯%n",
                  p->line, p->col,
                  eop2string(p->op),
                  eop2string(p->right ? p->right->op : -1));
               exit(-1);
               break;
         }
      }
   }

   return p;
}

#define OP2NUM(x) ((((x)[0]) << 8) | ((x)[1]))

bool is_double_relation_true(Tree *left, const char *op, Tree *right) {
   switch(OP2NUM(op)) {
      case OP2NUM("="):
         return left->dval == right->dval;
         break;
      case OP2NUM("<>"):
         return left->dval != right->dval;
         break;
      case OP2NUM(">="):
         return left->dval >= right->dval;
         break;
      case OP2NUM("<="):
         return left->dval <= right->dval;
         break;
      case OP2NUM(">"):
         return left->dval > right->dval;
         break;
      case OP2NUM("<"):
         return left->dval < right->dval;
         break;
   }
   return false;
}

bool is_integer_relation_true(Tree *left, const char *op, Tree *right) {
   switch(OP2NUM(op)) {
      case OP2NUM("="):
         return left->ival == right->ival;
         break;
      case OP2NUM("<>"):
         return left->ival != right->ival;
         break;
      case OP2NUM(">="):
         return left->ival >= right->ival;
         break;
      case OP2NUM("<="):
         return left->ival <= right->ival;
         break;
      case OP2NUM(">"):
         return left->ival > right->ival;
         break;
      case OP2NUM("<"):
         return left->ival < right->ival;
         break;
   }
   return false;
}

bool is_rational_relation_true(Tree *left, const char *op, Tree *right) {
   switch(OP2NUM(op)) {
      case OP2NUM("="):
         return *(left->rval) == *(right->rval);
         break;
      case OP2NUM("<>"):
         return *(left->rval) != *(right->rval);
         break;
      case OP2NUM(">="):
         return *(left->rval) >= *(right->rval);
         break;
      case OP2NUM("<="):
         return *(left->rval) <= *(right->rval);
         break;
      case OP2NUM(">"):
         return *(left->rval) > *(right->rval);
         break;
      case OP2NUM("<"):
         return *(left->rval) < *(right->rval);
         break;
   }
   return false;
}

bool is_string_relation_true(Tree *left, const char *op, Tree *right) {
   int result = strcmp(left->sval, right->sval);
   switch(OP2NUM(op)) {
      case OP2NUM("="):
         return result == 0;
         break;
      case OP2NUM("<>"):
         return result != 0;
         break;
      case OP2NUM(">="):
         return result >= 0;
         break;
      case OP2NUM("<="):
         return result <= 0;
         break;
      case OP2NUM(">"):
         return result > 0;
         break;
      case OP2NUM("<"):
         return result < 0;
         break;
   }
   return false;
}

bool is_relation_true(Tree *left, const char *op, Tree *right) {
   // assumes left and right are the same type!
   switch (left->op) {
      case YYDOUBLE:
         return is_double_relation_true(left, op, right);
         break;
      case YYINTEGER:
         return is_integer_relation_true(left, op, right);
         break;
      case YYRATIONAL:
         return is_rational_relation_true(left, op, right);
         break;
      case YYSTRING:
         return is_string_relation_true(left, op, right);
         break;
   }
   return false;
}

Val convert_to_value(const char *s) {
   Val value;
   int has_noninteger = 0;
   int has_nonrational = 0;
   int has_nondouble = 0;

   for (const char *p = s; *p; p++) {
      if (*p != '+' && *p != '-' && (*p < '0' || *p > '9')) {
         has_noninteger++;
      }
      if (*p != '#' && *p != '\'' && *p != '/' && *p != '+' && *p != '-' && (*p < '0' || *p > '9')) {
         has_nonrational++;
      }
      if (*p != '.' && *p != 'E' && *p != '+' && *p != '-' && (*p < '0' || *p > '9')) {
         has_nondouble++;
      }
   }
   if (has_noninteger && has_nonrational && has_nondouble) {
      value.typ = 's';
      value.sval = strdup(s);
   }
   else if (!has_noninteger) {
      value.typ = 'i';
      value.ival = atol(s);
   }
   else if (!has_nondouble) {
      value.typ = 'd';
      value.dval = atof(s);
   }
   else if (!has_nonrational) {
      value.typ = 'r';
      value.rval = new Rational(s);
   }
   else {
      GURU;
      // no test case, conversion always yeilds something
      eprintf("{ERROR}: {UNRECOGNIZED INPUT} ❮%0❯%n", s);
      exit(-1);
   }
   return value;
}

#define GOSUB_STACKSIZE 1024
void run(Tree *p) {
   Tree *gosub_stack[GOSUB_STACKSIZE];
   int gosub_spot = 0;

   while (p) {
      Tree *np = p->next;
      switch (p->op) {
         case YYASSIGN:
            {
               Tree *lvalue = evaluate(deep_copy(p->left));
               Tree *result = evaluate(deep_copy(p->right));

               const char *varname = lvalue->sval;
               set_value(varname, result);

               free((void *)lvalue);
               free((void *)result);
            }
            break;
         case YYPRINT:
            {
               Tree *result = evaluate(deep_copy(p));
               for (Tree *mid = result->middle; mid; mid = mid->middle) {
                  switch (mid->op) {
                     case YYDOUBLE:
                        {
                           char buf[1024];
                           sprintf(buf, "%g", mid->dval);
                           if (!strchr(buf, '.')) {
                              strcat(buf, ".0");
                           }
                           printf("%s", buf);

                           // other unsatisfactory answers:
                           //printf("%f", mid->dval);
                           //printf("%g", mid->dval);
                           //printf("%.*e ", DBL_DECIMAL_DIG, mid->dval);
                        }
                        break;
                     case YYINTEGER:
                        printf("%li", mid->ival);
                        break;
                     case YYRATIONAL:
                        {
                           char buf[1024];
                           mid->rval->shortprint(buf, sizeof(buf));
                           printf("%s", buf);
                        }
                        break;
                     case YYSTRING:
                        printf("%s", mid->sval);
                        break;
                     default:
                        GURU;
                        // test case voidprint
                        eprintf("{ERROR}: @%0:%1, {UNRECOGNIZED OP IN PRINT} ❮%2❯%n",
                           p->line, p->col, eop2string(mid->op));
                        exit(-1);
                        break;
                  }
                  if (mid->middle) {
                     printf(" ");
                  }
               }
               printf("\n");
            }
            break;
         case YYFOR:
            {
               set_for(p);
               Tree *result = evaluate(deep_copy(p->left));
               set_value(p->sval, result);
            }
            break;
         case YYNEXT:
            {
               Tree *onp = np;
               Tree *fore = get_for(p->sval, false);
               if (!fore) {
                  GURU;
                  // test case unrecognext
                  eprintf("{ERROR}: @%0:%1, {UNRECOGNIZED NEXT VARIABLE} ❮%2❯%n",
                     p->line, p->col, p->sval);
                  exit(-1);
               }
               Tree *start = evaluate(deep_copy(fore->left));
               Tree *fini = evaluate(deep_copy(fore->right));
               const Val *valuep = get_value(fore->sval);
               Val value = *valuep;
               switch(value.typ) {
                  case 'd':
                     {
                        double step = 1.0;
                        if (fini->dval < start->dval) {
                           step = -1.0;
                        }
                        if (fore->middle) {
                           Tree *middle = evaluate(deep_copy(fore->middle));
                           step = middle->dval;
                        }
                        value.dval += step;
                        set_value(fore->sval, value);
                        if (step > 0.0 && value.dval <= fini->dval) {
                           np = fore->next;
                        }
                        else if (step < 0.0 && value.dval >= fini->dval) {
                           np = fore->next;
                        }
                     }
                     break;
                  case 'i':
                     {
                        int64_t step = 1;
                        if (fini->ival < start->ival) {
                           step = -1.0;
                        }
                        if (fore->middle) {
                           Tree *middle = evaluate(deep_copy(fore->middle));
                           step = middle->ival;
                        }
                        value.ival += step;
                        set_value(fore->sval, value);
                        if (step > 0 && value.ival <= fini->ival) {
                           np = fore->next;
                        }
                        else if (step < 0 && value.ival >= fini->ival) {
                           np = fore->next;
                        }
                     }
                     break;
                  case 'r':
                     {
                        Rational value_rval = *(value.rval);
                        Rational step = Rational(1,1,0,1);
                        if (fini->rval < start->rval) {
                           step = Rational(-1,1,0,1);
                        }
                        if (fore->middle) {
                           Tree *middle = evaluate(deep_copy(fore->middle));
                           step = *(middle->rval);
                        }
                        value_rval = value_rval + step;
                        value.rval = new Rational(value_rval);
                        set_value(fore->sval, value);
                        if (step.sgn() > 0 && value_rval <= *(fini->rval)) {
                           np = fore->next;
                        }
                        else if (step.sgn() < 0 && value_rval >= *(fini->rval)) {
                           np = fore->next;
                        }
                     }
                     break;
                  case 's':
                     {
                        // punt, this is just stupid
                        GURU;
                        // test case loopstring
                        eprintf("{ERROR}: @%0:%1, {NEXT ON FOR LOOP WITH STRING VARIABLE}%n",
                           p->line, p->col);
                        exit(-1);
                     }
                     break;
               }
               if (np == onp) {
                  get_for(p->sval, true);
               }
            }
            break;
         case YYSTOP: // why are there two of these???
         case YYEND:  // when they both do the same things???
            exit(0);
            break;
         case YYGOTO:
            {
               Tree *t = get_label(p->sval);
               if (!t) {
                  GURU;
                  // test case badgoto
                  eprintf("{ERROR}: @%0:%1, {UNRECOGNIZED GOTO LABEL} ❮%2❯%n",
                     p->line, p->col, p->sval);
                  exit(-1);
               }
               np = t;
            }
            break;
         case YYGOSUB:
            {
               Tree *t = get_label(p->sval);
               if (!t) {
                  GURU;
                  // test case badgosub
                  eprintf("{ERROR}: @%0:%1, {UNRECOGNIZED GOSUB LABEL} ❮%2❯%n",
                     p->line, p->col, p->sval);
                  exit(-1);
               }

               gosub_stack[gosub_spot++] = np;
               if (gosub_spot == GOSUB_STACKSIZE) {
                  GURU;
                  // test case gosuboverflow
                  eprintf("{ERROR}: @%0:%1, {GOSUB STACK OVERFLOW}%n", p->line, p->col);
                  exit(-1);
               }

               np = t;
            }
            break;
         case YYRETURN:
            {
               gosub_spot--;
               if (gosub_spot < 0) {
                  GURU;
                  // test case gosubunderflow
                  eprintf("{ERROR}: @%0:%1, {GOSUB STACK UNDERFLOW}%n", p->line, p->col);
                  exit(-1);
               }
               np = gosub_stack[gosub_spot];
            }
            break;
         case YYIFGOTO:
         case YYIFGOSUB:
         case YYIFSTMTLIST:
            {
               Tree *left = evaluate(deep_copy(p->left));
               Tree *right = evaluate(deep_copy(p->right));
               Tree *target = (p->op == YYIFSTMTLIST) ? p->middle : get_label(p->middle->sval);
               if (!target) {
                  GURU;
                  // test case badiflabel
                  eprintf("{ERROR}: @%0:%1, {UNKNOWN IF LABEL} ❮%2❯%n", p->line, p->col, p->middle->sval);
                  exit(-1);
               }

               if (left->op != right->op) {
                  // in a mismatch, try to make strings into numbers
                  if (left->op == YYSTRING) {
                     upgrade_to_number(left);
                  }
                  if (right->op == YYSTRING) {
                     upgrade_to_number(right);
                  }

                  if (left->op == YYRATIONAL && right->op == YYINTEGER) {
                     upgrade_to_rational(right);
                  }
                  else if (left->op == YYINTEGER && right->op == YYRATIONAL) {
                     upgrade_to_rational(left);
                  }

                  if (left->op == YYRATIONAL && right->op == YYDOUBLE) {
                     upgrade_to_double(left);
                  }
                  else if (left->op == YYDOUBLE && right->op == YYRATIONAL) {
                     upgrade_to_double(right);
                  }

                  if (left->op == YYINTEGER && right->op == YYDOUBLE) {
                     upgrade_to_double(left);
                  }
                  else if (left->op == YYDOUBLE && right->op == YYINTEGER) {
                     upgrade_to_double(right);
                  }
               }

               if (left->op == right->op) {
                  if (is_relation_true(left, p->sval, right)) {
                     if (p->op == YYIFGOSUB) {
                        gosub_stack[gosub_spot++] = np;
                        if (gosub_spot == GOSUB_STACKSIZE) {
                           GURU;
                           // test case ifgosuboverflow
                           eprintf("{ERROR}: @%0:%1, {GOSUB STACK OVERFLOW}%n", p->line, p->col);
                           exit(-1);
                        }
                     }
                     np = target;
                  }
               }
               else {
                  GURU;
                  // test case voidif
                  eprintf("{ERROR}: @%0:%1, {LEFT / RIGHT OPERATION MISMATCH} ❮%2❯ ❮%3❯%n",
                     p->line, p->col, eop2string(left->op), eop2string(right->op));
                  exit(-1);
               }
            }
            break;
         case YYON:
            {
               Tree *result = evaluate(deep_copy(p->left));
               int i = -1;
               switch (result->op) {
                  case YYDOUBLE:
                     i = (int) result->dval;
                     break;
                  case YYINTEGER:
                     i = (int) result->ival;
                     break;
                  case YYRATIONAL:
                     i = (int) ((double)(*result->rval));
                     break;
                  case YYSTRING:
                     i = atoi(result->sval);
                     break;
                  default:
                     GURU;
                     // test case voidon
                     eprintf("{ERROR}: @%0:%1, {UNHANDLED OPERATION} ❮%2❯%n",
                        p->line, p->left->col, eop2string(result->op));
                     exit(-1);
                     break;
               }
               if (i < 0) {
                  GURU;
                  // test case negativeon
                  eprintf("{ERROR}: @%0:%1, {NEGATIVE INDEX} ❮%d❯%n", p->line, p->left->col, i);
                  exit(-1);
               }
               int oi = i;
               Tree *label = p->right;
               while (i && label) {
                  i--;
                  label = label->middle;
               }
               if (i || label == NULL) {
                  GURU;
                  // test case bigon
                  eprintf("{ERROR}: @%0:%1, {INDEX OUT OF RANGE} ❮%2❯%n", p->line, p->left->col, oi);
                  exit(-1);
               }
               Tree *target = get_label(label->sval);
               if (!target) {
                  GURU;
                  // test case badonlabel
                  eprintf("{ERROR}: @%0:%1, {UNDEFINED LABEL} ❮%2❯%n", p->line, label->col, label->sval);
                  exit(-1);
               }
               if (p->ival) { // GOSUB
                  gosub_stack[gosub_spot++] = np;
                  if (gosub_spot == GOSUB_STACKSIZE) {
                     GURU;
                     // test case ongosuboverflow
                     eprintf("{ERROR}: @%0:%1, {GOSUB STACK OVERFLOW}%n", p->line, p->col);
                     exit(-1);
                  }
               }
               np = target;
            }
            break;
         case YYREM:
            {
               // do... nothing...
               // this is here so the default case doesn't howl at REM statements
               // go figure.
            }
            break;
         case YYDATA:
            {
               // as above, for REM
            }
            break;
         case YYRESTORE:
            {
               rewind_data();
            }
            break;
         case YYREAD:
            {
               for (Tree *varname = p->right; varname; varname = varname->middle) {
                  Val value;
                  value.typ = next_data_type();
                  switch(value.typ) {
                     case 'd':
                        get_data(value.dval);
                        set_value(varname->sval, value);
                        break;
                     case 'i':
                        get_data(value.ival);
                        set_value(varname->sval, value);
                        break;
                     case 'r':
                        get_data(value.rval);
                        set_value(varname->sval, value);
                        break;
                     case 's':
                        get_data(value.sval);
                        set_value(varname->sval, value);
                        break;
                     default:
                        GURU;
                        // test case readunderflow
                        eprintf("{ERROR}: @%0:%1, {DATA READ UNDERFLOW}%n", p->line, p->col);
                        exit(-1);
                        break;
                  }
               }
            }
            break;
         case YYINPUT:
            {
               for (Tree *varname = p->right; varname; varname = varname->middle) {
                  char buf[1024];
                  printf("%s? ",varname->sval);
                  fflush(stdout);
                  char *s = fgets(buf, sizeof(buf), stdin); // TODO FIX is this unicode/utf8 safe?
                  if (s) {
                     // trim newlines or anything else goofy
                     for (char *p = s; *p; p++) {
                        if (*p < ' ') {
                           *p = 0;
                        }
                     }
                     // now do the conversion
                     Val value = convert_to_value(s);
                     set_value(varname->sval, value);
                  }
                  else {
                     GURU;
                     // test case inputunderflow
                     eprintf("{ERROR}: @%0:%1, {DATA INPUT UNDERFLOW}%n", p->line, p->col);
                     exit(-1);
                  }
               }
            }
            break;
         case YYBASE:
            {
               // this is handled by register_option_base
               // nothing to do here
            }
            break;
         case YYDIM:
            {
               // this is handled by register_arrays
               // nothing to do here
            }
            break;
         case YYDEF:
            {
               // this is handled by register_def
               // nothing to do here
            }
            break;
         default:
            GURU;
            // no test case
            eprintf("{ERROR}: @%0:%1, {UNHANDLED OPERATION CODE} ❮%2❯%n",
               p->line, p->col, eop2string(p->op));
            exit(-1);
            break;
      }
      p = np;
   }
}

void runtree(Tree *root) {
   register_labels(root);
   register_option_base(root);
   register_arrays(root);
   register_def(root);
   register_data(root);
   run(root);
}


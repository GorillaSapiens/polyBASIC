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
            eprintf("{ERROR}: @%0:%1, {LABEL ALREADY DEFINED}, ❰%2❱ @%3:%4%n",
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
         if (V_AS_I(root->value) != 0) {
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
            if (is_bound_defined(V_AS_S(list->value))) {
               const Varbound *vb = get_varbound(V_AS_S(list->value));
               GURU;
               // test case multiple_dim
               eprintf("{ERROR}: @%0:%1, {ARRAY ALREADY DEFINED} ❰%2❱ @%3%n",
                  list->line, list->col, V_AS_S(list->value), vb->line);
               exit(-1);
            }
            else {
               if (list->right) {
                  set_bound(V_AS_S(list->value), list->line, 2,
                     V_AS_I(list->left->value),
                     V_AS_I(list->right->value));
               }
               else {
                  set_bound(V_AS_S(list->value), list->line, 1,
                     V_AS_I(list->left->value),
                     0);
               }
            }
         }
      }

      root = root->next;
   }
}

static void register_def(Tree *root) {
   while (root) {
      if (root->op == YYDEF && V_AS_S(root->value)) {
         if (is_def_defined(V_AS_S(root->value))) {
            Tree *prev = get_def(V_AS_S(root->value));
            GURU;
            // test case multiple_def
            eprintf("{ERROR}: @%0:%1 {FUNCTION DEFINITION MULTIPLY DEFINED} ❰%2❱ @%3:%4%n",
               root->line, root->col, V_AS_S(root->value), prev->line, prev->col);
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
            add_data(data->value);
         }
      }
      root = root->next;
   }
}

void upgrade_to_number(Tree *p) {
   if (p->op == YYSTRING) {
      const char *s = strdup(V_AS_S(p->value));
      p->value.vacate();

      if (void_enabled && !strcasecmp(s, "void")) {
         p->op = YYVOID;
         // vacate() call above makes value void
      }
      else if (strchr((char *)s, '#') == s) {
         p->op = YYRATIONAL;
         p->value.base() = Rational(s);
      }
      else if (strchr((char *)s, '.') || strchr((char *)s, 'E')) {
         p->op = YYDOUBLE;
         p->value.base() = atof(s);
      }
      else {
         p->op = YYINTEGER;
         p->value.base() = atoll(s);
      }

      free((void *)s);
   }
}

void upgrade_to_rational(Tree *p) {
   if (p->op == YYINTEGER) {
      int64_t ival = V_AS_I(p->value);
      int8_t sign = 1;
      if (ival < 0) {
         sign = -1;
         ival = -ival;
      }
      p->op = YYRATIONAL;
      p->value.base() = Rational(sign, ival, 0, 1);
   }
   else if (p->op == YYDOUBLE) {
      p->op = YYRATIONAL;
      p->value.base() = Rational(V_AS_D(p->value));
   }
}

void upgrade_to_double(Tree *p) {
   if (p->op == YYINTEGER) {
      int64_t ival = V_AS_I(p->value);
      p->op = YYDOUBLE;
      p->value.base() = (double) ival;
   }
   else if (p->op == YYRATIONAL) {
      double dval = (double)(V_AS_R(p->value));
      p->value.vacate();
      p->op = YYDOUBLE;
      p->value.base() = dval;
   }
}

void upgrade_to_integer(Tree *p) {
   if (p->op == YYDOUBLE) {
      p->op = YYINTEGER;
      p->value.base() = (int64_t) floor(V_AS_D(p->value));
   }
   else if (p->op == YYRATIONAL) {
      double dval = (double)(V_AS_R(p->value));
      p->value.vacate();
      p->op = YYINTEGER;
      p->value.base() = (int64_t) floor(dval);
   }
}

void upgrade_to_string(Tree *p) {
   if (p->op != YYSTRING) {
      char buf[1024];
      if (p->op == YYDOUBLE) {
         snprintf(buf, sizeof(buf), "%g", V_AS_D(p->value));
         if (!strchr(buf, '.')) {
            strcat(buf, ".0");
         }
         p->op = YYSTRING;
         p->value.base() = strdup(buf);
      }
      else if (p->op == YYINTEGER) {
         snprintf(buf, sizeof(buf), "%ld", V_AS_I(p->value));
         p->op = YYSTRING;
         p->value.base() = strdup(buf);
      }
      else if (p->op == YYRATIONAL) {
         V_AS_R(p->value).shortprint(buf, sizeof(buf));
         p->value.vacate();
         p->op = YYSTRING;
         p->value.base() = strdup(buf);
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

// make a deep copy
Tree *deep_copy(Tree *subtree) {
   Tree *copy = new Tree(*subtree);

   // don't copy labels, we'd just have to free them later

   if (subtree->left) { copy->left = deep_copy(subtree->left); }
   if (subtree->middle) { copy->middle = deep_copy(subtree->middle); }
   if (subtree->right) { copy->right = deep_copy(subtree->right); }

   copy->value = subtree->value;

   copy->next = NULL;

   return copy;
}

#define BUILTINFUNC(name, args) void builtin_ ## name(Tree *p)

BUILTINFUNC(ABS, 1) {
   upgrade_to_number(p->right);

   if (p->right->op == YYDOUBLE) {
      V_AS_D(p->right->value) = fabs(V_AS_D(p->right->value));
   }
   else if (p->right->op == YYINTEGER) {
      V_AS_I(p->right->value) = llabs(V_AS_I(p->right->value));
   }
   else if (p->right->op == YYRATIONAL) {
      V_AS_R(p->right->value) = V_AS_R(p->right->value).abs();
   }

   p->op = p->right->op;
   p->value = p->right->value;
   delete(p->right);
   p->right = NULL;
}

BUILTINFUNC(ATN, 1) {
   upgrade_to_number(p->right);
   upgrade_to_double(p->right);
   V_AS_D(p->right->value) = atan(V_AS_D(p->right->value));

   p->op = p->right->op;
   p->value = p->right->value;
   delete(p->right);
   p->right = NULL;
}

BUILTINFUNC(CHR, 1) {
   upgrade_to_number(p->right);
   upgrade_to_integer(p->right);

   p->right->op = YYSTRING;
   p->right->value.base() = strdup(int2utf8(V_AS_I(p->right->value)));

   p->op = p->right->op;
   p->value = p->right->value;
   delete(p->right);
   p->right = NULL;
}

BUILTINFUNC(COS, 1) {
   upgrade_to_number(p->right);
   upgrade_to_double(p->right);
   V_AS_D(p->right->value) = cos(V_AS_D(p->right->value));

   p->op = p->right->op;
   p->value = p->right->value;
   delete(p->right);
   p->right = NULL;
}

BUILTINFUNC(DBL, 1) {
   upgrade_to_number(p->right);
   upgrade_to_double(p->right);

   p->op = p->right->op;
   p->value = p->right->value;
   delete(p->right);
   p->right = NULL;
}

BUILTINFUNC(EXP, 1) {
   upgrade_to_number(p->right);
   upgrade_to_double(p->right);
   V_AS_D(p->right->value) = pow(M_E,V_AS_D(p->right->value));

   p->op = p->right->op;
   p->value = p->right->value;
   delete(p->right);
   p->right = NULL;
}

BUILTINFUNC(INT, 1) {
   upgrade_to_number(p->right);
   upgrade_to_integer(p->right);

   p->op = p->right->op;
   p->value = p->right->value;
   delete(p->right);
   p->right = NULL;
}

BUILTINFUNC(RAT, 1) {
   upgrade_to_number(p->right);
   upgrade_to_rational(p->right);

   p->op = p->right->op;
   p->value = p->right->value;
   delete(p->right);
   p->right = NULL;
}

BUILTINFUNC(STR, 1) {
   upgrade_to_string(p->right);

   p->op = p->right->op;
   p->value = p->right->value;
   delete(p->right);
   p->right = NULL;
}

BUILTINFUNC(LOG, 1) {
   upgrade_to_number(p->right);
   upgrade_to_double(p->right);
   V_AS_D(p->right->value) = log(V_AS_D(p->right->value));

   p->op = p->right->op;
   p->value = p->right->value;
   delete(p->right);
   p->right = NULL;
}

BUILTINFUNC(RND, 1) {
   upgrade_to_number(p->right);
   upgrade_to_double(p->right);
   p->right->value.base() = V_AS_D(p->right->value) *
      ((double) rand() / ((double) RAND_MAX + 1));

   p->op = p->right->op;
   p->value = p->right->value;
   delete(p->right);
   p->right = NULL;
}

BUILTINFUNC(RANDOMIZE, 0) {
   time_t t = time(NULL);
   srand(t);
   p->op = YYINTEGER;
   p->value.base() = t;
}

BUILTINFUNC(SGN, 1) {
   upgrade_to_number(p->right);
   upgrade_to_integer(p->right);
   if (V_AS_I(p->right->value) < 0) {
      p->right->value.base() = -1;
   }
   else if (V_AS_I(p->right->value) > 0) {
      p->right->value.base() = 1;
   }
   else {
      p->right->value.base() = 0;
   }

   p->op = p->right->op;
   p->value = p->right->value;
   delete(p->right);
   p->right = NULL;
}

BUILTINFUNC(SIN, 1) {
   upgrade_to_number(p->right);
   upgrade_to_double(p->right);
   V_AS_D(p->right->value) = sin(V_AS_D(p->right->value));

   p->op = p->right->op;
   p->value = p->right->value;
   delete(p->right);
   p->right = NULL;
}

BUILTINFUNC(SQR, 1) {
   upgrade_to_number(p->right);
   upgrade_to_double(p->right);
   V_AS_D(p->right->value) = sqrt(V_AS_D(p->right->value));

   p->op = p->right->op;
   p->value = p->right->value;
   delete(p->right);
   p->right = NULL;
}

BUILTINFUNC(TAB, 1) {
   upgrade_to_number(p->right);
   upgrade_to_integer(p->right);

   char buffer[128];
   sprintf(buffer, "\x1b[%ldG", V_AS_I(p->right->value));
   p->right->op = YYSTRING;
   p->right->value.base() = strdup(buffer);

   p->op = p->right->op;
   p->value = p->right->value;
   delete(p->right);
   p->right = NULL;
}

BUILTINFUNC(TAN, 1) {
   upgrade_to_number(p->right);
   upgrade_to_double(p->right);
   V_AS_D(p->right->value) = tan(V_AS_D(p->right->value));

   p->op = p->right->op;
   p->value = p->right->value;
   delete(p->right);
   p->right = NULL;
}

// talk about arcane!
BUILTINFUNC(VAL, 1) {
   if (p->right->op != YYSTRING) {
      GURU;
      // no test case
      eprintf("{ERROR}: @%0:%1, {VAL ARGUMENT MUST BE STRING} ❰%2❱%n",
            p->line, p->col, eop2string(p->right->op));
      exit(-1);
   }

   char buf[1024];
   const char *in = V_AS_S(p->right->value);
   char *out = buf;
   bool allow_plusminus = true;
   bool allow_dot = true;
   bool allow_e = true;
   bool done = false;

   while(*in && !done) {
      switch (*in) {
         case '+':
         case '-':
            if (!allow_plusminus) {
               done = true;
            }
            else {
               allow_plusminus = false;
               *out++ = *in;
            }
            break;
         case '.':
            if (!allow_dot) {
               done = true;
            }
            else {
               allow_dot = false;
               *out++ = *in;
            }
            break;
         case 'e':
         case 'E':
            if (!allow_e) {
               done = true;
            }
            else {
               allow_e = false;
               allow_plusminus = true;
               *out++ = *in;
            }
            break;
         case '0':
         case '1':
         case '2':
         case '3':
         case '4':
         case '5':
         case '6':
         case '7':
         case '8':
         case '9':
            if (!allow_e) {
               allow_plusminus = false;
            }
            *out++ = *in;
            break;
         case ' ':
            // ignored
            break;
         default:
            done = true;
            break;
      }
      in++;
   }
   *out = 0;

   p->op = YYDOUBLE;
   p->value.base() = atof(buf);
   delete(p->right);
   p->right = NULL;
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
      char *nc = strdup(name);
      if (nc[strlen(nc)-1] == '$') {
         nc[strlen(nc)-1] = 0;
         translation = has_tuple(nc);
      }
      free(nc);
   }

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

// caution, returns strdup'd memory
char *get_var_array_name(Tree *p) {
   Varbound *vb = (Varbound *) get_varbound(V_AS_S(p->value));
   int count = paramcount(p->right);

   if (!vb) {
      set_bound(V_AS_S(p->value), p->line, count, 10, 10);
      vb = (Varbound *) get_varbound(V_AS_S(p->value));
   }

   if (p->right) {
      if (p->right->op != YYINTEGER) {
         GURU;
         // test case voidarraysubscript
         eprintf("{ERROR}: @%0:%1, {ARRAY SUBSCRIPT NOT A NUMBER} ❰%2❱(%3) ❰%4❱%n",
               p->line, p->col, V_AS_S(p->value), 0, eop2string(p->right->op));
         exit(-1);
      }
      if (p->right->middle && p->right->middle->op != YYINTEGER) {
         GURU;
         // no test case
         eprintf("{ERROR}: @%0:%1, {ARRAY SUBSCRIPT NOT A NUMBER} ❰%2❱(%3) ❰%4❱%n",
               p->line, p->col, V_AS_S(p->value), 1, eop2string(p->right->middle->op));
         exit(-1);
      }
   }

   if (vb) {
      if (vb->dimensions == 0 && count > 0) {
         GURU;
         // test case varbounds3 vardim3
         eprintf("{ERROR}: @%0:%1, {VARIABLE USED AS ARRAY} ❰%2❱ @%3%n",
               p->line, p->col, V_AS_S(p->value), vb->line);
         exit(-1);
      }
      if (count == 0 && vb->dimensions > 0) {
         GURU;
         // test case vardim1 vardim2
         eprintf("{ERROR}: @%0:%1, {ARRAY USED AS VARIABLE} ❰%2❱ @%3%n",
               p->line, p->col, V_AS_S(p->value), vb->line);
         exit(-1);
      }
      if (count != vb->dimensions) {
         GURU;
         // test case varbounds4 vardim4
         eprintf("{ERROR}: @%0:%1, {ARRAY INDEX SIZE MISMATCH} ❰%2❱ DIM%3 @%4%n",
               p->line, p->col, V_AS_S(p->value), vb->dimensions, vb->line);
         exit(-1);
      }
      if (vb->dimensions == 1 && (V_AS_I(p->right->value) < option_base ||
                                  V_AS_I(p->right->value) > vb->upper1)) {
         GURU;
         // test case varbounds
         eprintf("{ERROR}: @%0:%1, {ARRAY INDEX OUT OF BOUNDS} ❰%2❱(%5) ❰%2❱(%3..%4) @%6%n",
               p->line, p->col,
               V_AS_S(p->value), option_base, vb->upper1,
               V_AS_I(p->right->value), vb->line);
         exit(-1);
      }
      if (vb->dimensions == 2 &&
            (V_AS_I(p->right->value) < option_base || V_AS_I(p->right->value) > vb->upper1 ||
             V_AS_I(p->right->middle->value) < option_base || V_AS_I(p->right->middle->value) > vb->upper2)) {
         GURU;
         // test case varbounds1 varbounds2
         eprintf("{ERROR}: @%0:%1, {ARRAY INDEX OUT OF BOUNDS} ❰%2❱(%6,%7) ❰%2❱(%3..%4,%3..%5) @%8%n",
               p->line, p->col, V_AS_S(p->value), option_base, vb->upper1, vb->upper2,
               V_AS_I(p->right->value), V_AS_I(p->right->middle->value), vb->line);
         exit(-1);
      }
   }

   if (p->right) { // an array
      int n = 0;
      char buf[4096];
      sprintf(buf, "%s(", V_AS_S(p->value));

      for (Tree *tree = p->right; tree; tree = tree->middle) {
         upgrade_to_number(tree);
         upgrade_to_integer(tree);
         if (tree->middle) {
            sprintf(buf + strlen(buf), "%ld,", V_AS_I(tree->value));
         }
         else {
            sprintf(buf + strlen(buf), "%ld)", V_AS_I(tree->value));
         }
         n++;
      }

      return strdup(buf);
   }
   else { // a variable
      return strdup(V_AS_S(p->value));
   }
}

Tree *get_param(const char *s, Tree *params, Tree *vals) {
   while (params && vals) {
      if (!strcmp(s, V_AS_S(params->value))) {
         return vals;
      }
      params = params->middle;
      vals = vals->middle;
   }
   return NULL;
}

#define OP2NUM(x) ((((x)[0]) << 8) | ((x)[1]))

bool is_double_relation_true(Tree *left, const char *op, Tree *right) {
   switch(OP2NUM(op)) {
      case OP2NUM("="):
         return V_AS_D(left->value) == V_AS_D(right->value);
         break;
      case OP2NUM("<>"):
         return V_AS_D(left->value) != V_AS_D(right->value);
         break;
      case OP2NUM(">="):
         return V_AS_D(left->value) >= V_AS_D(right->value);
         break;
      case OP2NUM("<="):
         return V_AS_D(left->value) <= V_AS_D(right->value);
         break;
      case OP2NUM(">"):
         return V_AS_D(left->value) > V_AS_D(right->value);
         break;
      case OP2NUM("<"):
         return V_AS_D(left->value) < V_AS_D(right->value);
         break;
   }
   return false;
}

bool is_integer_relation_true(Tree *left, const char *op, Tree *right) {
   switch(OP2NUM(op)) {
      case OP2NUM("="):
         return V_AS_I(left->value) == V_AS_I(right->value);
         break;
      case OP2NUM("<>"):
         return V_AS_I(left->value) != V_AS_I(right->value);
         break;
      case OP2NUM(">="):
         return V_AS_I(left->value) >= V_AS_I(right->value);
         break;
      case OP2NUM("<="):
         return V_AS_I(left->value) <= V_AS_I(right->value);
         break;
      case OP2NUM(">"):
         return V_AS_I(left->value) > V_AS_I(right->value);
         break;
      case OP2NUM("<"):
         return V_AS_I(left->value) < V_AS_I(right->value);
         break;
   }
   return false;
}

bool is_rational_relation_true(Tree *left, const char *op, Tree *right) {
   switch(OP2NUM(op)) {
      case OP2NUM("="):
         return V_AS_R(left->value) == V_AS_R(right->value);
         break;
      case OP2NUM("<>"):
         return V_AS_R(left->value) != V_AS_R(right->value);
         break;
      case OP2NUM(">="):
         return V_AS_R(left->value) >= V_AS_R(right->value);
         break;
      case OP2NUM("<="):
         return V_AS_R(left->value) <= V_AS_R(right->value);
         break;
      case OP2NUM(">"):
         return V_AS_R(left->value) > V_AS_R(right->value);
         break;
      case OP2NUM("<"):
         return V_AS_R(left->value) < V_AS_R(right->value);
         break;
   }
   return false;
}

bool is_string_relation_true(Tree *left, const char *op, Tree *right) {
   int result = strcmp(V_AS_S(left->value), V_AS_S(right->value));
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
      Builtin *builtin = get_builtin(V_AS_S(p->value));
      if (builtin) { // it's a builtin function
         int count = 0;
         for (Tree *tree = p->right; tree; tree = tree->middle) {
            count++;
         }
         if (count != builtin->args) {
            GURU;
            // test case builtinparamcount
            eprintf("{ERROR}: @%0:%1, {INCORRECT NUMBER OF PARAMETERS} ❰%2❱ %3<>%4%n",
               p->line, p->col, has_tuple(V_AS_S(p->value)), count, builtin->args);
            exit(-1);
         }
         builtin->fptr(p);
      }
      else if (is_def_defined(V_AS_S(p->value))) {
         Tree *deftree = get_def(V_AS_S(p->value));

         int defcount = paramcount(deftree->left);
         int callcount = paramcount(p->right);

         if (defcount != callcount) {
            GURU;
            // test case param_mismatch1 param_mismatch2
            eprintf("{ERROR}: @%0:%1, {FUNCTION DEFINITION PARAMETER MISMATCH} ❰%2❱ %3<>%4%n",
               p->line, p->col, V_AS_S(p->value), defcount, callcount);
            exit(-1);
         }

         Tree *expression = deep_copy(deftree->right);
         Tree *val = evaluate(expression, deftree->left, p->right);
         // TODO FIX do we need to free anything up???
         p->op = val->op;
         switch (val->op) {
            case YYDOUBLE:
            case YYINTEGER:
            case YYRATIONAL:
            case YYSTRING:
               p->value = val->value;
               break;
            default:
               GURU;
               // test case defreturnsvoid
               eprintf("{ERROR}: @%0:%1, {UNKNOWN OP IN PARAMETER SUBSTITUTION} ❰%2❱%n",
                  p->line, p->col, eop2string(val->op));
               exit(-1);
               break;
         }
         // TODO FIX: do we need to null or free p->left or p->right???
      }
      else if (params && (tmp = /*assignment */ get_param(V_AS_S(p->value), params, vals))) {
         // parameter substitution from a defcall
         Tree *val = tmp;
         // TODO FIX do we need to free anything up???
         p->op = val->op;
         switch (val->op) {
            case YYDOUBLE:
            case YYINTEGER:
            case YYRATIONAL:
            case YYSTRING:
               p->value = val->value;
               break;
            default:
               GURU;
               // test case defgivenvoid
               eprintf("{ERROR}: @%0:%1, {UNKNOWN OP IN PARAMETER SUBSTITUTION} ❰%2❱%n",
                  p->line, p->col, eop2string(val->op));
               exit(-1);
               break;
         }
         // TODO FIX: do we need to null or free p->left or p->right???
      }
      else { // array or variable
         char *s = get_var_array_name(p);
         const Value *val = get_value(s);
         if (val) {
            if (p->right) {
               // TODO FIX // free p->right?!?!?
               p->right = NULL;
            }
            switch (val->index()) {
               case V_D:
                  p->op = YYDOUBLE;
                  break;
               case V_I:
                  p->op = YYINTEGER;
                  break;
               case V_R:
                  p->op = YYRATIONAL;
                  break;
               case V_S:
                  p->op = YYSTRING;
                  break;
            }
            p->value = *val;
         }
         else {
            GURU;
            // test case no_value
            eprintf("{ERROR}: @%0:%1, {VARIABLE OR ARRAY HAS NO VALUE} ❰%2❱%n",
               p->line, p->col, s);
            exit(-1);
         }
         free(s);
      }
   }

   if (p->op == YYLVAL) {
      Builtin *builtin = get_builtin(V_AS_S(p->value));
      if (builtin) { // it's a builtin function
         GURU;
         // test case assigntobuiltin
         eprintf("{ERROR}: @%0:%1, {CANNOT ASSIGN TO FUNCTION} ❰%2❱%n",
            p->line, p->col, has_tuple(V_AS_S(p->value)));
         exit(-1);
      }
      else if (is_def_defined(V_AS_S(p->value))) {
         GURU;
         // test case assigntodef
         eprintf("{ERROR}: @%0:%1, {CANNOT ASSIGN TO DEFINITION} ❰%2❱%n",
            p->line, p->col, V_AS_S(p->value));
         exit(-1);
      }
      else { // variable or array
         char *s = get_var_array_name(p);

         p->value.vacate();
         p->value.base() = s;
         delete(p->right);
         p->right = NULL;
      }
   }

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
                        p->value.base() = V_AS_D(p->left->value) + V_AS_D(p->right->value);
                        break;
                     case '-':
                        p->value.base() = V_AS_D(p->left->value) - V_AS_D(p->right->value);
                        break;
                     case '*':
                        p->value.base() = V_AS_D(p->left->value) * V_AS_D(p->right->value);
                        break;
                     case '/':
                        p->value.base() = V_AS_D(p->left->value) / V_AS_D(p->right->value);
                        break;
                     case '^':
                        p->value.base() = pow(V_AS_D(p->left->value),V_AS_D(p->right->value));
                        break;
                     default:
                        GURU;
                        // test case double_amp
                        eprintf("{ERROR}: @%0:%1, {UNRECOGNIZED DOUBLE MATH OPERATION} ❰%2❱%n",
                              p->line, p->col, eop2string(p->op));
                        exit(-1);
                        break;
                  }
                  p->op = YYDOUBLE;
                  delete(p->left);
                  p->left = NULL;
                  delete(p->right);
                  p->right = NULL;
                  break;
               case YYINTEGER:
                  switch(p->op) {
                     case '+':
                        p->value.base() = V_AS_I(p->left->value) + V_AS_I(p->right->value);
                        break;
                     case '-':
                        p->value.base() = V_AS_I(p->left->value) - V_AS_I(p->right->value);
                        break;
                     case '*':
                        p->value.base() = V_AS_I(p->left->value) * V_AS_I(p->right->value);
                        break;
                     case '/':
                        p->value.base() = V_AS_I(p->left->value) / V_AS_I(p->right->value);
                        break;
                     case '^':
                        p->value.base() = (int64_t) pow(V_AS_I(p->left->value),V_AS_I(p->right->value));
                        break;
                     default:
                        GURU;
                        // test case integer_amp
                        eprintf("{ERROR}: @%0:%1, {UNRECOGNIZED INTEGER MATH OPERATION} ❰%2❱%n",
                              p->line, p->col, eop2string(p->op));
                        exit(-1);
                        break;
                  }
                  p->op = YYINTEGER;
                  delete(p->left);
                  p->left = NULL;
                  delete(p->right);
                  p->right = NULL;
                  break;
               case YYRATIONAL:
                  switch(p->op) {
                     case '+':
                        {
                           Rational rval = V_AS_R(p->left->value) + V_AS_R(p->right->value);
                           p->value.base() = rval;
                           p->op = YYRATIONAL;
                           break;
                        }
                     case '-':
                        {
                           Rational rval = V_AS_R(p->left->value) - V_AS_R(p->right->value);
                           p->value.base() = rval;
                           p->op = YYRATIONAL;
                           break;
                        }
                     case '*':
                        {
                           Rational rval = V_AS_R(p->left->value) * V_AS_R(p->right->value);
                           p->value.base() = rval;
                           p->op = YYRATIONAL;
                           break;
                        }
                     case '/':
                        {
                           Rational rval = V_AS_R(p->left->value) / V_AS_R(p->right->value);
                           p->value.base() = rval;
                           p->op = YYRATIONAL;
                           break;
                        }
                     case '^':
                        {
                           double dval =
                              pow((double)V_AS_R(p->left->value), (double)V_AS_R(p->right->value));
                           p->value.base() = dval;
                           p->op = YYDOUBLE;
                           break;
                        }
                     default:
                        GURU;
                        // test case rational_amp
                        eprintf("{ERROR}: @%0:%1, {UNRECOGNIZED RATIONAL MATH OPERATION} ❰%2❱%n",
                              p->line, p->col, eop2string(p->op));
                        exit(-1);
                        break;
                  }
                  delete(p->left);
                  p->left = NULL;
                  delete(p->right);
                  p->right = NULL;
                  break;
               case YYSTRING:
                  switch(p->op) {
                     case '&':
                        {
                           char *sval = (char *) malloc(strlen(V_AS_S(p->left->value)) +
                                                        strlen(V_AS_S(p->right->value)) + 1);
                           sprintf(sval, "%s%s", V_AS_S(p->left->value), V_AS_S(p->right->value));
                           p->value.vacate();
                           p->value.base() = (const char *) sval;
                           p->op = YYSTRING;
                        }
                        break;
                     default:
                        GURU;
                        // no test case, strings are converted to numbers
                        eprintf("{ERROR}: @%0:%1, {STRING MATH LOGIC ERROR}%n", p->line, p->col);
                        exit(-1);
                        break;
                  }
                  delete(p->left);
                  p->left = NULL;
                  delete(p->right);
                  p->right = NULL;
                  break;
               default:
                  GURU;
                  // test case voidmath2 badstringmath
                  eprintf("{ERROR}: @%0:%1, {UNRECOGNIZED MATH TYPE} ❰%2❱%n",
                        p->line, p->col, eop2string(p->left->op));
                  exit(-1);
                  break;
            }
         }
         else {
            GURU;
            // test case voidmath
            eprintf("{ERROR}: @%0:%1, {OPERAND MISMATCH} ❰%2❱ ❰%3❱%n",
               p->line, p->col,
               eop2string(p->left ? p->left->op : -1),
               eop2string(p->right ? p->right->op : -1));
            exit(-1);
         }
      }
      else if (!p->left && p->right && p->op == '-') {
         switch (p->right->op) {
            case YYDOUBLE:
               p->value.base() = -(V_AS_D(p->right->value));
               p->op = YYDOUBLE;
               delete(p->right);
               p->right = NULL;
               break;
            case YYINTEGER:
               p->value.base() = -(V_AS_I(p->right->value));
               p->op = YYINTEGER;
               delete(p->right);
               p->right = NULL;
               break;
            case YYRATIONAL:
               {
                  Rational rval = -V_AS_R(p->right->value);
                  p->value.base() = rval;
                  p->op = YYRATIONAL;
                  delete(p->right);
                  p->right = NULL;
               }
               break;
            case YYSTRING:
            default:
               GURU;
               // test case voidnegation stringnegation
               eprintf("{ERROR}: @%0:%1, {OPERAND MISMATCH} ❰%2❱ ❰%3❱%n",
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
                  p->op = p->right->op;
                  p->value = p->right->value;
                  delete(p->right);
                  p->right = NULL;
               }
               break;
            case YYSTRING:
            default:
               GURU;
               // test case voidpositive stringpositive
               eprintf("{ERROR}: @%0:%1, {OPERAND MISMATCH} ❰%2❱ ❰%3❱%n",
                  p->line, p->col,
                  eop2string(p->op),
                  eop2string(p->right ? p->right->op : -1));
               exit(-1);
               break;
         }
      }
   }

   if (p->op == YYAND) {
      if (p->left->op == p->right->op &&
            p->left->op == YYINTEGER &&
            (V_AS_I(p->left->value) && V_AS_I(p->right->value))) {
         p->op = YYINTEGER;
         p->value.base() = 1;
      }
      else {
         p->op = YYINTEGER;
         p->value.vacate();
         p->value.base() = 0;
      }

      delete(p->left);
      delete(p->right);
   }

   if (p->op == YYOR) {
      if (p->left->op == p->right->op &&
            p->left->op == YYINTEGER &&
            (V_AS_I(p->left->value) || V_AS_I(p->right->value))) {
         p->op = YYINTEGER;
         p->value.base() = 1;
      }
      else {
         p->op = YYINTEGER;
         p->value.vacate();
         p->value.base() = 0;
      }

      delete(p->left);
      delete(p->right);
   }

   if (p->op == YYNOT) {
      if (p->right->op == YYINTEGER) {
         p->op = YYINTEGER;
         p->value.vacate();
         p->value.base() = V_AS_I(p->right->value) == 0 ? 1 : 0;
      }

      delete(p->right);
   }

   if (p->op == YYCOMPARE) {
      Tree *left = evaluate(deep_copy(p->left));
      Tree *right = evaluate(deep_copy(p->right));

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

      if (left->op != right->op) {
         GURU;
         // test case voidif
         eprintf("{ERROR}: @%0:%1, {LEFT / RIGHT OPERATION MISMATCH} ❰%2❱ ❰%3❱%n",
               p->line, p->col, eop2string(left->op), eop2string(right->op));
         exit(-1);
      }

      if (left->op == right->op &&
            is_relation_true(left, V_AS_S(p->value), right)) {
         p->op = YYINTEGER;
         p->value.vacate();
         p->value.base() = 1;
      }
      else {
         p->op = YYINTEGER;
         p->value.vacate();
         p->value.base() = 0;
      }
      delete(p->left);
      delete(p->right);
   }

   return p;
}

Value convert_to_value(const char *s) {
   Value value;
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
      value.base() = strdup(s);
   }
   else if (!has_noninteger) {
      value.base() = atol(s);
   }
   else if (!has_nondouble) {
      value.base() = atof(s);
   }
   else if (!has_nonrational) {
      value.base() = Rational(s);
   }
   else {
      GURU;
      // no test case, conversion always yeilds something
      eprintf("{ERROR}: {UNRECOGNIZED INPUT} ❰%0❱%n", s);
      exit(-1);
   }
   return value;
}

void switch_to_desired_index(Value &value, int desired_index) {
   if (value.index() == desired_index) {
      return;
   }

   switch (desired_index) {
      case V_D:
         {
            switch(value.index()) {
               case V_R:
                  {
                     double dval = (double) V_AS_R(value);
                     value.vacate();
                     value.base() = dval;
                  }
                  break;
               case V_I:
                  value.base() = (double) V_AS_I(value);
                  break;
            }
         }
         break;
      case V_R:
         {
            switch(value.index()) {
               case V_D:
                  {
                     Rational rval = Rational(V_AS_D(value));
                     value.base() = rval;
                  }
                  break;
               case V_I:
                  {
                     Rational rval = Rational(V_AS_I(value));
                     value.base() = rval;
                  }
                  break;
            }
         }
         break;
      case V_I:
         {
            switch(value.index()) {
               case V_D:
                  {
                     value.base() = (int64_t) floor(V_AS_D(value));
                  }
                  break;
               case V_R:
                  {
                     double dval = floor((double) V_AS_R(value));
                     value.vacate();
                     value.base() = (int64_t) dval;
                  }
                  break;
            }
         }
         break;
   }
}

int is_inverted(Value &left, Value &right) {
   switch(left.index()) {
      case V_D:
         return V_AS_D(right) < V_AS_D(left);
         break;
      case V_R:
         return V_AS_R(right) < V_AS_R(left);
         break;
      case V_I:
         return V_AS_I(right) < V_AS_I(left);
         break;
   }
   return 0;
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

               switch (result->op) {
                  case YYDOUBLE:
                  case YYINTEGER:
                  case YYRATIONAL:
                  case YYSTRING:
                     // do nothing
                     break;
                  default:
                     GURU;
                     // test case voidsetvalue
                     eprintf("{ERROR}: @%0:%1, {UNRECOGNIZED VARIABLE TYPE} ❰%2❱%n",
                        p->line, p->col, eop2string(result->op));
                     exit(-1);
                     break;
               }

               const char *varname = V_AS_S(lvalue->value);
               set_value(varname, result->value);

               delete(lvalue);
               delete(result);
            }
            break;
         case YYPRINT:
            {
               bool want_newline = true;
               Tree *result = evaluate(deep_copy(p));
               for (Tree *mid = result->middle; mid; mid = mid->middle) {
                  switch (mid->op) {
                     case YYDOUBLE:
                        {
                           char buf[1024];
                           sprintf(buf, "%g", V_AS_D(mid->value));
                           if (!strchr(buf, '.')) {
                              strcat(buf, ".0");
                           }
                           if (V_AS_D(mid->value) < 0.0) {
                              printf("%s", buf);
                           }
                           else {
                              printf(" %s", buf);
                           }

                           // other unsatisfactory answers:
                           //printf("%f", mid->dval);
                           //printf("%g", mid->dval);
                           //printf("%.*e ", DBL_DECIMAL_DIG, mid->dval);
                        }
                        break;
                     case YYINTEGER:
                        if (V_AS_I(mid->value) < 0) {
                           printf("%li", V_AS_I(mid->value));
                        }
                        else {
                           printf(" %li", V_AS_I(mid->value));
                        }
                        break;
                     case YYRATIONAL:
                        {
                           char buf[1024];
                           V_AS_R(mid->value).shortprint(buf, sizeof(buf));
                           printf("%s", buf);
                        }
                        break;
                     case YYSTRING:
                        printf("%s", V_AS_S(mid->value));
                        break;
                     case ',':
                        // TODO FIX
                        // this should forward to the next tab stop,
                        // and then fallthrough to the ';' case
                     case ';':
                        want_newline = false;
                        break;
                     default:
                        GURU;
                        // test case voidprint
                        eprintf("{ERROR}: @%0:%1, {UNRECOGNIZED OP IN PRINT} ❰%2❱%n",
                           p->line, p->col, eop2string(mid->op));
                        exit(-1);
                        break;
                  }
               }
               if (want_newline) {
                  printf("\n");
               }
            }
            break;
         case YYFOR:
            {
               set_for(p);
               Tree *result = evaluate(deep_copy(p->left));
               set_value(V_AS_S(p->value), result->value);
            }
            break;
         case YYNEXT:
            {
               Tree *onp = np;
               Tree *fore = get_for(V_AS_S(p->value), false);
               if (!fore) {
                  GURU;
                  // test case unrecognext
                  eprintf("{ERROR}: @%0:%1, {UNRECOGNIZED NEXT VARIABLE} ❰%2❱%n",
                     p->line, p->col, V_AS_S(p->value));
                  exit(-1);
               }

               Tree *start = evaluate(deep_copy(fore->left));
               Tree *increment = fore->middle ? evaluate(deep_copy(fore->middle)) : NULL;
               Tree *fini = evaluate(deep_copy(fore->right));
               const Value *valuep = get_value(V_AS_S(fore->value));

               Value svalue = start->value;
               Value cvalue = *valuep;
               Value fvalue = fini->value;
               Value ivalue;

               if (increment) {
                  ivalue = increment->value;
               }

               // this is the biggest mixup i've ever seen...
               // nothing prevents these things from having different types...
               // some things can be missing...
               // and we want everything to behave "reasonably" for the user...

               int desired_index = 0;

               if (svalue.index() == V_D ||
                   cvalue.index() == V_D ||
                   fvalue.index() == V_D ||
                   ivalue.index() == V_D) {
                  desired_index = V_D;
               }
               else if (svalue.index() == V_R ||
                        cvalue.index() == V_R ||
                        fvalue.index() == V_R ||
                        ivalue.index() == V_R) {
                  desired_index = V_R;
               }
               else {
                  desired_index = V_I;
               }

               switch_to_desired_index(svalue, desired_index);
               switch_to_desired_index(cvalue, desired_index);
               switch_to_desired_index(fvalue, desired_index);

               if (ivalue.index() == V_V) {
                  if (is_inverted(svalue, fvalue)) {
                     ivalue.base() = -1L;
                  }
                  else {
                     ivalue.base() = 1L;
                  }
               }
               switch_to_desired_index(ivalue, desired_index);

               // EVERYTHING should be the same now...

               switch(cvalue.index()) {
                  case V_D:
                     {
                        V_AS_D(cvalue) += V_AS_D(ivalue);
                        set_value(V_AS_S(fore->value), cvalue);
                        if (V_AS_D(ivalue) > 0.0 && V_AS_D(cvalue) <= V_AS_D(fvalue)) {
                           np = fore->next;
                        }
                        else if (V_AS_D(ivalue) < 0.0 && V_AS_D(cvalue) >= V_AS_D(fvalue)) {
                           np = fore->next;
                        }
                     }
                     break;
                  case V_I:
                     {
                        V_AS_I(cvalue) += V_AS_I(ivalue);
                        set_value(V_AS_S(fore->value), cvalue);
                        if (V_AS_I(ivalue) > 0 && V_AS_I(cvalue) <= V_AS_I(fvalue)) {
                           np = fore->next;
                        }
                        else if (V_AS_I(ivalue) < 0 && V_AS_I(cvalue) >= V_AS_I(fvalue)) {
                           np = fore->next;
                        }
                     }
                     break;
                  case V_R:
                     {
                        Rational i_rval(V_AS_R(ivalue));
                        Rational c_rval(V_AS_R(cvalue));
                        Rational f_rval(V_AS_R(fvalue));

                        c_rval = c_rval + i_rval;
                        cvalue.vacate();
                        cvalue.base() = Rational(c_rval);

                        set_value(V_AS_S(fore->value), cvalue);

                        if (i_rval.sgn() > 0 && c_rval <= f_rval) {
                           np = fore->next;
                        }
                        else if (i_rval.sgn() < 0 && c_rval >= f_rval) {
                           np = fore->next;
                        }
                     }
                     break;
                  case V_S:
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
                  get_for(V_AS_S(p->value), true);
               }
            }
            break;
         case YYSTOP: // why are there two of these???
         case YYEND:  // when they both do the same things???
            exit(0);
            break;
         case YYGOTO:
            {
               Tree *t = get_label(V_AS_S(p->value));
               if (!t) {
                  GURU;
                  // test case badgoto
                  eprintf("{ERROR}: @%0:%1, {UNRECOGNIZED GOTO LABEL} ❰%2❱%n",
                     p->line, p->col, V_AS_S(p->value));
                  exit(-1);
               }
               np = t;
            }
            break;
         case YYGOSUB:
            {
               Tree *t = get_label(V_AS_S(p->value));
               if (!t) {
                  GURU;
                  // test case badgosub
                  eprintf("{ERROR}: @%0:%1, {UNRECOGNIZED GOSUB LABEL} ❰%2❱%n",
                     p->line, p->col, V_AS_S(p->value));
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

               Tree *target = (p->op == YYIFSTMTLIST) ? p->middle : get_label(V_AS_S(p->middle->value));
               if (!target) {
                  GURU;
                  // test case badiflabel
                  eprintf("{ERROR}: @%0:%1, {UNKNOWN IF LABEL} ❰%2❱%n", p->line, p->col, V_AS_S(p->middle->value));
                  exit(-1);
               }

               if (left->op == YYINTEGER && V_AS_I(left->value)) {
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
            break;
         case YYON:
            {
               Tree *result = evaluate(deep_copy(p->left));
               int i = -1;
               switch (result->op) {
                  case YYDOUBLE:
                     i = (int) V_AS_D(result->value);
                     break;
                  case YYINTEGER:
                     i = (int) V_AS_I(result->value);
                     break;
                  case YYRATIONAL:
                     i = (int) ((double)V_AS_R(result->value));
                     break;
                  case YYSTRING:
                     i = atoi(V_AS_S(result->value));
                     break;
                  default:
                     GURU;
                     // test case voidon
                     eprintf("{ERROR}: @%0:%1, {UNHANDLED OPERATION} ❰%2❱%n",
                        p->line, p->left->col, eop2string(result->op));
                     exit(-1);
                     break;
               }
               if (i <= 0) {
                  GURU;
                  // test case negativeon
                  eprintf("{ERROR}: @%0:%1, {INDEX LESS THAN 1} ❰%2❱%n", p->line, p->left->col, i);
                  exit(-1);
               }
               int oi = i;
               i--;
               Tree *label = p->right;
               while (i && label) {
                  i--;
                  label = label->middle;
               }
               if (i || label == NULL) {
                  GURU;
                  // test case bigon
                  eprintf("{ERROR}: @%0:%1, {INDEX OUT OF RANGE} ❰%2❱%n", p->line, p->left->col, oi);
                  exit(-1);
               }
               Tree *target = get_label(V_AS_S(label->value));
               if (!target) {
                  GURU;
                  // test case badonlabel
                  eprintf("{ERROR}: @%0:%1, {UNDEFINED LABEL} ❰%2❱%n", p->line, label->col, V_AS_S(label->value));
                  exit(-1);
               }
               if (V_AS_I(p->value)) { // GOSUB
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
               Tree *varname = evaluate(deep_copy(p->right));
               while (varname) { 
                  Value value;
                  if (get_data(value)) {
                     set_value(V_AS_S(varname->value), value);
                  }
                  else {
                     GURU;
                     // test case readunderflow
                     eprintf("{ERROR}: @%0:%1, {DATA READ UNDERFLOW}%n", p->line, p->col);
                     exit(-1);
                  }
                  Tree *tmp = varname;
                  varname = varname->middle;
                  delete tmp;
               }
            }
            break;
         case YYINPUT:
            {
               if (p->left) {
                  printf("%s?", V_AS_S(p->left->value));
               }

               Tree *varname = evaluate(deep_copy(p->right));
               while (varname) {
                  char buf[1024];
                  printf("%s? ",V_AS_S(varname->value));
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
                     Value value = convert_to_value(s);
                     set_value(V_AS_S(varname->value), value);
                  }
                  else {
                     GURU;
                     // test case inputunderflow
                     eprintf("{ERROR}: @%0:%1, {DATA INPUT UNDERFLOW}%n", p->line, p->col);
                     if (ignore_diu) {
                        exit(0);
                     }
                     exit(-1);
                  }
                  Tree *tmp = varname;
                  varname = varname->middle;
                  delete tmp;
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
            eprintf("{ERROR}: @%0:%1, {UNHANDLED OPERATION CODE} ❰%2❱%n",
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


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

static int64_t option_base = 0;
static int64_t option_upper = 10; // default upper array bound per ECMA-55

static void register_labels(Tree *root) {
   while (root) {
      if (root->label) {
         if (is_lbl_defined(root->label)) {
            Tree *prev = get_label(root->label);
            GURU;
            // test case multiple_integer_label multiple_string_label
            eprintf("ERROR: label ❮%0❯ at %1:%2 already defined %3:%4%n",
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
               eprintf("SOURCE %0:%1, ARRAY ❮%2❯ ALREADY DEFINED ON LINE %3%n",
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

static void register_for(Tree *root) {
   while (root) {
      if (root->op == YYFOR && root->sval) {
         if (is_for_defined(root->sval)) {
            Tree *prev = get_for(root->sval);
            GURU;
            // test case multiple_for
            eprintf("ERROR: for ❮%0❯ multiply defined %1:%2 and %3:%4%n",
               root->sval, root->line, root->col, prev->line, prev->col);
            exit(-1);
         }
         else {
            set_for(root);
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
            eprintf("ERROR: def ❮%0❯ multiply defined %1:%2 and %3:%4%n",
               root->sval, root->line, root->col, prev->line, prev->col);
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

// fwd decls
Tree *evaluate(Tree *p);
void upgrade_to_number(Tree *p);
Tree *deep_copy(Tree *subtree, Tree *params = NULL, Tree *values = NULL);

int paramcount(Tree *tree) {
   int ret = 0;
   while (tree != NULL) {
      tree = tree->middle;
      ret++;
   }
   return ret;
}

Tree *deep_copy_defcall(Tree *defcall, Tree *params, Tree *values) {
   Tree *def = get_def(defcall->sval);
   if (!def) {
      GURU;
      // test case unrecognized_defcall
      eprintf("SOURCE %0:%1, UNRECOGNIZED FUNCTION DEF ❮%2❯%n",
         defcall->line, defcall->col, defcall->sval);
      exit(-1);
   }
   int defcount = paramcount(def->left);
   int callcount = paramcount(defcall->left);
   if (defcount != callcount) {
      GURU;
      // test case param_mismatch1 param_mismatch2
      eprintf("SOURCE %0:%1, FUNCTION DEF ❮%2❯ REQUIRES %3 PARAMS, BUT CALLED WITH %4%n",
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

// make a deep copy, substituting variables along the way
Tree *deep_copy(Tree *subtree, Tree *params, Tree *values) {
   Tree *copy = (Tree *) malloc(sizeof(Tree));
   memcpy(copy, subtree, sizeof(Tree));

   if (subtree->op == YYDEFCALL) {
      return deep_copy_defcall(subtree, params, values);
   }

// don't copy labels, we'd just have to free them later
//   if (subtree->label) {
//      copy->label = strdup(subtree->label);
//   }

   if (subtree->left) { copy->left = deep_copy(subtree->left, params, values); }
   if (subtree->middle) { copy->middle = deep_copy(subtree->middle, params, values); }
   if (subtree->right) { copy->right = deep_copy(subtree->right, params, values); }

   if (copy->op == YYSTRING) {
      copy->sval = strdup(subtree->sval);
   }
   else if (copy->op == YYRATIONAL) {
      copy->rval = new Rational(*(subtree->rval));
   }
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
            // test case no_value
            eprintf("ERROR: line %0 column %1, ❮%2❯ has no value%n",
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

   copy->next = NULL;

   return copy;
}

void upgrade_to_number(Tree *p) {
   if (p->op == YYSTRING) {
      const char *s = p->sval;
      if (strchr((char *)s, '#') == s) {
         p->op = YYRATIONAL;
         p->rval = new Rational(s);
      }
      else if (strchr((char *)s, '.') || strchr((char *)s, 'E')) {
         p->op = YYDOUBLE;
         // TODO FIX does this work????
         p->dval = atof(s);
      }
      else {
         p->op = YYINTEGER;
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
      p->rval = new Rational(sign, ival, 0, 1);
   }
}

void upgrade_to_double(Tree *p) {
   if (p->op == YYINTEGER) {
      int64_t ival = p->ival;
      p->op = YYDOUBLE;
      p->dval = (double) ival;
   }
   else if (p->op == YYRATIONAL) {
      Rational *deleteme = p->rval;
      double dval = (double)(*(p->rval));
      p->op = YYDOUBLE;
      p->dval = dval;
      delete deleteme;
   }
}

Tree *evaluate(Tree *p) {
   if (p->left) {
      p->left = evaluate(p->left);
   }
   if (p->middle) {
      p->middle = evaluate(p->middle);
   }
   if (p->right) {
      p->right = evaluate(p->right);
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

   if (p->op == YYABS) {
      Tree *freeme = p->left;
      if (p->left->op == YYSTRING) {
         upgrade_to_number(p->left);
      }
      if (p->left->op == YYDOUBLE) {
         p->left->dval = fabs(p->left->dval);
      }
      else if (p->left->op == YYINTEGER) {
         p->left->ival = llabs(p->left->ival);
      }
      else if (p->left->op == YYRATIONAL) {
         *(p->left->rval) = p->left->rval->abs();
      }
      memcpy(p, p->left, sizeof(Tree));
      free(freeme);
   }
   else if (p->op == YYATN) {
      Tree *freeme = p->left;
      if (p->left->op == YYSTRING) {
         upgrade_to_number(p->left);
      }
      if (p->left->op == YYDOUBLE) {
         p->left->dval = atan(p->left->dval);
      }
      else if (p->left->op == YYINTEGER) {
         p->left->op = YYDOUBLE;
         p->left->dval = atan((double)p->left->ival);
      }
      else if (p->left->op == YYRATIONAL) {
         p->left->op = YYDOUBLE;
         Rational *deleteme = p->left->rval;
         p->left->dval = atan((double)*(p->left->rval));
         delete deleteme;
      }
      memcpy(p, p->left, sizeof(Tree));
      free(freeme);
   }
   else if (p->op == YYCOS) {
      Tree *freeme = p->left;
      if (p->left->op == YYSTRING) {
         upgrade_to_number(p->left);
      }
      if (p->left->op == YYDOUBLE) {
         p->left->dval = cos(p->left->dval);
      }
      else if (p->left->op == YYINTEGER) {
         p->left->op = YYDOUBLE;
         p->left->dval = cos((double)p->left->ival);
      }
      else if (p->left->op == YYRATIONAL) {
         p->left->op = YYDOUBLE;
         Rational *deleteme = p->left->rval;
         p->left->dval = cos((double)*(p->left->rval));
         delete deleteme;
      }
      memcpy(p, p->left, sizeof(Tree));
      free(freeme);
   }
   else if (p->op == YYDBL) {
      Tree *freeme = p->left;
      if (p->left->op == YYSTRING) {
         p->left->op = YYDOUBLE;
         p->left->dval = atof(p->left->sval);
      }
      if (p->left->op == YYDOUBLE) {
         p->left->op = YYDOUBLE;
         p->left->dval = p->left->dval;
      }
      else if (p->left->op == YYINTEGER) {
         p->left->op = YYDOUBLE;
         p->left->dval = (double) p->left->ival;
      }
      else if (p->left->op == YYRATIONAL) {
         Rational *deleteme = p->left->rval;
         p->left->op = YYDOUBLE;
         p->left->dval = (double) (*(p->left->rval));
         delete deleteme;
      }
      memcpy(p, p->left, sizeof(Tree));
      free(freeme);
   }
   else if (p->op == YYEXP) {
      Tree *freeme = p->left;
      if (p->left->op == YYSTRING) {
         upgrade_to_number(p->left);
      }
      if (p->left->op == YYDOUBLE) {
         p->left->dval = pow(M_E,(p->left->dval));
      }
      else if (p->left->op == YYINTEGER) {
         p->left->op = YYDOUBLE;
         p->left->dval = pow(M_E,((double)p->left->ival));
      }
      else if (p->left->op == YYRATIONAL) {
         p->left->op = YYDOUBLE;
         Rational *deleteme = p->left->rval;
         p->left->dval = pow(M_E,((double)*(p->left->rval)));
         delete deleteme;
      }
      memcpy(p, p->left, sizeof(Tree));
      free(freeme);
   }
   else if (p->op == YYINT) {
      Tree *freeme = p->left;
      if (p->left->op == YYSTRING) {
         upgrade_to_number(p->left);
      }
      if (p->left->op == YYDOUBLE) {
         p->left->dval = floor(p->left->dval);
      }
      else if (p->left->op == YYINTEGER) {
         p->left->ival = (int)floor((double)p->left->ival);
      }
      else if (p->left->op == YYRATIONAL) {
         *(p->left->rval) = p->left->rval->floor();
      }
      memcpy(p, p->left, sizeof(Tree));
      free(freeme);
   }
   else if (p->op == YYRAT) {
      Tree *freeme = p->left;
      if (p->left->op == YYSTRING) {
         upgrade_to_number(p->left);
      }
      if (p->left->op == YYDOUBLE) {
         p->left->op = YYRATIONAL;
         p->left->rval = new Rational(p->left->dval);
      }
      else if (p->left->op == YYINTEGER) {
         p->left->op = YYRATIONAL;
         p->left->rval = new Rational(p->left->ival);
      }
      else if (p->left->op == YYRATIONAL) {
         // leave it alone
      }
      memcpy(p, p->left, sizeof(Tree));
      free(freeme);
   }
   else if (p->op == YYSTR) {
      Tree *freeme = p->left;
      if (p->left->op == YYSTRING) {
         // leave it alone
      }
      char buf[1024];
      if (p->left->op == YYDOUBLE) {
         snprintf(buf, sizeof(buf), "%f", p->left->dval);
         p->left->op = YYSTRING;
         p->left->sval = strdup(buf);
      }
      else if (p->left->op == YYINTEGER) {
         snprintf(buf, sizeof(buf), "%ld", p->left->ival);
         p->left->op = YYSTRING;
         p->left->sval = strdup(buf);
      }
      else if (p->left->op == YYRATIONAL) {
         Rational *deleteme = p->left->rval;
         deleteme->shortprint(buf, sizeof(buf));
         p->left->op = YYSTRING;
         p->left->sval = strdup(buf);
         delete deleteme;
      }
      memcpy(p, p->left, sizeof(Tree));
      free(freeme);
   }
   else if (p->op == YYLOG) {
      Tree *freeme = p->left;
      if (p->left->op == YYSTRING) {
         upgrade_to_number(p->left);
      }
      if (p->left->op == YYDOUBLE) {
         p->left->dval = log(p->left->dval);
      }
      else if (p->left->op == YYINTEGER) {
         p->left->op = YYDOUBLE;
         p->left->dval = log((double)p->left->ival);
      }
      else if (p->left->op == YYRATIONAL) {
         p->left->op = YYDOUBLE;
         Rational *deleteme = p->left->rval;
         p->left->dval = log((double)*(p->left->rval));
         delete deleteme;
      }
      memcpy(p, p->left, sizeof(Tree));
      free(freeme);
   }
   else if (p->op == YYRND) {
      p->op = YYDOUBLE;
      p->dval = (double)rand() / (double)RAND_MAX;
   }
   else if (p->op == YYRANDOMIZE) {
      time_t t = time(NULL);
      p->op = YYINTEGER;
      p->ival = t;
   }
   else if (p->op == YYSGN) {
      Tree *freeme = p->left;
      int sign = 0;
      if (p->left->op == YYSTRING) {
         upgrade_to_number(p->left);
      }
      if (p->left->op == YYDOUBLE) {
         if (p->left->dval > 0) { sign = 1; }
         if (p->left->dval < 0) { sign = -1; }
         p->left->op = YYINTEGER;
         p->left->ival = sign;
      }
      else if (p->left->op == YYINTEGER) {
         if (p->left->ival > 0) { sign = 1; }
         if (p->left->ival < 0) { sign = -1; }
         p->left->ival = sign;
      }
      else if (p->left->op == YYRATIONAL) {
         Rational *deleteme = p->left->rval;
         p->left->op = YYINTEGER;
         p->left->ival = p->left->rval->sgn();
         delete deleteme;
      }
      memcpy(p, p->left, sizeof(Tree));
      free(freeme);
   }
   else if (p->op == YYSIN) {
      Tree *freeme = p->left;
      if (p->left->op == YYSTRING) {
         upgrade_to_number(p->left);
      }
      if (p->left->op == YYDOUBLE) {
         p->left->dval = sin(p->left->dval);
      }
      else if (p->left->op == YYINTEGER) {
         p->left->op = YYDOUBLE;
         p->left->dval = sin((double)p->left->ival);
      }
      else if (p->left->op == YYRATIONAL) {
         p->left->op = YYDOUBLE;
         Rational *deleteme = p->left->rval;
         p->left->dval = sin((double)*(p->left->rval));
         delete deleteme;
      }
      memcpy(p, p->left, sizeof(Tree));
      free(freeme);
   }
   else if (p->op == YYSQR) {
      Tree *freeme = p->left;
      if (p->left->op == YYSTRING) {
         upgrade_to_number(p->left);
      }
      if (p->left->op == YYDOUBLE) {
         p->left->dval = sqrt(p->left->dval);
      }
      else if (p->left->op == YYINTEGER) {
         p->left->op = YYDOUBLE;
         p->left->dval = sqrt((double)p->left->ival);
      }
      else if (p->left->op == YYRATIONAL) {
         p->left->op = YYDOUBLE;
         Rational *deleteme = p->left->rval;
         p->left->dval = sqrt((double)*(p->left->rval));
         delete deleteme;
      }
      memcpy(p, p->left, sizeof(Tree));
      free(freeme);
   }
   else if (p->op == YYTAN) {
      Tree *freeme = p->left;
      if (p->left->op == YYSTRING) {
         upgrade_to_number(p->left);
      }
      if (p->left->op == YYDOUBLE) {
         p->left->dval = tan(p->left->dval);
      }
      else if (p->left->op == YYINTEGER) {
         p->left->op = YYDOUBLE;
         p->left->dval = tan((double)p->left->ival);
      }
      else if (p->left->op == YYRATIONAL) {
         p->left->op = YYDOUBLE;
         Rational *deleteme = p->left->rval;
         p->left->dval = tan((double)*(p->left->rval));
         delete deleteme;
      }
      memcpy(p, p->left, sizeof(Tree));
      free(freeme);
   }

   if (p->left && p->right ) {
      if (p->op == '+' ||
            p->op == '-' ||
            p->op == '*' ||
            p->op == '/' ||
            p->op == '^' ||
            p->op == '&') {

         // ECMA-116 uses '&' ; for other types we'll just treat it like a '+'

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

         if (p->left && p->right && p->left->op == p->right->op) {
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
                        eprintf("SOURCE %0:%1, UNRECOGNIZED DOUBLE MATH OP ❮%2❯%n",
                           p->line, p->col, p->op);
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
                        eprintf("SOURCE %0:%1, UNRECOGNIZED INTEGER MATH OP ❮%2❯%n",
                            p->line, p->col, p->op);
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
                        eprintf("SOURCE %0:%1, UNRECOGNIZED RATIONAL MATH OP ❮%2❯%n",
                           p->line, p->col, p->op);
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
                        p->sval = (char *) malloc(strlen(p->left->sval) + strlen(p->right->sval) + 1);
                        sprintf((char *) p->sval, "%s%s", p->left->sval, p->right->sval);
                        p->op = YYSTRING;
                        break;
                     default:
                        GURU;
                        // no test case, strings are converted to numbers
                        eprintf("SOURCE %0:%1, STRING MATH LOGIC ERROR%n", p->line, p->col);
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
            }
         }
         else {
            GURU;
            // no test case, type conversion is always successful
            eprintf("SOURCE %0:%1, OPERAND MISMATCH ❮%2:%3❯ ❮%4:%5❯%n",
               p->line, p->col,
               p->left, p->left ? p->left->op : -1,
               p->right, p->right ? p->right->op : -1);
            exit(-1);
         }
      }
   }

   return p;
}

#define OP2NUM(x) ((((x)[0]) << 8) | ((x)[1]))

bool is_double_relation_true(Tree *left, const char *op, Tree *right) {
   switch(OP2NUM(op)) {
      case OP2NUM("=="):
         return left->dval == right->dval;
         break;
      case OP2NUM("<>"):
      case OP2NUM("!="): // let's be kind to C programmers...
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
      case OP2NUM("=="):
         return left->ival == right->ival;
         break;
      case OP2NUM("<>"):
      case OP2NUM("!="): // let's be kind to C programmers...
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
      case OP2NUM("=="):
         return *(left->rval) == *(right->rval);
         break;
      case OP2NUM("<>"):
      case OP2NUM("!="): // let's be kind to C programmers...
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
      case OP2NUM("=="):
         return result == 0;
         break;
      case OP2NUM("<>"):
      case OP2NUM("!="): // let's be kind to C programmers...
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
      eprintf("UNRECOGNIZED INPUT ❮%0❯%n", s);
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
         case YYASSIGNARRAYREF:
            {
               char varname[1024];
               if (p->op == YYASSIGN) {

                  if (!is_bound_defined(p->left->sval)) {
                     set_bound(p->left->sval, p->line, 0, 0, 0);
                  }

                  const Varbound *vb = get_varbound(p->left->sval);
                  if (!vb || vb->dimensions != 0) {
                     if (vb->dimensions == 1) {
                        GURU;
                        // test case vardim1
                        eprintf("SOURCE %0:%1, VARIABLE ❮%2❯ DEFINED AS DIM%3(%4..%5) ARRAY ON LINE %6%n",
                           p->line, p->col, p->sval, vb->dimensions, option_base, vb->upper1, vb->line);
                     }
                     else {
                        GURU;
                        // test case vardim2
                        eprintf("SOURCE %0:%1, VARIABLE ❮%2❯ DEFINED AS DIM%3(%4..%5, %6..%7) ARRAY ON LINE %8%n",
                           p->line, p->col, p->sval, vb->dimensions, option_base, vb->upper1, option_base, vb->upper2, vb->line);
                     }
                     exit(-1);
                  }

                  sprintf(varname, "%s", p->left->sval);
               }
               else {
                  if (p->left->right) {
                     Tree *left = evaluate(deep_copy(p->left->left));
                     Tree *right = evaluate(deep_copy(p->left->right));

                     if (!is_bound_defined(p->left->sval)) {
                        set_bound(p->left->sval, p->line, 2, option_upper, option_upper);
                     }

                     const Varbound *vb = get_varbound(p->left->sval);
                     if (!vb || vb->dimensions != 2) {
                        if (vb->dimensions == 0) {
                           GURU;
                           // testcase vardim3
                           eprintf("SOURCE %0:%1, VARIABLE ❮%2❯ DEFINED AS NONARRAY ON LINE %3%n",
                                 p->line, p->col, p->sval, vb->line);
                           exit(-1);
                        }
                        else {
                           GURU;
                           // testcase vardim4
                           eprintf("SOURCE %0:%1, VARIABLE ❮%2❯ DEFINED AS DIM%3(%4..%5) ARRAY ON LINE %6%n",
                              p->line, p->col, p->sval, vb->dimensions, option_base, vb->upper1, vb->line);
                           exit(-1);
                        }
                        exit(-1);
                     }
                     if (left->ival < option_base || left->ival > vb->upper1) {
                        GURU;
                        // test case varbounds1
                        eprintf("SOURCE %0:%1, VARIABLE ❮%2❯ DIM1 AS %3 OUTSIDE BOUNDS1 %4..%5 FROM LINE %6%n",
                              p->line, p->col, p->sval, left->ival, option_base, vb->upper1, vb->line);
                        exit(-1);
                     }
                     if (right->ival < option_base || right->ival > vb->upper2) {
                        GURU;
                        // test case varbounds2
                        eprintf("SOURCE %0:%1, VARIABLE ❮%2❯ DIM2 AS %3 OUTSIDE BOUNDS2 %4..%5 FROM LINE %6%n",
                              p->line, p->col, p->sval, right->ival, option_base, vb->upper2, vb->line);
                        exit(-1);
                     }

                     sprintf(varname, "%s(%ld,%ld)", p->left->sval, left->ival, right->ival);
                  }
                  else {
                     Tree *left = evaluate(deep_copy(p->left->left));

                     if (!is_bound_defined(p->left->sval)) {
                        set_bound(p->left->sval, p->line, 1, option_upper, 0);
                     }

                     const Varbound *vb = get_varbound(p->left->sval);
                     if (!vb || vb->dimensions != 1) {
                        if (vb->dimensions == 0) {
                           GURU;
                           // test case varbounds3
                           eprintf("SOURCE %0:%1, VARIABLE ❮%2❯ DEFINED AS NONARRAY ON LINE %3%n",
                                 p->line, p->col, p->sval, vb->line);
                           exit(-1);
                        }
                        else {
                           GURU;
                           // test case varbounds4
                           eprintf("SOURCE %0:%1, VARIABLE ❮%2❯ DEFINED AS DIM%3 ARRAY ON LINE %4%n",
                                 p->line, p->col, p->sval, vb->dimensions, vb->line);
                           exit(-1);
                        }
                        exit(-1);
                     }
                     if (left->ival < option_base || left->ival > vb->upper1) {
                        GURU;
                        // test case varbounds
                        eprintf("SOURCE %0:%1, VARIABLE ❮%2❯ DIM1 AS %3 OUTSIDE BOUNDS %4..%5 FROM LINE %6%n",
                              p->line, p->col, p->sval, left->ival, option_base, vb->upper1, vb->line);
                        exit(-1);
                     }
                     sprintf(varname, "%s(%ld)", p->left->sval, left->ival);
                  }
               }
               Tree *result = evaluate(deep_copy(p->right));
               set_value(varname, result);
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
                        // no test case, this should not be possible
                        eprintf("SOURCE %0:%1, UNRECOGNIZED MID OP %2%n",
                           p->line, p->col, mid->op);
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
               Tree *result = evaluate(deep_copy(p->left));
               set_value(p->sval, result);
            }
            break;
         case YYNEXT:
            {
               Tree *fore = get_for(p->sval);
               if (!fore) {
                  GURU;
                  // test case unrecognext
                  eprintf("SOURCE %0:%1, UNRECOGNIZED NEXT VARIABLE ❮%2❯%n",
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
                        eprintf("SOURCE %0:%1, NEXT ON FOR LOOP WITH STRING VARIABLE%n",
                           p->line, p->col);
                        exit(-1);
                     }
                     break;
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
                  eprintf("SOURCE %0:%1, UNRECOGNIZED GOTO LABEL ❮%2❯%n",
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
                  eprintf("SOURCE %0:%1, UNRECOGNIZED GOSUB LABEL ❮%2❯%n",
                     p->line, p->col, p->sval);
                  exit(-1);
               }

               gosub_stack[gosub_spot++] = np;
               if (gosub_spot == GOSUB_STACKSIZE) {
                  GURU;
                  // test case gosuboverflow
                  eprintf("SOURCE %0:%1, GOSUB STACK OVERFLOW%n", p->line, p->col);
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
                  eprintf("SOURCE %0:%1, GOSUB STACK UNDERFLOW%n", p->line, p->col);
                  exit(-1);
               }
               np = gosub_stack[gosub_spot];
            }
            break;
         case YYIF:
            {
               Tree *left = evaluate(deep_copy(p->left));
               Tree *right = evaluate(deep_copy(p->right));
               Tree *target = get_label(p->middle->sval);
               if (!target) {
                  GURU;
                  // test case badiflabel
                  eprintf("SOURCE %0:%1, UNKNOWN IF LABEL ❮%2❯%n", p->line, p->col, p->sval);
                  exit(-1);
               }
               if (left->op != right->op) {
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

               if (left->op == right->op) {
                  if (is_relation_true(left, p->sval, right)) {
                     np = target;
                  }
               }
               else {
                  GURU;
                  // no test case
                  eprintf("SOURCE %0:%1, LEFT/RIGHT OP MISMATCH %2 %3%n",
                     p->line, p->col, left->op, right->op);
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
                     // no test case
                     eprintf("SOURCE %0:%1, UNHANDLED OP %2%n", p->line, p->left->col, result->op);
                     exit(-1);
                     break;
               }
               if (i < 0) {
                  GURU;
                  // test case negativeon
                  eprintf("SOURCE %0:%1, NEGATIVE INDEX %d%n", p->line, p->left->col, i);
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
                  eprintf("SOURCE %0:%1, INDEX %2 OUT OF RANGE%n", p->line, p->left->col, oi);
                  exit(-1);
               }
               Tree *target = get_label(label->sval);
               if (!target) {
                  GURU;
                  // test case badonlabel
                  eprintf("SOURCE %0:%1, UNDEFINED LABEL ❮%2❯%n", p->line, label->col, label->sval);
                  exit(-1);
               }
               if (p->ival) { // GOSUB
                  gosub_stack[gosub_spot++] = np;
                  if (gosub_spot == GOSUB_STACKSIZE) {
                     GURU;
                     // test case ongosuboverflow
                     eprintf("SOURCE %0:%1, GOSUB STACK OVERFLOW%n", p->line, p->col);
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
                        eprintf("SOURCE %0:%1, DATA READ UNDERFLOW%n", p->line, p->col);
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
                     eprintf("SOURCE %0:%1, DATA INPUT UNDERFLOW%n", p->line, p->col);
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
            eprintf("UNHANDLED OPCODE src:%0 op %1 line %2 col %3%n", __LINE__, p->op, p->line, p->col);
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
   register_for(root);
   register_def(root);
   register_data(root);
   run(root);
}


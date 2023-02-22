#include <string.h>
#include <stdlib.h>
#include "runtime_vars.h"
#include "hash.h"

#define HASH_SIZE 65536
static Var *vars[HASH_SIZE];

int is_var_defined(const char *p) {
   unsigned long h = hash(p);

   for (unsigned long i = 0; i < HASH_SIZE; i++) {
      unsigned long j = (i + h) % HASH_SIZE;
      if (vars[j] != NULL && !strcmp(p, vars[j]->name)) {
         return 1;
      }
   }
   return 0;
}

int set_value(const char *p, Val value) {
#if 0
   printf ("set_value %s = ", p);
   switch(value.typ) {
      case 'd':
         printf("%f\n", value.dval);
         break;
      case 'i':
         printf("%ld\n", value.ival);
         break;
      case 'r':
         char buffer[1024];
         value.rval->print(buffer);
         printf("%s\n", buffer);
         break;
      case 's':
         printf("%s\n", value.sval);
         break;
   }
#endif

   unsigned long h = hash(p);

   for (unsigned long i = 0; i < HASH_SIZE; i++) {
      unsigned long j = (i + h) % HASH_SIZE;
      if (vars[j] != NULL && !strcmp(p, vars[j]->name)) {
         if (vars[j]->value.typ == 'r') {
            delete vars[j]->value.rval;
         }
         else if (vars[j]->value.typ == 's') {
            free((void *)(vars[j]->value.sval));
         }
         free(vars[j]);
         vars[j] = NULL;
      }
      if (vars[j] == NULL) {
         vars[j] = (Var *)malloc(sizeof(Var));
         vars[j]->name = strdup(p);
         vars[j]->value = value;
         if (value.typ == 'r') {
            vars[j]->value.rval = new Rational(*value.rval);
         }
         else if (value.typ == 's') {
            vars[j]->value.sval = strdup(value.sval);
         }
         return 1;
      }
   }
   return 0;
}

int set_value(const char *p, Tree *result) {
   Val value;
   switch (result->op) {
      case YYDOUBLE:
         value.typ = 'd';
         value.dval = result->dval;
         break;
      case YYINTEGER:
         value.typ = 'i';
         value.ival = result->ival;
         break;
      case YYRATIONAL:
         value.typ = 'r';
         value.rval = result->rval;
         break;
      case YYSTRING:
         value.typ = 's';
         value.sval = result->sval;
         break;
      default:
         fprintf(stderr, "INTERNAL ERROR %s:%d\n", __FILE__, __LINE__);
         break;
   }
   return set_value(p, value);
}

const Val *get_value(const char *p) {
   unsigned long h = hash(p);

   for (unsigned long i = 0; i < HASH_SIZE; i++) {
      unsigned long j = (i + h) % HASH_SIZE;
      if (vars[j] != NULL && !strcmp(p, vars[j]->name)) {
         return &(vars[j]->value);
      }
   }
   return NULL;
}

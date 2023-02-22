#ifndef _INCLUDE_RUNTIME_LBLS_H_
#define _INCLUDE_RUNTIME_LBLS_H_

#include "tree.h"
typedef struct Lbl {
   char *name;
   Tree *tree;
} Lbl;

int is_lbl_defined(const char *p);

int set_label(const char *p, Tree *n);

Tree *get_label(const char *p);

#endif

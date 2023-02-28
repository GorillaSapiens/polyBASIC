#ifndef _INCLUDE_RUNTIME_LBLS_H_
#define _INCLUDE_RUNTIME_LBLS_H_

#include "tree.hpp"

int is_lbl_defined(const char *p);
int set_label(Tree *n);
Tree *get_label(const char *p);

#endif

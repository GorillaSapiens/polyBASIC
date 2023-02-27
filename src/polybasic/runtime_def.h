#ifndef _INCLUDE_RUNTIME_DEF_H_
#define _INCLUDE_RUNTIME_DEF_H_

#include "tree.h"

int is_def_defined(const char *p);

int set_def(Tree *n);

Tree *get_def(const char *p);

#endif

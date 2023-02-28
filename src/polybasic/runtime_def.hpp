#ifndef _INCLUDE_RUNTIME_DEF_H_
#define _INCLUDE_RUNTIME_DEF_H_

#include "tree.hpp"

int is_def_defined(const char *p);
int set_def(Tree *n);
Tree *get_def(const char *p);
void def_check_cycle(void);

#endif

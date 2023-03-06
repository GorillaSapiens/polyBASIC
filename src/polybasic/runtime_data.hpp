#ifndef _INCLUDE_RUNTIME_DATA_H_
#define _INCLUDE_RUNTIME_DATA_H_

#include <stdint.h>
#include "tree.hpp"
#include "rational.hpp"

void add_data(const Value &val);

int get_data(Value &val);

void rewind_data(void);

#endif

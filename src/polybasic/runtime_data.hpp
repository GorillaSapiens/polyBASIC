#ifndef _INCLUDE_RUNTIME_DATA_H_
#define _INCLUDE_RUNTIME_DATA_H_

#include <stdint.h>
#include "rational.hpp"

void add_data(double d);
void add_data(int64_t i);
void add_data(Rational *r);
void add_data(const char *s);

char next_data_type(void);

int get_data(double &d);
int get_data(int64_t &i);
int get_data(Rational *&r);
int get_data(const char *&s);

void rewind_data(void);

#endif

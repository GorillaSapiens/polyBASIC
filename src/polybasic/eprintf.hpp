#ifndef _INCLUDE_EMIT_H_
#define _INCLUDE_EMIT_H_

#include <stdarg.h>

#define FTOKEN(x, y) x, y
#define FTOKEN2(x, y) FTOKEN(x, y)
#define GURU guru(FTOKEN2(__FILE__, __LINE__))

// set this true to enable guru meditations
extern bool guru_enabled;
void guru(const char *fname, int line);

void add_error(const char *tag, const char *types, const char *format);
void eprintf(const char *tag, ...);

#endif

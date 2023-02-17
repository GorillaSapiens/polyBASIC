#ifndef _INCLUDE_EMIT_H_
#define _INCLUDE_EMIT_H_

#include <stdarg.h>

void add_error(const char *tag, const char *types, const char *format);
void eprintf(const char *tag, ...);

#endif

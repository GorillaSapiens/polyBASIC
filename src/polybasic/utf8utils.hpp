#ifndef _INCLUDE_UTF8UTILS_H_
#define _INCLUDE_UTF8UTILS_H_

#include <stdint.h>

int utf8casecmp(const char *l, const char *r);

// caution, returns pointer to static buffer
const char *int2utf8(int64_t ord);

#endif

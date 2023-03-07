#ifndef _INCLUDE_FLEXDEBUG_H_
#define _INCLUDE_FLEXDEBUG_H_

extern bool flexdebug_enabled;
void flexdebug(const char *text, int token, int line, int col);

#endif

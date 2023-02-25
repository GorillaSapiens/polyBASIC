#ifndef _INCLUDE_FLEXDEBUG_H_
#define _INCLUDE_FLEXDEBUG_H_

extern int flexdebug_enable;
void flexdebug(const char *token, int yytt, int line, int col);

#endif

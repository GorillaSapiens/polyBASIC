#ifndef _INCLUDE_SSTRDUP_H_
#define _INCLUDE_SSTRDUP_H_

static char *safe_strdup(const char *x) {
   return (x == NULL) ? NULL : strdup(x);
}

#define strdup(x) safe_strdup(x)

#endif //_INCLUDE_SSTRDUP_H_


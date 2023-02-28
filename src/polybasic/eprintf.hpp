#ifndef _INCLUDE_EMIT_H_
#define _INCLUDE_EMIT_H_

#include "tree.hpp"
#include "rational.hpp"

#define FTOKEN(x, y) x, y
#define FTOKEN2(x, y) FTOKEN(x, y)
#define GURU guru(FTOKEN2(__FILE__, __LINE__))

// set this true to enable guru meditations
extern bool guru_enabled;
void guru(const char *fname, int line);

class EprintfArg {
      char *data;
   public:
      EprintfArg(void);
      EprintfArg(int i);
      EprintfArg(int64_t li);
      EprintfArg(const char *s);
      EprintfArg(Rational *r);
      EprintfArg(Tree *t);
      EprintfArg(double d);
      ~EprintfArg();
      const char *c_str(void) { return data; };
};

void eprintf(const char *tag,
               EprintfArg arg0 = EprintfArg(),
               EprintfArg arg1 = EprintfArg(),
               EprintfArg arg2 = EprintfArg(),
               EprintfArg arg3 = EprintfArg(),
               EprintfArg arg4 = EprintfArg(),
               EprintfArg arg5 = EprintfArg(),
               EprintfArg arg6 = EprintfArg(),
               EprintfArg arg7 = EprintfArg(),
               EprintfArg arg8 = EprintfArg(),
               EprintfArg arg9 = EprintfArg());

void add_error(const char *format, const char *translation);

#endif

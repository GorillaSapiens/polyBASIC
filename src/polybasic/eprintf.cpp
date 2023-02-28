#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <math.h>
#include <unordered_map>
#include <string>

#include "eprintf.hpp"

using namespace std;

bool guru_enabled= false;

void guru(const char *fname, int line) {
   if (guru_enabled) {
      fprintf(stderr, "GURU: %s:%d\n", fname, line);
   }
}

EprintfArg::EprintfArg(void) {
   data = NULL;
}

EprintfArg::EprintfArg(int i) {
   int len = snprintf(NULL, 0, "%d", i);
   data = (char *) malloc(len + 1);
   sprintf(data, "%d", i);
}

EprintfArg::EprintfArg(int64_t li) {
   int len = snprintf(NULL, 0, "%ld", li);
   data = (char *) malloc(len + 1);
   sprintf(data, "%ld", li);
}

EprintfArg::EprintfArg(const char *s) {
   data = strdup(s);
}

EprintfArg::EprintfArg(Rational *r) {
   char buf[1024];
   r->shortprint(buf, sizeof(buf));
   data = strdup(buf);
}

EprintfArg::EprintfArg(Tree *t) {
   char buf[1024];
   sprintf(buf, "%p", t);
   data = strdup(buf);
}

EprintfArg::EprintfArg(double d) {
   int len = snprintf(NULL, 0, "%f", d);
   data = (char *) malloc(len + 1);
   sprintf(data, "%f", d);
}

EprintfArg::~EprintfArg() {
   if (data) {
      free(data);
   }
}

static unordered_map<string, string> errmap;

void add_error(const char *format, const char *translation) {
   errmap[format] = translation;
}

static int epfh(char *out, EprintfArg &arg) {
   const char *str = arg.c_str();
   int ret = 0;
   if (str) {
      ret = strlen(str);
      strcpy(out, str);
   }
   return ret;
}

void eprintf(const char *format,
   EprintfArg arg0,
   EprintfArg arg1,
   EprintfArg arg2,
   EprintfArg arg3,
   EprintfArg arg4,
   EprintfArg arg5,
   EprintfArg arg6,
   EprintfArg arg7,
   EprintfArg arg8,
   EprintfArg arg9) {

   string translation;
   char output[4096];
   char *out = output;

   if (errmap.find(format) == errmap.end()) {
      translation = format;
   }
   else {
      translation = errmap[format];
   }

   const char *in = translation.c_str();

   while (*in) {
      if (*in != '%') {
         *out++ = *in++;
      }
      else {
         in++;
         if (*in == 'n') {
            *out++ = '\n';
            in++;
         }
         else if (*in == 't') {
            *out++ = '\t';
            in++;
         }
         else if (*in == 'b') {
            *out++ = ' ';
            in++;
         }
         else if (*in < '0' || *in > '9') {
            *out++ = *in++;
         }
         else {
            switch (*in) {
               case '0':
                  out += epfh(out, arg0);
                  break;
               case '1':
                  out += epfh(out, arg1);
                  break;
               case '2':
                  out += epfh(out, arg2);
                  break;
               case '3':
                  out += epfh(out, arg3);
                  break;
               case '4':
                  out += epfh(out, arg4);
                  break;
               case '5':
                  out += epfh(out, arg5);
                  break;
               case '6':
                  out += epfh(out, arg6);
                  break;
               case '7':
                  out += epfh(out, arg7);
                  break;
               case '8':
                  out += epfh(out, arg8);
                  break;
               case '9':
                  out += epfh(out, arg9);
                  break;
            }
            in++;
         }
      }
   }
   *out = 0;

   fprintf(stderr, "%s", output);
}

#ifdef STANDALONE_TEST
int main(int argc, char **argv) {
   add_error("hello %0", "goodbye %0");
   eprintf("hello %0", 12);
}
#endif

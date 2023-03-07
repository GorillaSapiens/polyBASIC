#include "tree.hpp"
#include "polybasic.tab.hpp"
#include "flexdebug.hpp"
#include "mapping.hpp"

bool flexdebug_enabled = false;

void flexdebug(const char *text, int token, int line, int col) {
   if (!flexdebug_enabled) {
      return;
   }

   char textbuf[4096];
   const char *in = text;
   char *out = textbuf;

   while (*in) {
      if (*in >= ' ' || *in < 0) {
         *out++ = *in++;
      }
      else {
         *out++ = '\\';
         switch (*in) {
            case 0x07: *out++ = 'a'; break;
            case 0x08: *out++ = 'b'; break;
            case 0x09: *out++ = 't'; break;
            case 0x0a: *out++ = 'n'; break;
            case 0x0b: *out++ = 'v'; break;
            case 0x0c: *out++ = 'f'; break;
            case 0x0d: *out++ = 'r'; break;
            case 0x1b: *out++ = 'e'; break;
            default:
               *out++ = 'x';
               *out++ = "0123456789abcdef"[(*in >> 4) & 0xF];
               *out++ = "0123456789abcdef"[(*in >> 0) & 0xF];
               break;
         }
         in++;
      }
   }
   *out = 0;

   char charbuf[2];
   const char *name;

   if (token >= ' ' && token <= '~') {
      charbuf[0] = token;
      charbuf[1] = 0;
      name = charbuf;
   }
   else {
      for (int i = 0; reserved[i].name; i++) {
         if ((int)reserved[i].token == token) {
            name = reserved[i].name;
            break;
         }
      }
   }

   printf("@%d:%d '%s' => %d %s\n", line, col, textbuf, token, name ? name : "<nil>");
}

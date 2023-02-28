#include "tree.hpp"
#include "polybasic.tab.hpp"
#include "flexdebug.hpp"
#include "mapping.hpp"

int flexdebug_enable = 0;

void flexdebug(const char *s, int yytt, int line, int col) {
   if (!flexdebug_enable) {
      return;
   }

   const char *display = s;
   char displaybuf[128];

   const char *name = NULL;
   char charbuf[2];

   if (s[0] < ' ') {
      displaybuf[0] = 0;
      for (const char *p = s; *p; p++) {
         switch (*p) {
            case 0x07: strcat(displaybuf, "\\a"); break;
            case 0x08: strcat(displaybuf, "\\b"); break;
            case 0x09: strcat(displaybuf, "\\t"); break;
            case 0x0a: strcat(displaybuf, "\\n"); break;
            case 0x0b: strcat(displaybuf, "\\v"); break;
            case 0x0c: strcat(displaybuf, "\\f"); break;
            case 0x0d: strcat(displaybuf, "\\r"); break;
            case 0x1b: strcat(displaybuf, "\\e"); break;
            default:
               sprintf(displaybuf + strlen(displaybuf), "\\x%02x", *p);
               break;
         }
      }
      display = displaybuf;
   }

   if (yytt >= ' ' && yytt <= '~') {
      charbuf[0] = yytt;
      charbuf[1] = 0;
      name = charbuf;
   }
   else {
      for (int i = 0; reserved[i].name; i++) {
         if ((int)reserved[i].token == yytt) {
            name = reserved[i].name;
            break;
         }
      }
   }

   printf("line %d col %d '%s' => %d %s\n", line, col, display, yytt, name ? name : "<nil>");
}

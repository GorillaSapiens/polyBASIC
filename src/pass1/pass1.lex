%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <errno.h>

int directory_exists(const char *path) {
   DIR* dir = opendir(path);
   if (dir) {
      closedir(dir);
      return 1;
   }
   return 0;
}

void load_translations(const char *language) {
   const char *path = getenv("POLYECMA55PATH");
   if (path == NULL) {
      fprintf(stderr,
         "please check POLYECMA55PATH setting.\n");
      exit(-1);
   }
   if (!directory_exists(path)) {
      fprintf(stderr,
         "cannot access directory %s.\n", path);
      exit(-1);
   }

   char full_path[16384];
   snprintf(full_path, sizeof(full_path), "%s/%s.txt", path, language);

   FILE *f = fopen(full_path, "r");
   if (f) {
   }
   else {
      fprintf(stderr,
         "unable to open %s for reading. "
         "please check POLYECMA55 and/or language settings.\n",
         full_path);
      exit(-1);
   }
}

int main(int argc, char **argv) {
   char *language = getenv("POLYECMA55");
   if (language == NULL) {
      if (argc != 3) {
         fprintf(stderr,
            "POLYECMA55 not set, and no language "
            "given on command line.  exiting.\n");
         exit(-1);
      }
      language = argv[1];
   }
   load_translations(language);
}

%}

%%

%%

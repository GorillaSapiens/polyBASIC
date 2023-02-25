#!/usr/bin/env perl

use utf8;
use Encode 'decode';

#binmode(STDOUT, ':utf8');
binmode *STDOUT, ':encoding(UTF-8)';

printf("# mappings from uppercase and titlecase to lowercase\n");
printf("# if there is no mapping, it won't appear here\n");
printf("\n");
printf("typedef struct LCMAP {\n");
printf("   const char *utcase;\n");
printf("   const char *lcase;\n");
printf("} LCMAP;\n");
printf("\n");
printf("LCMAP lcmap[] = {\n");

open FILE, "<UnicodeData.txt";
while (<FILE>) {
   s/[\x0a\x0d]//g;
   @x = split /;/, $_, -1;
   $codevalue = shift @x;
   $titlecase = pop @x;
   $lowercase = pop @x;
   $uppercase = pop @x;
   if (length($lowercase)) {
      $codevalue = chr(hex($codevalue));
      $lowercase = chr(hex($lowercase));
      print "   { \"$codevalue\", \"$lowercase\" },\n";
   }
}
close FILE;

printf("   { NULL, NULL}\n");
printf("};\n");

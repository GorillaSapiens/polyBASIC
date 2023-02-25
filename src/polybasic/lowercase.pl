#!/usr/bin/env perl

use utf8;
use Encode 'decode';

#binmode(STDOUT, ':utf8');
binmode *STDOUT, ':encoding(UTF-8)';

printf("// this file is utf8\n");
printf("// mappings from uppercase and titlecase to lowercase\n");
printf("// if there is no mapping, it won't appear here\n");
printf("\n");
printf("typedef struct LCMAP {\n");
printf("   const char *utcase;\n");
printf("   const char *lcase;\n");
printf("} LCMAP;\n");
printf("\n");
printf("LCMAP lcmap[] = {\n");

%map = ();

# first, the plain old mappings....

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

# second, the complicated stuff...
sub recode($) {
   my $arg = shift @_;
   if (!length($arg)) {
      return "";
   }
   my @x = split / /, $arg;
   foreach my $x (@x) {
      $x = chr(hex($x));
   }
   return join("", @x);
}

open FILE, "<SpecialCasing.txt";
while (<FILE>) {
   s/[\x0a\x0d]//g;
   s/^#.*//g;
   if (length($_)) {
      @x = split /;/,$_;
      $code = shift @x;

      $lower = shift @x;
      $lower =~ s/^[ ]*//g;
      $lower =~ s/[ ]*$//g;

      $title = shift @x;
      $title =~ s/^[ ]*//g;
      $title =~ s/[ ]*$//g;

      $upper = shift @x;
      $upper =~ s/^[ ]*//g;
      $upper =~ s/[ ]*$//g;

      if (length($lower)) {
         $lower = recode($lower);
         $title = recode($title);
         $upper = recode($upper);

         if (length($title) && length($lower)) {
            print "   { \"$title\", \"$lower\" },\n";
         }
         if (length($upper) && length($lower)) {
            print "   { \"$upper\", \"$lower\" },\n";
         }
      }
   }
}
close FILE;

printf("   { NULL, NULL}\n");
printf("};\n");

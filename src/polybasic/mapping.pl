#!/usr/bin/env perl

print "// some reserved words and their tokens\n";
print "static const struct {\n";
print "   const char *name;\n";
print "   enum yytokentype token;\n";
print "} reserved[] = {\n";

$mode = 0;
while (<>) {
   if ($mode == 0) {
      if (/enum yytokentype/) {
         $mode = 1;
      }
   }
   elsif ($mode == 1) {
      $mode = 2;
   }
   elsif ($mode == 2) {
      if ( /}/) {
         $mode = 3;
      }
      else {
         s/[\x0a\x0d]//g;
         s/^[ ]+//g;
         s/ = /=/g;
         s/[, ].*//g;
         ($a,$b) = split /=/;
         $a =~ s/^YY//g;
         print "   { \"$a\", (enum yytokentype) $b },\n";
      }
   }
   elsif ($mode == 3) {
   }
}
print "   { NULL, (enum yytokentype) 0 }\n";
print "};\n";

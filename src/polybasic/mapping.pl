#!/usr/bin/env perl

open FILE, "polybasic.tab.hpp";
@hpp = <FILE>;
close FILE;

open FILE, "polybasic.ypp";
@ypp = <FILE>;
close FILE;

##########
# process ypp
##########

foreach $_ (@ypp) {
   s/[\x0a\x0d]//g;
   s/^[ ]*//g;
   if (/\$\$.op/) {
      s/^.* = //g;
      s/;.*//g;
      s/^YY//g;
      $op = $_;
   }
#   if (/\$\$..val/) {
#      s/ = .*//g;
#      s/^...//g;
#      #print "$op\n";
#      #print "$_\n";
#      if ($_ eq "sval") {
#         $valprint{$op} = "s";
#         #printf("if (!strcmp(opname, \"$op\")) { printf(\"sval=%%s\\n\", root->sval ? root->sval : \"<nil>\"); }\n");
#      }
#      if ($_ eq "ival") {
#         $valprint{$op} = "i";
#         #printf("if (!strcmp(opname, \"$op\")) { printf(\"ival=%%li\\n\", root->ival); }\n");
#      }
#      if ($_ eq "dval") {
#         $valprint{$op} = "d";
#         #printf("if (!strcmp(opname, \"$op\")) { printf(\"dval=%%f\\n\", root->dval); }\n");
#      }
#      if ($_ eq "rval") {
#         $valprint{$op} = "r";
#         #printf("if (!strcmp(opname, \"$op\")) {\n");
#         #printf("   char buf[1024];\n");
#         #printf("   root->rval->print(buf, sizeof(buf));\n");
#         #printf("   printf(\"rval=\\\"%%s\\\"\\n\", buf); }\n");
#      }
#   }
}

##########
# process tab.hpp
##########

print "// some reserved words and their tokens\n";
print "static const struct {\n";
print "   const char *name;\n";
print "   enum yytokentype token;\n";
#print "   char valprint;\n";
print "} reserved[] = {\n";

$mode = 0;
foreach $_ (@hpp) {
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
#         if (defined($valprint{$a})) {
#            print "   { \"$a\", (enum yytokentype) $b, '$valprint{$a}' },\n";
#         }
#         else {
            print "   { \"$a\", (enum yytokentype) $b },\n";
#         }
      }
   }
   elsif ($mode == 3) {
   }
}
#print "   { NULL, (enum yytokentype) 0, '\\0' }\n";
print "   { NULL, (enum yytokentype) 0 }\n";
print "};\n";

#!/usr/bin/env perl

while (<>) {
   s/[\x0a\x0d]//g;
   s/^[ ]*//g;
   if (/\$\$.op/) {
      s/^.* = //g;
      s/;.*//g;
      s/^YY//g;
      $op = $_;
   }
   if (/\$\$..val/) {
      s/ = .*//g;
      s/^...//g;
      #print "$op\n";
      #print "$_\n";
      if ($_ eq "sval") {
         printf("if (!strcmp(opname, \"$op\")) { printf(\"sval=%%s\\n\", root->sval ? root->sval : \"<nil>\"); }\n");
      }
      if ($_ eq "ival") {
         printf("if (!strcmp(opname, \"$op\")) { printf(\"ival=%%li\\n\", root->ival); }\n");
      }
      if ($_ eq "dval") {
         printf("if (!strcmp(opname, \"$op\")) { printf(\"dval=%%f\\n\", root->dval); }\n");
      }
      if ($_ eq "rval") {
         printf("if (!strcmp(opname, \"$op\")) { printf(\"rval=\"); root->rval->print(); printf(\"\\n\");}\n");
      }
   }
}

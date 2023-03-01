#!/usr/bin/env perl

use utf8;
binmode(STDOUT, ":utf8");

open FILE, "template.pbt";
binmode(FILE, ":utf8");
@template = <FILE>;
close FILE;

open FILE, "../polybasic/errs.txt";
binmode(FILE, ":utf8");
@errors = <FILE>;
close FILE;

sub revit($) {
   my $arg = $_[0];
   $arg =~ s/ <= //g;
   $arg = scalar reverse($arg);
   return " <= $arg";
}

foreach $line (@template) {
   $line =~ s/\$LANGUAGE/reverse/g;
   $line =~ s/( <= ([A-Z]+))/revit($1)/ge;
   print $line;
}

foreach $line (@errors) {
   $line =~ s/[\x0a\x0d]//g;
   $reverse = scalar reverse($line);
   print "$line\t$reverse\n";
}

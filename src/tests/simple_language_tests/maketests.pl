#!/usr/bin/env perl

use utf8;
binmode(STDOUT, ":utf8");

@example = (
"10 FOR x := 1 TO 10",
"20 PRINT \"hello world, or 👋 🌎!\", x",
"30 NEXT x",
"40 END");

foreach $file (`ls ../../translations/*.utf8`) {
   chomp $file;
   $file =~ s/[\x0a\x0d]//g;

   $base = $file;
   $base =~ s/^.*\///g;
   $base =~ s/.utf8//g;

   print "=== $base $file\n";

   %t = ();
   $mode = 0;
   open FILE, $file;
   binmode(FILE, ":utf8");
   while (<FILE>) {
      s/^([^ ]+) <= ([^ ]+)/$t{$1}=$2/ge;
   }
   close FILE;

   open FILE, ">$base.bas";
   binmode(FILE, ":utf8");
   foreach $line (@example) {
      @parts = split / /, $line;
      foreach my $part (@parts) {
         if (defined($t{$part})) {
            $part = $t{$part};
         }
      }
      print FILE join(" ", @parts) . "\n";
   }
   close FILE;
}

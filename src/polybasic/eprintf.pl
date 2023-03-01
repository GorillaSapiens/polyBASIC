#!/usr/bin/env perl

use utf8;

binmode(STDOUT, ':utf8');

foreach $file (@ARGV) {
   open FILE, $file;
   binmode(FILE, ':utf8');
   @file = <FILE>;
   close FILE;

   foreach $line (@file) {
      if ($line =~ /eprintf\(/) {
         $contents = $line;
         $contents =~ s/[\x0a\x0d]//g;
         $contents =~ s/^[^\"]*\"//g;
         $contents =~ s/\".*//g;
         $contents =~ s/\{([^\}]+)\}/print "$1\n"/ge;
         #print "$contents\n";
      }
   }
}

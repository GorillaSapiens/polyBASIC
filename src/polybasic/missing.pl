#!/usr/bin/env perl

open FILE, "needed.txt";
while (<FILE>) {
   s/[\x0a\x0d]//g;
   $y = $_;
   `grep -q "$y" runtime.cpp`;
   if ($? >> 8) {
      print "yes $y\n";
   }
   else {
      print "no $y\n";
   }
}
close FILE;

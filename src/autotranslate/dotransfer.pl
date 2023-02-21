#!/usr/bin/env perl

@files = `ls *.txt`;

foreach $file (@files) {
   $file =~ s/[\x0a\x0d]//g;
   if ($file ne "template.txt") {
      print "==== $file\n";
      $docopy = 1;
      if (-e "../translations/$file") {
         $status = system("grep -q \"THIS FILE WAS AUTOMATICALLY GENERATED\" ../translations/$file");
         if ($? >> 8) {
            $docopy = 0;
            print "human copy found, not touching.\n";
         }
         else {
            print "automated copy found, updating.\n";
         }
      }
      else {
         print "no copy found, updating.\n";
      }
      if ($docopy) {
         `cp $file ../translations/`;
      }
   }
}

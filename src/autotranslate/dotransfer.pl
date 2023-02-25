#!/usr/bin/env perl

@files = `ls *.pbt`;

foreach $file (@files) {
   $file =~ s/[\x0a\x0d]//g;
   if ($file ne "template.pbt") {
      print "= $file\t\t";
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

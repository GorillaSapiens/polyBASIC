#!/usr/bin/env perl

use utf8;

open TEMPLATE, "template.txt";
binmode TEMPLATE, ':utf8';
@template = <TEMPLATE>;
close TEMPLATE;

open TRANSLATION, "$ARGV[0]";
binmode TRANSLATION, ':utf8';
@translation = <TRANSLATION>;
close TRANSLATION;

$mode = 0;
foreach $line (@template) {
   if ($mode == 0) {
      if ($line =~ /\[keywords\]/) {
         $mode = 1;
      }
   }
   elsif ($mode == 1) {
      if ($line =~ /\[errors\]/) {
         $mode = 2;
      }
      else {
         $tmp = $line;
         $tmp =~ s/[\x0a\x0d]//g;
         $tmp =~ s/^[ \t]+//g;
         $tmp =~ s/[ \t]+$//g;

         if (length($tmp)) {
            $flag = 0;
            foreach $translation (@translation) {
               if ($translation =~ /^$tmp <= /) {
                  $flag = 1;
               }
            }
            if (!$flag) {
               print "WARNING, no translation for $tmp\n";
            }
         }
      }
   }
   elsif ($mode == 2) {
      $tmp = $line;
      $tmp =~ s/[\x0a\x0d]//g;
      $tmp =~ s/^[ \t]+//g;
      $tmp =~ s/[ \t]+$//g;

      if (length($tmp)) {
         $flag = 0;
         foreach $translation (@translation) {
            if ($translation =~ /^$tmp <= /) {
               $flag = 1;
# TODO FIX check number and type of arguments
            }
         }
         if (!$flag) {
            print "WARNING, no translation for $tmp\n";
         }
      }
   }
}

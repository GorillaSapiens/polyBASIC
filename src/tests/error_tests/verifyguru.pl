#!/usr/bin/env perl

foreach $file (`ls *guru.txt`) {
   $file =~ s/[\x0a\x0d]//g;
   print "====== $file\n";

   open FILE, $file;
   while (<FILE>) {
      s/[\x0a\x0d]//g;
      if (/GURU: /) {
         if (!(/main.cpp/)) {
            $stub = $file;
            $stub =~ s/_guru.txt//g;

            @pieces = split /:/;
            shift @pieces;
            $pieces[0] =~ s/ //g;
            print "$pieces[0]:$pieces[1]\n";
            $pieces[1]++;
            $cmd = "head -$pieces[1] ../../polybasic/$pieces[0] | tail -1";
            @out = `$cmd`;
            foreach my $out (@out) {
               $out =~ s/^[ ]+//g;
            }
            $actual = pop @out;
            print $actual;
            if ($actual =~ / $stub / || $actual =~ / $stub$/) {
               print "MATCH\n";
            }
            else {
               print "FAIL\n";
            }
         }
      }
   }
   close FILE;
}

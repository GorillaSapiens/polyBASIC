#!/usr/bin/env perl

use utf8;
use Data::Dumper;

open FILE, "polybasic.csv";
binmode(FILE, ":utf8");

binmode(STDOUT, ":utf8");

$mode = 0;
while(<FILE>) {
   chomp;
   s/[\x0a\x0d]//g;
   if ($mode == 0) {
      @all = split /,/;
      foreach my $all (@all) {
         $all = lc($all);
      }
      $mode++;
   }
   else {
      @pieces = split /,/;
      foreach my $piece (@pieces) {
        $piece = uc($piece);
        $piece =~ s/ //g;
        $piece =~ s/[^\p{Letter}\p{Number}]//g;
      }

      push @keywords, $pieces[0];

      for ($i = 0; $i <= $#all; $i++) {
#         print "$all[$i]-$pieces[0] = $pieces[$i]\n";
         $all{"$all[$i]-$pieces[0]"} = $pieces[$i];
      }
   }
}

close FILE;

#print Dumper(\%all);

shift @all;

foreach $language(@all) {
   $sharpindex = 1;
   @file = ();

   open TEMPLATE, "<template.pbt";
   binmode(TEMPLATE, ":utf8");
   while (<TEMPLATE>) {
      s/\$LANGUAGE/$language/g;

      foreach $keyword (@keywords) {
         $translate = $all{"$language-$keyword"};
         s/^$keyword <= $keyword/$keyword <= $translate/g;
      }

      if (/err0/) {
         $error = $all{"$language-ERROR"};
         $file = lc($all{"$language-FILE"});
         $line = lc($all{"$language-LINE"});
         $column = lc($all{"$language-COLUMN"});

         s/ERROR/$error/g;
         s/file/$file/g;
         s/line/$line/g;
         s/column/$column/g;
      }

      $sharp = index($_, '#');
      if ($sharp > $sharpindex) {
         $sharpindex = $sharp;
      }
      push @file, $_;
   }
   close TEMPLATE;

   foreach my $line(@file) {
      $sharp = index($line, '#');
      if ($sharp > 1) {
         while ($sharp < $sharpindex) {
            $line =~ s/#/ #/g;
            $sharp++;
         }
      }
   }

   open FILE, ">$language.pbt";
   binmode(FILE, ":utf8");
   print FILE @file;
   close FILE;
}

#!/usr/bin/env perl

@keywords = ();
@errors = ();

use utf8;
use Data::Dumper;

open FILE, "polybasic.tsv";
binmode(FILE, ":utf8");

binmode(STDOUT, ":utf8");

$mode = 0;
while(<FILE>) {
   chomp;
   s/[\x0a\x0d]//g;
   if ($mode == 0) { # skip the first line
      $mode++;
   }
   elsif ($mode == 1) { # the second line has language names
      @all = split /\t/;
      foreach my $all (@all) {
         $all = lc($all);
      }
      $mode++;
   }
   elsif ($mode == 2) { # this section has all the keywords
      $tmp = $_;
      $tmp =~ s/\t//g;
      if (!length($tmp)) {
         $mode++;
         $errnum = 0;
      }
      else {
         @pieces = split /\t/;
         foreach my $piece (@pieces) {
            $piece = uc($piece);
            $piece =~ s/ //g;
            $piece =~ s/[^\p{Letter}\p{Number}]//g;
         }

         push @keywords, $pieces[0];

         for ($i = 0; $i <= $#all; $i++) {
#         print "$all[$i]-$pieces[0] = $pieces[$i]\n";
            if ($all[$i] eq "english") {
               $all{"$all[$i]-$pieces[0]"} = $pieces[$0];
            }
            else {
               $all{"$all[$i]-$pieces[0]"} = $pieces[$i];
            }
         }
      }
   }
   else { # this section has all the error messages
      @pieces = split /\t/;
      push @errors, $pieces[1];

      for ($i = 0; $i <= $#all; $i++) {
       print "$all[$i]-$errnum = $pieces[$i]\n";
         $errr{"$all[$i]-$errnum"} = $pieces[$i];
      }
      $errnum++;
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

#      if (/err0/) {
#         $error = $all{"$language-ERROR"};
#         $file = lc($all{"$language-FILE"});
#         $line = lc($all{"$language-LINE"});
#         $column = lc($all{"$language-COLUMN"});
#
#         s/ERROR/$error/g;
#         s/file/$file/g;
#         s/line/$line/g;
#         s/column/$column/g;
#      }

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

####
   for ($i = 0; $i <= $#errors; $i++) {
      $err = $errors[$i];
      $translate = $errr{"$language-$i"};

      # some translations add spaces after percent signs.  *sigh*
      $translate =~ s/\% / \%/g;

      # some translations make %n %N, reverse that
      $translate =~ s/\%N/\%n/g;

      # some translations do some funky case things
      $translate=~ s/POLYBASICPATH/POLYBASICPATH/ig;
      $translate=~ s/POLYBASICLANG/POLYBASICLANG/ig;

      # and don't get me started on latin.... *sigh*
      if ($language eq "latin") {
         # these have to happen in a specific order...
         $translate =~ s/\%IX/\%9/g;
         $translate =~ s/\%VIII/\%8/g;
         $translate =~ s/\%VII/\%7/g;
         $translate =~ s/\%VI/\%6/g;
         $translate =~ s/\%V/\%5/g;
         $translate =~ s/\%IV/\%4/g;
         $translate =~ s/\%III/\%3/g;
         $translate =~ s/\%II/\%2/g;
         $translate =~ s/\%I/\%1/g;

         $translate =~ s/\%0\%0/\%0/g;
         $translate =~ s/\%1\%1/\%1/g;
         $translate =~ s/\%2\%2/\%2/g;
         $translate =~ s/\%3\%3/\%3/g;
         $translate =~ s/\%4\%4/\%4/g;
         $translate =~ s/\%5\%5/\%5/g;
         $translate =~ s/\%6\%6/\%6/g;
         $translate =~ s/\%7\%7/\%7/g;
         $translate =~ s/\%8\%8/\%8/g;
         $translate =~ s/\%9\%9/\%9/g;
      }

      print FILE "$err\t$translate\n";
   }
####

   close FILE;
}

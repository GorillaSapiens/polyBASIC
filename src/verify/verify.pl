#!/usr/bin/env perl

use utf8;
binmode STDOUT, ':utf8';

$problems = 0;

$translation_file = $ARGV[0];
$template_file = "template.txt";

my %template_keyword_line;
my @template_error;
my @template_error_line;

my %translation_keyword;
my %translation_keyword_line;
my @translation_error;
my @translation_error_line;

# for debugging
sub dump_template_debug() {
   foreach $key(keys(%template_keyword_line)) {
      print "keyword $key line $template_keyword_line{$key}\n";
   }
   foreach $key(keys(%template_error)) {
      print "error $key|$template_error{$key} line $template_error_line{$key}\n";
   }
}

sub dump_translation_debug() {
   foreach $key(keys(%translation_keyword)) {
      print "keyword $key <= $translation_keyword{$key} line $translation_keyword_line{$key}\n";
   }
   foreach $key(keys(%translation_error)) {
      print "error $key|$translation_error{$key} line $translation_error_line{$key}\n";
   }
}

# gather all the keywords and errors from the template file

open TEMPLATE, "$template_file";
binmode TEMPLATE, ':utf8';
@template = <TEMPLATE>;
close TEMPLATE;

$mode = 0;
$lineno = 1;
foreach $line (@template) {
   if ($mode == 0) {
      if ($line =~ /^\[keywords\]/) {
         $mode = 1;
      }
   }
   elsif ($mode == 1) {
      if ($line =~ /^\[errors\]/) {
         $mode = 2;
      }
      else {
         $tmp = $line;
         $tmp =~ s/[\x0a\x0d]//g;
         $tmp =~ s/^[ \t]+//g;
         $tmp =~ s/[ \t]+$//g;

         if (length($tmp)) {
            if (defined($template_keyword_line{$tmp})) {
               print "$template_file DEFINES KEYWORD '$tmp' MULTIPLE TIMES (lines $template_keyword_line{$tmp} and $lineno)\n";
               print"\n";
               $problems++;
            }
            $template_keyword_line{$tmp} = $lineno;
         }
      }
   }
   elsif ($mode == 2) {
      $tmp = $line;
      $tmp =~ s/[\x0a\x0d]//g;
      $tmp =~ s/^[ \t]+//g;
      $tmp =~ s/[ \t]+$//g;

      if (length($tmp)) {
         push @template_error, $tmp;
         push @template_error_line, $lineno;
      }
   }
   $lineno++;
}

# dump_template_debug();

# gather all the keywords and errors from the ttranslation file

open TRANSLATION, "$translation_file";
binmode TRANSLATION, ':utf8';
@translation = <TRANSLATION>;
close TRANSLATION;

$mode = 0;
$lineno = 1;
foreach $line (@translation) {
   if ($mode == 0) {
      if ($line =~ /^\[keywords\]/) {
         $mode = 1;
      }
   }
   elsif ($mode == 1) {
      if ($line =~ /^\[errors\]/) {
         $mode = 2;
      }
      else {
         $tmp = $line;
         $tmp =~ s/[\x0a\x0d]//g;
         $tmp =~ s/#.*//g;
         $tmp =~ s/^[ \t]+//g;
         $tmp =~ s/[ \t]+$//g;

         if (length($tmp)) {
            if (!($tmp =~ / <= /)) {
               print "ODDLY FORMATTED LINE $lineno:\n";
               print "$line\n";
            }
            else {
               ($word, $translation) = split / <= /, $tmp;
               $word =~ s/^[ \t]+//g;
               $word =~ s/[ \t]+$//g;
               $translation =~ s/^[ \t]+//g;
               $translation =~ s/[ \t]+$//g;

               if (length($tmp)) {
                  if (defined($translation_keyword_line{$word})) {
                     print "$translation_file DEFINES KEYWORD '$word' MULTIPLE TIMES (lines $translation_keyword_line{$word} and $lineno)\n";
                     print"\n";
                     $problems++;
                  }
                  $translation_keyword{$word} = $translation;
                  $translation_keyword_line{$word} = $lineno;
               }
            }
         }
      }
   }
   elsif ($mode == 2) {
      $tmp = $line;
      $tmp =~ s/[\x0a\x0d]//g;
      $tmp =~ s/[\t].*$//g;

      if (length($tmp)) {
         push @translation_error, $tmp;
         push @translation_error_line, $lineno;
      }
   }
   $lineno++;
}

#dump_translation_debug();

# now we cross check EVERYTHING!

foreach $key (keys(%template_keyword_line)) {
   if (!defined($translation_keyword_line{$key})) {
      print "KEYWORD '$key' MISSING FROM $translation_file ($template_file:$template_keyword_line{$key})\n";
      print"\n";
      $problems++;
   }
}

foreach $key (keys(%translation_keyword_line)) {
   if (!defined($template_keyword_line{$key})) {
      print "UNEXPECTED KEYWORD '$key' IN $translation_file:$translation_keyword_line{$key}\n";
      print"\n";
      $problems++;
   }
}

for ($i = 0; $i <= $#template_error; $i++) {
   $found = 0;
   for ($j = 0; $j <= $#translation_error; $j++) {
      if ($template_error[$i] eq $translation_error[$j]) {
         $found = 1;
         last;
      }
   }
   if (!$found) {
      print "MISSSING ERROR TRANSLATION LINE $template_error_line[$i] :: $template_error[$i]\n";
      print"\n";
      $problems++;
   }
}

for ($i = 0; $i <= $#translation_error; $i++) {
   $found = 0;
   for ($j = 0; $j <= $#template_error; $j++) {
      if ($template_error[$j] eq $translation_error[$i]) {
         $found = 1;
         last;
      }
   }
   if (!$found) {
      print "UNUSED ERROR TRANSLATION LINE $translation_error_line[$i] :: $translation_error[$i]\n";
      print"\n";
      $problems++;
   }
}

@keys = keys(%translation_keyword);
for ($i = 0; $i <= $#keys; $i++) {
   for ($j = $i + 1; $j <= $#keys; $j++) {
      if ($translation_keyword{$keys[$i]} eq $translation_keyword{$keys[$j]}) {
         print "TRANSLATION COLLISION\n";
         print "   $keys[$i] <= $translation_keyword{$keys[$i]} # $translation_file:$translation_keyword_line{$keys[$i]}\n";
         print "   $keys[$j] <= $translation_keyword{$keys[$j]} # $translation_file:$translation_keyword_line{$keys[$j]}\n";
         print "\n";
         $problems++;
      }
   }
}

sub errorcomparisonprint($$) {
   my ($key, $match) = @_;

   my $bold = "[31;1m";
   my $unbold = "[0m";

   $te = "$template_file:$template_error_line{$key}";
   $tr = "$translation_file:$translation_error_line{$key}";

   while (length($te) < length($tr)) {
      $te .= " ";
   }
   while (length($tr) < length($te)) {
      $te .= " ";
   }

   print "   $te $key|$template_error{$key}\n";
   $l2 = "   $tr $key|$translation_error{$key}\n";
   $l2 =~ s/$match/$bold$match$unbold/g;
   print $l2;
}

sub verifyintemplate($$) {
   my ($match, $key) = @_;

   if (!($template_error{$key} =~ /$match/)) {
      print "ERROR MISMATCH '$match' NOT FOUND IN $template_file:$template_error_line{$key}\n";
      errorcomparisonprint($key, $match);
      print("\n");
      $problems++;
   }
}

foreach $key (keys(%template_error_line)) {
   if (defined($translation_error_line{$key})) {
      $template_error = $template_error{$key};
      $translation_error = $translation_error{$key};

      $tmp = $translation_error;
      $tmp =~ s/(\{[0-9][ifcs]\})/verifyintemplate($1,$key)/ge;
   }
}

if ($problems) {
   print "----------\n";
   $pedanticplural = "";
   if ($problems > 1) { $pedanticplural = "S"; }
   print "$problems PROBLEM$pedanticplural FOUND.\n";
   exit -1;
}
else {
   print "DONE, NO PROBLEMS FOUND.\n";
   exit 0;
}

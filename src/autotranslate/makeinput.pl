#!/usr/bin/env perl

use utf8;
binmode(STDOUT, ":utf8");

%languages = (
   "en" => "ENGLISH",
   "ko" => "KOREAN",
   "fr" => "FRENCH",
   "de" => "GERMAN",
   "zh" => "CHINESE",
   "es" => "SPANISH",
   "ar" => "ARABIC",
   "ru" => "RUSSIAN",
   "hi" => "HINDI",
   "bn" => "BENGALI",
   "pt" => "PORTUGUESE",
   "in" => "INDONESIAN",
   "ja" => "JAPANESE",
   "he" => "HEBREW",
   "eo" => "ESPERANTO",
   "sw" => "SWAHILI",
   "tl" => "TAGOLOG",
   "ur" => "URDU",
   "la" => "LATIN",
   "cy" => "WELSH",
   "zu" => "ZULU",
   "yi" => "YIDDISH",
);

open FILE, "<template.utf8" or die "could not open template.utf8";
binmode(FILE, ":utf8");
@template = <FILE>;
close FILE;

foreach $line (@template) {
   $line =~ s/[\x0a\x0d]//g;
   if ($line =~ /^[^ ]+ <= /) {
      $tmp = $line;
      $tmp =~ s/ .*//g;
      push @keywords, $tmp;
   }
}

open FILE, "<../polybasic/errs.utf8" or die "could not open errs.utf8";
binmode(FILE, ":utf8");
@errs = <FILE>;
close FILE;

foreach my $err(@errs) {
   $err =~ s/[\x0a\x0d]//g;
}

$maxx = 0;
$maxy = 0;
sub put($$$) {
   my ($x, $y, $v) = @_;
   $output{"$x,$y"} = $v;
   if ($x > $maxx) { $maxx = $x; }
   if ($y > $maxy) { $maxy = $y; }
}

#####
# build our spreadsheet
#####

#####
# leftmost column
#####
put(0,0, "abbr");
put(0,1, "language");

$y = 2;
foreach $keyword(sort(@keywords)) {
   put(0,$y++,$keyword);
}
$y++;
foreach $error(sort(@errs)) {
   put(0,$y++,$error);
}

#####
# one column for each language
#####
$x = 1;
foreach my $abbr (sort(keys(%languages))) {
   put($x,0, $abbr);
   put($x,1, $languages{$abbr});

   @exceptions = ();
   if (-e "exceptions/$abbr.tsv") {
      open FILE, "<exceptions/$abbr.tsv" or die "could not open exceptions/$abbr.tsv";
      @exceptions = <FILE>;
      close FILE;
      foreach my $exception (@exceptions) {
         $exception =~ s/[\x0a\x0d]//g;
      }
   }

   $y = 2;
   # keywords
   foreach $keyword(sort(@keywords)) {
      if ($abbr eq "en") {
         put($x, $y, $keyword);
      }
      else {
         $found = 0;
         foreach $exception(@exceptions) {
            ($src, $lang, $dst) = split /\t/, $exception;
            if ($src eq $keyword) {
               $found = 1;
               if ($lang eq $abbr) {
                  put($x,$y,"$dst");
               }
               else {
                  put($x,$y,"=upper(googletranslate(\"$dst\", \"$lang\", \"$abbr\"))");
               }
            }
         }
         if (!$found) {
            put($x,$y,"=upper(googletranslate(\"$keyword\", \"en\", \"$abbr\"))");
         }
      }
      $y++;
   }

   $y++;
   # errors
   foreach $error(sort(@errs)) {
      if ($abbr eq "en") {
         put($x, $y, $error);
      }
      else {
         $found = 0;
         foreach $exception(@exceptions) {
            ($src, $lang, $dst) = split /\t/, $exception;
            if ($src eq $error) {
               $found = 1;
               if ($lang eq $abbr) {
                  put($x,$y,"$dst");
               }
               else {
                  put($x,$y,"=upper(googletranslate(\"$dst\", \"$lang\", \"$abbr\"))");
               }
            }
         }
         if (!$found) {
            put($x,$y,"=upper(googletranslate(\"$error\", \"en\", \"$abbr\"))");
         }
      }
      $y++;
   }
   $x++;
}

#####
# final output
#####
for ($y = 0; $y <= $maxy; $y++) {
   for ($x = 0; $x <= $maxx; $x++) {
      if (defined($output{"$x,$y"})) {
         print $output{"$x,$y"} . "\t";
      }
   }
   print "\n";
}


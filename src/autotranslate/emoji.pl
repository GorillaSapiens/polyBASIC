#!/usr/bin/env perl

use utf8;
binmode(STDOUT, ":utf8");

$en_freq = "ETAINOSHRDLUCMFWYGPBVKQJXZ";
$em_letters = "🍆🍑🍒🍌🍓🍄🍎🥥🍉🍇✨🔥🍔🍟🍕🌭🥪🌮🦍💥💫💦💨🐻🐨🐼";

@en_freq = split //, $en_freq;
@em_letters = split //, $em_letters;

while ($#en_freq >= 0) {
   $english = shift @en_freq;
   $emoji = shift @em_letters;
   $translate{$english} = $emoji;
}

sub toemoji($) {
   my $arg = shift @_;
   my @chars = split //, $arg;
   my $ret = "";

   foreach my $char (@chars) {
      if (defined($translate{$char})) {
         $ret .= $translate{$char};
      }
      else {
         $ret .= $char;
      }
   }

   return $ret;
}

$language = toemoji("EMOJI");

open FILE, "template.utf8";
binmode(FILE, ":utf8");
@template = <FILE>;
close FILE;

open FILE, "../polybasic/errs.utf8";
binmode(FILE, ":utf8");
@errors = <FILE>;
close FILE;

sub emojiit($) {
   my $arg = $_[0];
   $arg =~ s/ <= //g;
   $arg = toemoji($arg);
   return " <= $arg";
}

foreach $line (@template) {
   $line =~ s/\$LANGUAGE/$language/g;
   $line =~ s/( <= ([A-Z]+))/emojiit($1)/ge;
   print $line;
}

foreach $line (@errors) {
   $line =~ s/[\x0a\x0d]//g;
   $emojified = $line;
   $emojified =~ s/([A-Z]+)/toemoji($1)/ge;
   print "$line\t$emojified\n";
}

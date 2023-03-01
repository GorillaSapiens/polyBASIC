#!/usr/bin/env perl

use utf8;
binmode(STDOUT, ":utf8");

$language = "🍆🍑🍒🍌🍓🍄🍎🥥🍉🍇";
@alphabet = split //, "$language";

sub toemoji($) {
   my $arg = shift @_;

   my $value = 5381;
   my @chars = split //, $arg;

   foreach my $char (@chars) {
      $value = (($value << 5) + $value) ^ ord($char);
   }

   $value %= 10000;
   my $ret = "";
   while ($value > 0) {
      $ret .= $alphabet[$value % length($language)];
      $value = int($value / length($language));
   }

   return $ret;
}

open FILE, "template.pbt";
binmode(FILE, ":utf8");
@template = <FILE>;
close FILE;

open FILE, "../polybasic/errs.txt";
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

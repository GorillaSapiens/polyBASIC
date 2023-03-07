#!/usr/bin/env perl

sub compress($) {
   my $arg = shift @_;
   $n = $#str + 1;
   push @str, $arg;
   return " ___$n\___ ";
}

sub xform($) {
   my $arg = shift @_;
   $arg =~ s/[^0-9]//g;
   return $str[$arg];
}

sub uncompress($) {
   my $arg = shift @_;
   $arg =~ s/(___[0-9]+___)/xform($1)/ge;
   return $arg;
}

sub handle_subprint($) {
   my $arg = shift @_;
   $needcolon = 0;
   if ($arg =~ /:$/) {
      $needcolon = 1;
      $arg =~ s/:$//g;
   }
   $arg =~ s/^PRINT//g;

   #print "### $arg\n";
   if ($arg =~ /___[0-9]+___[^,;]+___[0-9]+___/) {
      $arg =~ s/(___[0-9]+___)([^,;]+)(___[0-9]+___)/"$1;$2;$3"/ge;
      #print ">>> $arg\n";
   }
   if ($arg =~ /___[0-9]+___[ ]*[^,;]+[ ]*[;,][ ]*___[0-9]+___/) {
      $arg =~ s/(___[0-9]+___)([ ]*[^,;]+[ ]*[;,][ ]*)(___[0-9]+___)/"$1;$2$3"/ge;
      #print "||| $arg\n";
   }
   if ($arg =~ /___[0-9]+___[ ]*[;,][ ]*[^,;]+[ ]*___[0-9]+___/) {
      $arg =~ s/(___[0-9]+___)([ ]*[;,][ ]*[^,;]+[ ]*)(___[0-9]+___)/"$1$2;$3"/ge;
      #print "/// $arg\n";
   }
   if ($arg =~ /^[ ]*[^ ;]+[ ]*___[0-9]+___/) {
      $arg =~ s/^([ ]*[^ ;]+[ ]*)(___[0-9]+___)/"$1;$2"/ge;
      #print "+++ $arg\n";
   }
   if ($arg =~ /___[0-9]+___[ ]*[^ ;,]+[ ]*$/) {
      $arg =~ s/(___[0-9]+___)([ ]*[^ ;,]+[ ]*)$/"$1;$2"/ge;
      #print "--- $arg\n";
   }

   if ($needcolon) {
      $arg = "$arg:";
   }
   return "PRINT $arg";
}

sub handle_print($) {
   my $arg = shift @_;

   # first, compress strings...
   @str = ();

   $arg =~ s/(\"[^\"]*\")/compress($1)/ge;

   $arg =~ s/((PRINT[^:]*:)|(PRINT[^:]*$))/handle_subprint($1)/ge;

   $arg = uncompress($arg);

   return $arg;
}

foreach $file (`ls *.obas`) {
   $file =~ s/[\x0a\x0d]//g;
   $base = $file;
   $base =~ s/\..*//g;

   print "=== $file $base\n";

   open IN, "<$file";
   open OUT, ">$base.bas";

   while (<IN>) {
      s/[\x0a\x0d]//g;
      s/^([0-9]+[ ]+)REM([^ ])/"$1REM $2"/ge;

      if (!(/^[0-9]+[ ]+REM/)) {
         if (/PRINT/) {
            $_ = handle_print($_);
         }
      }

      print OUT "$_\n";
   }

   close IN;
   close OUT;
}

#!/usr/bin/env perl

foreach $builtin (`grep ^BUILTINFUNC runtime.cpp`) {
   $builtin =~ s/[\x0a\x0d]//g;
   $builtin =~ s/.*\(//g;
   $builtin =~ s/\).*//g;
   $builtin =~ s/ //g;

   ($name, $args) = split /,/, $builtin;

   print "   { \"$name\", $args, builtin_$name },\n";
}

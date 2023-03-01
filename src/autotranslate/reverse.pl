#!/usr/bin/env perl

while (<>) {
   s/([A-Za-z]+)/scalar reverse($1)/ge;
   print $_;
}

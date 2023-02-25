#!/bin/sh

# exit on any error
set -e

for each in `ls ../translations`
do

echo -n "= VERIFY $each :	"
./verify.pl ../translations/$each

done

echo ======= TRANSLATION TABLES VERIFIED FOR CONSISTENCY

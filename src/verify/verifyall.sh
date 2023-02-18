#!/bin/sh

# exit on any error
set -e

for each in `ls ../translations`
do

echo ======= $each
./verify.pl ../translations/$each

done

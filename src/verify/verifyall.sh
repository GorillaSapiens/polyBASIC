#!/bin/sh

for each in `ls ../translations`
do

echo ======= $each
./verify.pl ../translations/$each

done

#!/bin/sh

export PATH=$PATH:../../polybasic
export POLYBASICPATH=../../translations

for file in `ls *.bas`
do
   base=`basename -s .bas $file`
   echo ===== $base
   polybasic -g -l english $base.bas > $base\_guru.txt 2>&1
   polybasic -l english $base.bas > $base\_actual.txt 2>&1
   DIFF=$(diff -q $base\_expected.txt $base\_actual.txt)
   if [ "$DIFF" ]
   then
      echo FAIL
      exit 1
   else
      echo PASS
   fi
done

exit 0

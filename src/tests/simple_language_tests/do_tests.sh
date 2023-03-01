#!/bin/sh

export PATH=$PATH:../../polybasic
export POLYBASICPATH=../../translations

for file in `ls *.bas`
do
   base=`basename -s .bas $file`
   echo ===== $base
   polybasic -l $base $base.bas 2>&1 > $base\_actual.txt
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

#!/bin/sh

export PATH=$PATH:../../polybasic
export POLYBASICPATH=../../translations

if [ ! -e "../../polybasic/polybasic" ]
then
   echo "polybasic executable missing!";
   exit 1;
fi

for file in `ls *.bas`
do
   base=`basename -s .bas $file`
   echo ===== $base
   polybasic -0 -g -l english $base.bas > $base\_guru.txt 2>&1 < /dev/null
   polybasic -0 -l english $base.bas > $base\_actual.txt 2>&1 < /dev/null

   if [ ! -e $base\_expected.txt ]
   then
      echo WARNING! COPYING ACTUAL TO EXPECTED!
      cp $base\_actual.txt $base\_expected.txt
   fi

   DIFF=$(diff -q $base\_expected.txt $base\_actual.txt)
   if [ "$DIFF" ]
   then
      diff -uprN $base\_expected.txt $base\_actual.txt
      echo FAIL
      exit 1
   else
      echo PASS
   fi
done

exit 0

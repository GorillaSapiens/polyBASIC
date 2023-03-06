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

   if ! polybasic -u -l english $base.bas > $base\_actual.txt 2>&1 < /dev/null
   then
      cat $base\_actual.txt
      exit 1
   fi

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
      echo to fix: cp $base\_actual.txt $base\_expected.txt
      exit 1
   else
      echo PASS
   fi
done

exit 0

#!/bin/sh

export PATH=$PATH:../../polybasic
export POLYBASICPATH=../../translations

echo ================== english test
polybasic -l english english.bas > english_actual.txt
DIFF=$(diff -q english_expected.txt english_actual.txt)
if [ "$DIFF" ]
then
   echo FAIL
   exit 1
else
   echo PASS
fi

echo ================== reverse test
polybasic -l reverse reverse.bas > reverse_actual.txt
DIFF=$(diff -q reverse_expected.txt reverse_actual.txt)
if [ "$DIFF" ]
then
   echo FAIL
   exit 1
else
   echo PASS
fi

echo ================== emoji test
polybasic -l emoji emoji.bas > emoji_actual.txt
DIFF=$(diff -q emoji_expected.txt emoji_actual.txt)
if [ "$DIFF" ]
then
   echo FAIL
   exit 1
else
   echo PASS
fi

exit 0

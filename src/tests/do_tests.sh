#!/bin/sh

export POLYBASICPATH=../translations
echo ================== english test
../polybasic/polybasic -l english english.bas
echo ================== reverse test
../polybasic/polybasic -l reverse reverse.bas
echo ================== emoji test
../polybasic/polybasic -l emoji emoji.bas

#!/bin/sh
CONFIGFIX="../configfix"
echo "Assuming configfix is located at $CONFIGFIX"
if [ ! -f "$CONFIGFIX" ]
then
  echo "Executable not found!"
  exit 1
fi
cp testdata.txt out2.txt
cp testdata.txt out3.txt
echo " == Test 1 ======="
$CONFIGFIX -f - < testdata.txt > out1.txt
echo " == Test 2 ======="
$CONFIGFIX -f out2.txt
echo " == Test 3 ======="
$CONFIGFIX out3.txt
md5sum -c valid-checksums.txt
rm out*.txt out*.txt.bak

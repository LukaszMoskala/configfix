#!/bin/sh
CONFIGFIX="../configfix"
echo "Assuming configfix is located at $CONFIGFIX"
if [ ! -f "$CONFIGFIX" ]
then
  echo "Executable not found!"
  exit 1
fi
echo "Example config file before cleaning:"
echo "=========================================="
cat testdata.txt
echo "=========================================="
echo "After cleaning: "
echo "=========================================="
cat testdata.txt | $CONFIGFIX -f -
echo "=========================================="

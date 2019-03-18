#!/bin/sh
CONFIGFIX="../configfix"
echo "Assuming configfix is located at $CONFIGFIX"
echo "Example config file before cleaning:"
echo ""
cat testdata.txt
echo ""
echo "After cleaning: "
echo ""
cat testdata.txt | $CONFIGFIX -f -

#!/bin/gawk

#BEGIN {print "hello world\n"}

/# NOISE/ { printf $8 }
/work\/transmit/ { printf "\t" $7 "\t" $8 }
/Block counts:/  { printf "\t" $14/100 }
/Bit error rate/ { printf "\t" $8 "\n" }
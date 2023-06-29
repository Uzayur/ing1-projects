#!/bin/sh

cd ../../..
cut ~/.bash_history -d " " -f 1 | sort | uniq -c | tr -s ' '| sort -nr |  head -10 | cut -d " " -f 2,3
exit 0

#!/bin/sh

if [ "$#" -eq 0 ]; then
    echo
else
    count=0
    string=""
    delim=,
    for var in "$@"; do
        if [ $count -eq 0 ]; then
            string=$string$var
        else
            string="$string$delim"
            string="$string$var"
        fi
        count=$(($count+1))
    done
    echo "$string" | tr --delete "rR"
fi

#!/bin/sh

if [ "$#" -ne 1 ]; then
    exit 1
elif ! [ -e "$1" ]; then
    exit 1
fi

while IFS= read -r line; do
    length=`echo "$line" | wc -m`
    if [ $length -gt 80 ]; then
        printf "%s\n" "$line"
    fi
done < "$1"

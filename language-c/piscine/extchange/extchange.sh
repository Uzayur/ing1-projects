#!/bin/sh

if [ "$#" -ne 2 ]; then
    echo Usage: extchange.sh "'ext1'" "'ext2'" >&2
    exit 1
fi

value=0
for file in *.$1; do
    if [ $file = "*."$1"" ]; then
        exit 2
    fi
    value=$(($value+1))
    mv $file $(echo $file | cut -d "." -f 1)."$2"
    echo mv $file $(echo $file | cut -d "." -f 1)."$2"
done

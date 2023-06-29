#!/bin/sh

if [ "$#" -ne 3 ]; then
    echo Usage: ./seq.sh FIRST INCREMENT LAST >/dev/stderr
    exit 1
elif [ "$1" -lt "$3" ] && [ "$2" -lt 0 ]; then
    exit 1
elif [ "$1" -gt "$3" ] && [ "$2" -gt 0 ]; then
    exit 1
elif [ "$1" -eq "$3" ]; then
    echo "$1"
    exit 0
elif [ "$2" -eq 0 ]; then
    exit 1
elif [ "$1" -lt "$3" ]; then
    value="$1"
    while [ "$value" -le "$3" ]; do
	echo "$value"
	value="$(($value+$2))"
    done
    exit 0
else
    value="$1"
    while [ "$value" -ge "$3" ]; do
	echo "$value"
	value="$(($value+$2))"
    done
    exit 0
fi


#!/bin/sh

for var in "$@"
do
    echo -n "$var"
    echo -n ": "
    if [ -f "$var" ]; then
	echo file
    else
	if [ -d "$var" ]; then
	    echo directory
	else
	    echo unknown
	fi
    fi
done

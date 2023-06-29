#!/bin/sh


if [ $# -eq 0 ]; then
	exit 1
else
	if [ $1 -lt 0 ]; then
		exit 2
	else
		number=$1
		shift
		for i in $*; do
			for k in $(seq 1 $number); do
				echo "$i"
			done
		done
		exit 0
	fi
fi

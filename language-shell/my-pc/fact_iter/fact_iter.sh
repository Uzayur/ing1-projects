#!/bin/sh

if [ $# -eq 1 ]; then
	num=$*
	var=1
	while [ $num -gt 1 ]; do
		var=$(($var*$num))
		num=$(($num-1))
	done
	echo "$var"
else
	exit 1
fi

#!/bin/sh

if [ $# -ne 1 ]; then
	echo "Sorry, expected 1 argument but "$#" were passed"
	exit 1
else
	if [ -e $* ]; then
		if [ -f $* ]; then
			cat $*
			exit 0
		else
			echo "$*"":"
			printf "\t%s\n" "is not a valid file"
			exit 2
		fi
	else
		echo "$*"":"
		printf "\t%s\n" "is not a valid file"
		exit 2
	fi
fi

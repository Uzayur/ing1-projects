#!/bin/sh

cd ./../../../../../etc
cut -f 3 -d ':' passwd | sort -n -r -u

exit 0

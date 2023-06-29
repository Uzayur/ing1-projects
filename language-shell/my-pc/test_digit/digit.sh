#!/bin/sh

while [ "$#" -ne 0 ]; do
	case "$1" in
		[0-9])
			echo "$1" is a positive digit.
			shift
			;;
		+[0-9])
			echo "$1" is a positive digit.
			shift
			;;
		-[0-9])
			echo "$1" is a negative digit.
			shift
			;;
		*)
			echo -n "$1 "
			shift
			test=0
			while [ "$test" -ne 1 ]; do
				if [ "$#" -eq 0 ]; then
					echo is not a digit.
					break
				else
					case "$1" in
						[0-9])
							test=$(($test+1))
							;;
						*[0-9])
							test=$(($test+1))
							;;
						*)
							echo -n "$1 "
							shift
							;;
					esac
				fi
			done
			if [ "$#" -ne 0 ]; then
				echo is not a digit.
			fi
	esac
done

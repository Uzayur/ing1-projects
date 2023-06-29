#!/bin/sh

while read -r var; do
    val=0
    string=0
    printf "%s" "$var" > $string
    val=$(grep -w -c '[0-9]*' $string)
    if [ $val -eq 1 ];then
        if [ $var -lt 10 ]; then
            printf "it is a digit\n"
            continue;
        else
            printf "it is a number\n"
            continue;
        fi
    fi
    val=$(grep -w -c '[a-zA-Z]*' test1)
    if [ $val -eq 1 ]; then
        printf "it is a word\n"
        continue;
    fi
    val=$(grep -w -c '^[a-zA-Z0-9]*$' test1)
    if [ $val -eq 1 ]; then
        printf "it is an alphanum\n"
        continue;
    else
        break;
    fi
done

exit 0

#!/bin/sh

if [ "$#" -ne 2 ]; then
    exit 0
fi

test_value=0
case "$2" in
    [0-9]*)test_value=$(($test_value+1));;
        *);;
esac
if [ $test_value -ne 1 ]; then
    exit 0
fi

if ! [ -e "$1" ]; then
    exit 0
elif [ "$2" -lt 0 ]; then
    exit 0
elif [ -d "$1" ]; then
    exit 0
fi

file_line=$(wc -l < "$1")

if [ "$2" -gt "$file_line" ]; then
    exit 0
fi

touch test1
cut "$1" -d ";" -f 2,3 > test1

file_line=$(wc -l < test1)

if [ "$file_line" -eq 0 ]; then
    rm test1
    exit 0
elif [ "$file_line" -lt "$2" ]; then
    rm test1
    exit 0
fi

touch test2
head -n "$2" test1 | tail -n 1 > test2

file_line=$(wc -l < test2)
if [ $file_line -eq 0 ]; then
    rm test1
    rm test2
    exit 0
elif [ $file_line -gt 2 ]; then
    rm test1
    rm test2
    exit 0
fi

touch test3

var1=$(cut test2 -d ";" -f 1)
var2=$(cut test2 -d ";" -f 2)

test_value=0
case "$var2" in
    [0-9]*)test_value=$(($test_value+1));;
    *);;
esac
case "$var1" in
    F*)test_value=$(($test_value+1));;
    *);;
esac
if [ $test_value -eq 2 ]; then
    rm test1
    rm test2
    rm test3
    exit 0
fi

echo $var1 is $var2 > test3

value=$(head -n "$2" test3 | tail -n 1)

if [ "$value" = "is" ]; then
    rm test1
    rm test2
    rm test3
    exit 0
fi

echo "$value"

rm test1
rm test2
rm test3
exit 0

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
fi

file_line=$(wc -l < "$1")

if [ $file_line -lt "$2" ]; then
    exit 0
fi

touch test1
touch test2
touch test3

sed -n "$2","$2"p "$1" > test1
sed 's/;/\n/g' test1 > test2

echo `sed -n '2,2p' test2` is `sed -n '3,3p' test2` > test3

sed -n '1,1p' test3

rm test1
rm test2
rm test3
exit 0

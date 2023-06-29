#!/bin/sh

if [ "$#" -ne 2 ]; then
    echo Usage: mix_files file1 file2 >&2
    exit 1
fi

if ! [ -e "$1" ]; then
    exit 1
elif ! [ -e "$2" ]; then
    exit 1
fi

file1_ind=1
file2_ind=1
file1_line=$(wc -l < "$1")
file2_line=$(wc -l < "$2")


file1_line_static=$(wc -l < "$1")
file2_line_static=$(wc -l < "$2")

if [ $file1_line -eq 0 ]; then
    cat "$2"
elif [ $file2_line -eq 0 ]; then
    cat "$1"
fi

if [ $file1_line -gt $file2_line ]; then
    while [ $file2_line -ne 0 ]; do
        head -n $file1_ind "$1" | tail -n 1
        head -n $file2_ind "$2" | tail -n 1
        file1_ind=$(($file1_ind+1))
        file2_ind=$(($file2_ind+1))
        file1_line=$(($file1_line-1))
        file2_line=$(($file2_line-1))
    done
    while [ $file1_line -ne 0 ]; do
        head -n $file1_ind "$1" | tail -n 1
        file1_ind=$(($file1_ind+1))
        file1_line=$(($file1_line-1))
    done
fi

if [ $file2_line -gt $file1_line ]; then
    while [ $file1_line -ne 0 ]; do
        head -n $file1_ind "$1" | tail -n 1
        head -n $file2_ind "$2" | tail -n 1
        file1_ind=$(($file1_ind+1))
        file2_ind=$(($file2_ind+1))
        file1_line=$(($file1_line-1))
        file2_line=$(($file2_line-1))
    done
    while [ $file2_line -ne 0 ]; do
        head -n $file2_ind "$2" | tail -n 1
        file2_ind=$(($file2_ind+1))
        file2_line=$(($file2_line-1))
    done
fi

if [ $file1_line -eq $file2_line ]; then
    while [ $file2_line -ne 0 ]; do
        head -n $file1_ind "$1" | tail -n 1
        head -n $file2_ind "$2" | tail -n 1
        file1_ind=$(($file1_ind+1))
        file2_ind=$(($file2_ind+1))
        file1_line=$(($file1_line-1))
        file2_line=$(($file2_line-1))
    done
fi

exit 0

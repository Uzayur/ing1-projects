#!/bin/sh

touch " "
chmod 0644 " "
touch '\'
chmod 0644 '\'
touch ./--
chmod 0644 ./--
touch "|"
chmod 0644 "|"
touch '"'
chmod 0644 '"'
touch "'"
chmod 0644 "'"
touch ./--'$i*'"'"'"''\'
chmod 0644 ./--'$i*'"'"'"''\'
touch '#'" ""Exams are fun!"
chmod 0644 '#'" ""Exams are fun!"
touch ';`kill -9 0`'
chmod 0644 ';`kill -9 0`'

for i in $(seq 1 50); do
	mkdir $i
	chmod 0644 $i
	cd $i
done
touch 'farfaraway'
chmod 0644 'farfaraway'

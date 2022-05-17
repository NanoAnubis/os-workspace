#!/bin/bash

if ! [ $# -eq 3 ]; then exit 1
fi

first=$(cat $1 | egrep ${2}= | cut -d '=' -f 2)
second=$(cat $1 | egrep ${3}= | cut -d '=' -f 2)
d=$(echo $first $second | tr ' ' '\n' | sort | uniq -d)

for i in $d
do
	second=$(echo $second | tr "\ $i\ " "")
done
echo $first
echo $second

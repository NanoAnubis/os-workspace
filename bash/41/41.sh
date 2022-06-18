#!/bin/bash

if [ ! $# -eq 3 ]; then
	echo "Too few arguments"
	exit 1
fi

if [ ! -f $1 ]; then
	echo "$1 is not a file"
	exit 1
fi

date="$(date)"
user="$(whoami)"

key="\s*$2\s*="
value="=\s*$3\s*"
check=0
tmp="$(mktemp)"

while read line; do
	if [ $check -eq 1 ]; then
		echo $line >> $tmp
		continue
	fi

	search="$(echo $line | cut -d '#' -f 1)"
	
	if [ $(echo $search | grep $key | wc -l) -eq 1 ]; then
		if [ $(echo $search | grep $value | wc -l) -eq 1 ]; then
			check=1
		else
			echo "# $line # editted at $date by $user" >> $tmp
			echo "$2 = $3 # added at $date by $user" >> $tmp
			check=1
			continue
		fi
	fi
	echo $line >> $tmp
done < <(cat $1)
cat $tmp > $1
rm $tmp


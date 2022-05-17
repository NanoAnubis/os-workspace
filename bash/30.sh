#!/bin/bash

dir=$1

if ! [ -d $dir ]
then
	echo "Not a dir"	
	exit 1
fi

tmp=$(mktemp)
find $dir -type f >> $tmp

tmp1=$(mktemp)
while read l
do
	echo "$(echo $l| rev | cut -d '/' -f 2 | rev) $(cat $l | wc -l)" >> $tmp1

done < <(cat $tmp)

cat $tmp1

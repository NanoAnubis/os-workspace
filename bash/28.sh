#!/bin/bash

dir=$1
arch=$2

if ! [ -d $dir ]
then
	exit 1
fi	

tmp=$(mktemp)
find $dir -mindepth 1 -maxdepth 1 -type f -printf "%P\n" >> $tmp 

cat $tmp | egrep "^([[:alpha:]]+)-([0-9]+).([0-9]+).([0-9]+)-$arch" | sort -t '-' -k 2,2 -r | head -n 1



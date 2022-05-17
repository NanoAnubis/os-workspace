#!/bin/bash


file=$(mktemp)

c=1
while read line ; do
	line="${c}.$(echo ${line} | cut -d '-' -f 2-)"
	echo "${line}" >> ${file}
	c=$((${c}+1))
done < <(cat ./books)

cat ${file} | sort -t '"' -k 2,2

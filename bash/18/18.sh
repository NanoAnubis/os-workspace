#!/bin/bash

first=$1
second=$2

mkdir a b c

set $(find . -type f)

while [ $# -gt 0 ] 
do
	if [ "${1}" = "${0}"  ]
	then	
		shift 1
	fi	
	lin="$(cat "${1}" | wc -l)"
	if [ "${lin}" -lt "${first}" ]
	then
		mv "${1}" ./a/
	elif [ "${lin}" -ge "${first}" ] && [ "${lin}" -lt "${second}" ]
	then
		mv "${1}" ./b/
	else
		mv "${1}" ./c/
	fi
	shift 1
done


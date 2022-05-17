#!/bin/bash

max=$1

set $(ps -e -o user| tail -n +2 | sort | uniq)

c=$#

while [ "${c}" -ge 1 ]
do	
	rss="$(echo $(ps -u ${1} -o rss | tail -n +2 | sort -n | tr '\n' ' ' | tr -s ' '| sed 's/\ //' | tr ' ' '+' | rev | sed 's/+//' | rev) | bc)"
	
	echo "${1} ${rss}"

	if [ ${max} -lt ${rss} ]
	then
		echo "kill $(ps -u ${1} -o pid,rss | sort -n -k 2,2 | tail -n 1 | tr -s ' '| cut -d ' ' -f 2)"
	fi



	shift 1
	c=$((${c}-1))
done



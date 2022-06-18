#!/bin/bash
if [ ! $# -eq 3 ]; then
	echo "args"
	exit 1
fi

if [ ! -f $1 ] || [ ! -d $3 ]; then
	echo "wrong formats"
	exit 1
fi

valid="^\{\s.+;?\s\};$"
comment="^#.+"
nl="^$"
rm $2

for file in $(find $3 -type f -name "*.cfg"); do
	result=$(cat $file | egrep -nv "($valid|$comment|$nl)" | awk '{print "Line "$0}')
	if [ ! $(cat $file | egrep -nv "($valid|$comment|$nl)" | awk '{print "Line "$0}' | wc -l) -eq 0 ]; then 
		echo "Error in $(echo $file|rev|cut -d '/' -f 1|rev):"
		echo "$result"
		continue
	fi
	cat $file >> $2
	filename="$(echo $file|rev|cut -d '/' -f 1| rev |cut -d '.' -f 1)"
	if [ $(cat $1| egrep "^$filename:" | wc -l) -eq 0 ]; then
		pass="$(pwgen 16 1)"
		echo "$filename $pass"
		echo "$filename:$(echo $pass|md5sum|cut -d ' ' -f 1)" >> $1
	fi
done

#!/bin/bash

if ! [ -d $1 ] 
then
	exit 2
fi


ok="$(find $1 -type l -xtype f)"
broken="Broken symlinks: $(find $1 -xtype l | wc -l)"
tmp="$(mktemp)"

for l in $ok
do
	echo "$l --> $(file $l | awk '{print $NF}')" >> $tmp

done


case $# in
	1)
		cat $tmp
		echo "$broken"
		;;

	2)
		if [ -f $2 ]
		then
			exit 2
		fi
		cat $ok >> $2
		echo "$broken" >> $2
		;;
	*)
		exit 1
		;;
esac

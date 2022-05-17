#!/bin/bash

c=$#

if ! [ -d $1 ] 
then
	echo "not a dir"
	exit 1
fi

case $c in
	1)
		find $1 -xtype l 
		;;
	2)
		find $1 -type f -links +$(($2-1)) 
		exit 0
		;;
	*)
		echo "too many args"
		exit 2
		;;
esac

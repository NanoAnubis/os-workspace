#!/bin/bash

dir=$1

if [ ! -d "${dir}" ] 
then
	echo "Not a directory!"
	exit 1
fi

find "${dir}" -type l 

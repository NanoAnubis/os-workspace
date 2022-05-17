#!/bin/bash

read -p "Enter directory: " dir
echo "Number of files in $dir: $(find /home/students/s62569/ -type f -maxdepth 1 | wc -l)"
echo "Number of directories in $dir: $()"

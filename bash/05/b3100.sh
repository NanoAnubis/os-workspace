#!/bin/bash

read -p 'Enter username: ' user
echo "Active sessions for user $user: $(who -u | grep $user | wc -l)"
#who -u | grep $user | wc -l

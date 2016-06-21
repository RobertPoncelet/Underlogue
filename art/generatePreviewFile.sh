#!/bin/bash

for f in $1/$1.*.txt; do
    #clear
    cat $f >> $1/$1_preview.txt
    echo $f >> $1/$1_preview.txt
    #sleep 1
done

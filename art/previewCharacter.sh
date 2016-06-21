#!/bin/bash

for f in $1/$1.*.txt; do
    clear
    cat $f
    echo $f
    sleep 2
done

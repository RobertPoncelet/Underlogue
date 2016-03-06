#!/bin/bash

for f in $1/$1.*.txt; do
    clear
    cat $f
    sleep 1
done

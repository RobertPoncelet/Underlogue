#!/bin/bash

for f in $1/$1.*.txt; do
    clear
    cat $f
    echo "Name this expression: "
    read newname
    mv $f $1/$1.$newname.txt
done

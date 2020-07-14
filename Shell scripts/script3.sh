#!/bin/bash

D=$1
touch newFile.txt
for F in `find $D -type f -name "*.log"`; do
        cat $F | sort > newFile.txt
        cat newFile.txt > $F
done
rm newFile.txt
#!/bin/bash

D=$1

if [ -z "$D" ]; then
        echo "ERROR: No directory given" >&2
        exit 1
fi

if [ ! -d "$D" ]; then
        echo "ERROR: No directory $D found" >&2
        exit 1
fi

bigFiles=0
for f in `find $D -type f -name "*.c"`; do
        nr=`cat $f | wc -l`
        if [ $nr -gt 500 ]; then
                echo $f has $nr lines
                bigFiles=`expr $bigFiles + 1`
        fi
        if [ $bigFiles -eq 2 ]; then
                break
        fi
done

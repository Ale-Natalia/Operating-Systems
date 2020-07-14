#!/bin/bash

dir=$1 #directory received as cmd line argument
filesWith500=0


for file in `find $dir -type f -name *.c`; do
        nrlines=`cat $file | wc -l`
        if [ $nrlines -gt 500 ]; then
                echo $file has $nrlines lines
                filesWith500=`expr $filesWith500 + 1`
                if [ $filesWith500 -eq 2 ]; then
                        break
                fi
        fi
done
#!/bin/bash

for fs in `cat df.fake | tail -n +2 | awk '{print $2 ":" $5 ":" $NF}'`; do
        size=`echo $fs | cut -d: -f1`
        space=`echo $fs | cut -d: -f2`
        sys=`echo $fs | cut -d: -f3`
        size2=${size%?}
        space2=${space%?}
        echo $sys has size $size2, space $space2
        if [ $size2 -lt 1024 ]; then
                echo $sys is smaller than 1 GB
        elif [ $space2 -gt 80 ]; then
                echo $sys has less than 20% space left
        fi
done

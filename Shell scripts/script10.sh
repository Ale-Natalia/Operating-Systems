#!/bin/bash

month=`date | awk '{print $2}'`
month="Mar"

for s in `cat last.fake | grep "\([^ ]* \)\{4\}$month " | awk '{print $1}' | sort | uniq -c | sort -n -r | awk '{print $1 ":" $2}'`; do
        name=`echo $s | cut -d: -f1`
        count=`echo $s | cut -d: -f2`
        echo $name $count
done
#!/bin/bash

for u in `cat who.fake | cut -d ' ' -f1`; do
        nr=0
        for p in `cat ps.fake | grep -v "^root " | grep "^$u " | awk '{print $1}'`; do
                nr=`expr $nr + 1`
                echo $p
        done
        echo $u has $nr processes
done
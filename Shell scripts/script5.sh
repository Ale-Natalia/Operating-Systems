#!/bin/bash

for n in $@; do
        echo $n is a dangerous program and needs to be killed
done

while true; do
        for n in $@; do
                for p in `ps -ef | grep -v "\([^ ]* \)\{8\}./5.sh" | grep " $n$" | awk '{print $2}'`; do
                        echo $p needs to dieeeeeee
                        kill $p
                done
                sleep 1
        done
done
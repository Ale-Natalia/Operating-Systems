#!/bin/bash

D=$1

for f in `find -L $D`; do
        echo $f
        if [ ! -e $f ]; then
                echo Symbolic link points to file no longer available
        else
                echo Valid symbolic link
        fi
done
#!/bin/bash

f=$1

str=""
for u in `cat $f`; do
        echo $u
        if grep "^$u:" passwd.fake; then
                str="$str,$u@scs.ubbcluj.ro"
        fi
done
str2=${str:1}
echo $str2
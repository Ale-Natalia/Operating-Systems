#!/bin/bash

D=$1

files=`find $D`
for f in ` md5sum $files | sort`; do
        echo $f
done
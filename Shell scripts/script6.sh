#!/bin/bash

D=$1

files=`find $D`
for f in ` ls -l $files | grep "^[d\-]\([r\-]w[x\-]\)\{3\}" | awk '{print $9 ":" $1}'`; do
        echo $f
        filename=`echo $f | cut -d: -f1`
        perm=`echo $f | cut -d: -f2`
        echo Before removing write permission: $filename has $perm
        chmod -w $filename
done
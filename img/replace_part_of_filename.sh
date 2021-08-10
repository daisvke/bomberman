#!/bin/sh

var1=`find . -type f -iname '*explose*'`
for i in $var1; do mv "$i" "`echo $i | sed 's/explose/explode/g'`"; done

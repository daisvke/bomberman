#!/bin/sh

var1=`find . -type f -iname '*-24x24*'`
for i in $var1; do mv "$i" "`echo $i | sed 's/-24x24//g'`"; done

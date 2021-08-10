#!/bin/sh

for f in *.png ; do convert $f ${f/%png/xpm} ; done
rm *.png

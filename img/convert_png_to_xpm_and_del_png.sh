#!/bin/sh

# How to use: 
# 	bash convert_png_to_xpm_and_del_png.sh

for f in *.png ; do convert $f ${f/%png/xpm} ; done
rm *.png

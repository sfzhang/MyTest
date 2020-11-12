#!/bin/bash

usage="$0 symbol"

if [ $# -ne 1 ]
then
    echo $usage
    exit 1
fi

vtk_lib_path=/usr/local/vtk-9.0.1/lib

for i in `ls $vtk_lib_path/*.so`
do
    nm $i | grep "$1" > /dev/null 2>&1
    if [ $? -eq 0 ]
    then
        so=`basename $i | sed -e 's/lib//' | sed -e 's/.so//'`
        echo -e "\e[1;31m$1\e[m found in:"
        echo -e "    \e[1;36m$so\e[m: $i"
        exit 0
    fi
done

echo -e "\e[1;31m$1\e[m NOT FOUND!"
    

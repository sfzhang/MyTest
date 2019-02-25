#!/bin/bash

while read local_ref local_sha1 remote_ref remote_sha1
do
    if [[ "$remote_ref" == "refs/for/master" ]]
    then
        exit 0
    fi
done


echo -n "Enter bug id:"
exec < /dev/tty

while true
do
    read bugid
    echo $bugid
    expr $bugid + 0 &>/dev/null
    if [ $? -ne 0 ]; then
        echo "bug id should be a number"
        echo -n "Enter bug id:"
    else
        break
    fi
done

rs="1"
rs=`python3 test/autotest/attach.py $bugid`
if [ "$rs" != "0" ]; then
    echo $rs
    exit 1
else
    exit 0
fi

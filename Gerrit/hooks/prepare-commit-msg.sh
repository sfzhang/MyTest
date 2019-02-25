#!/bin/bash
#
# An example hook script to prepare the commit log message.
# Called by "git commit" with the name of the file that has the
# commit message, followed by the description of the commit
# message's source.  The hook's purpose is to edit the commit
# message file.  If the hook fails with a non-zero status,
# the commit is aborted.
#
# To enable this hook, rename this file to "prepare-commit-msg".

# This hook includes three examples.  The first comments out the
# "Conflicts:" part of a merge commit.
#
# The second includes the output of "git diff --name-status -r"
# into the message, just before the "git status" output.  It is
# commented because it doesn't cope with --amend or with squashed
# commits.
#
# The third example adds a Signed-off-by line to the message, that can
# still be edited.  This is rarely a good idea.

#case "$2,$3" in
#  merge,)
#    /usr/bin/perl -i.bak -ne 's/^/# /, s/^# #/#/ if /^Conflicts/ .. /#/; print' "$1" ;;

# ,|template,)
#   /usr/bin/perl -i.bak -pe '
#      print "\n" . `git diff --cached --name-status -r`
#	 if /^#/ && $first++ == 0' "$1" ;;

#  *) ;;
#esac

# SOB=$(git var GIT_AUTHOR_IDENT | sed -n 's/^\(.*>\).*$/Signed-off-by: \1/p')
# grep -qs "^$SOB" "$1" || echo "$SOB" >> "$1"

ztcheck=sbin/hooks/zentao/ztcheck.py
if [[ ! -f "$ztcheck" ]]
then
    exit 0
fi

exec < /dev/tty

# Check task/bug
old_msg=`grep -E "^task:[0-9]+$" "$1" | head -n 1`
if [[ "$old_msg" == "" ]]
then
    old_msg=`grep -E "^bug:[0-9]+$" "$1" | head -n 1`
fi

if [[ "$old_msg" != "" ]]
then
    # Check invalid or not
    type=`echo $old_msg | awk -F: '{ print $1 }'`
    id=`echo $old_msg | awk -F: '{ print $2 }'`
    python3 "$ztcheck" "$type" "$id"
    if [[ $? -ne 0 ]]
    then
        echo "Invalid original: $old_msg, replace it."
    else
        read -p "Use original: $old_msg ? [Y/n]: " answer
        if [[ "$answer" == "" || "$answer" == "Y" || "$answer" == "y" ]]
        then
            new_msg=$old_msg
        fi
    fi
fi

# Input new taks/bug
if [[ "$new_msg" == "" ]]
then
    read -p "Choose commit type: task(t) or bug(b): " type
    if [[ "$type" == "t" ]]
    then
        type="task"
    elif [[ "$type" == "b" ]]
    then
        type="bug"
    else
        echo "Invalid commit type: $type!"
        exit 1
    fi

    read -p "Enter $type ID: " id

    # Check invalid or not
    python3 "$ztcheck" "$type" "$id"
    if [[ $? -ne 0 ]]
    then
        echo "Error: Invalid $type id($id)"
        exit 1
    fi
    new_msg="$type:$id"
fi

# Replace message
cp "$1" "$1.bak"
if [[ $? -ne 0 ]]
then
    echo "Backup $1 failed!"
    exit 1
fi

echo "$new_msg" > "$1"
if [[ "$old_msg" == "" ]]
then
    echo "" >> "$1"
fi

while read line
do
    if [[ "$old_msg" == "" || "$old_msg" != "$line" ]]
    then
        echo "$line" >> "$1"
    fi
done < "$1.bak"

rm -f "$1.bak"

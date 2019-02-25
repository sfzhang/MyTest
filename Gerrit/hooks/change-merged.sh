#!/bin/bash

work_dir="/home/gerrit/codereview/review_site/hooks/zentao"

# Parse argument
args=`getopt -ql "change-url:,change-owner:,project:,branch:,commit:" -- "$@"`
eval set -- "$args"

while true
do
    case "$1" in
        --change-url)
            change_url=$2
            shift 2
            ;;
        --change-owner)
            change_owner=$2
            shift 2
            ;;
        --project)
            project=$2
            shift 2
            ;;
        --branch)
            branch=$2
            shift 2
            ;;
        --commit)
            commit=$2
            shift 2
            ;;
        --topic)
            shift 2
            ;;
        --)
            shift
            break
            ;;
        *)
            shift
            ;;
    esac
done

receiver="shengfazhang@126.com"
title="change-merged hook failed"

if [[ "$change_url" == "" ]] || [[ "$change_owner" == "" ]] || [[ "$project" == "" ]] || [[ "$branch" == "" ]] || [[ "$commit" == "" ]]
then
    # Send email
    python3 $work_dir/sendmail.py "$receiver" "$title" "Invalid argument: $@"
    exit 1
fi

if [[ "$project" != "hifu" ]] || [[ "$branch" != "master" ]]
then
    echo "Ignore the $branch in $project!"
    exit 0
fi

# Check project exist or not
repo_root=$HOME/Git
proj_dir=$project-$branch-$commit

if [[ ! -d $repo_root ]]
then
    mkdir $repo_root
    if [[ $? -ne 0 ]]
    then
        python3 $work_dir/sendmail.py "$receiver" "$title" "Create $repo_root failed: $@"
        exit 1
    fi
fi

# Clone project
/bin/rm -fr $repo_root/$proj_dir
cd $repo_root && git clone ssh://cmshende@192.168.1.2:2022/$project $proj_dir
if [[ $? -ne 0 ]]
then
    # Send email
    python3 $work_dir/sendmail.py "$receiver" "$title" "Clone project failed: $@"
    /bin/rm -fr $repo_root/$proj_dir
    exit 1
fi

# Get commit message
cd $proj_dir
commit_msg=`git log --format=%B -n 1 $commit`
id=`echo "$commit_msg" | grep -E "^task:[0-9]+$" | head -n 1 | awk -F: '{ print $2 }'`
if [[ "$id" != "" ]]
then
    type="task"
else
    id=`echo "$commit_msg" | grep -E "^bug:[0-9]+$" | head -n 1 | awk -F: '{ print $2 }'`
    if [[ "$id" != "" ]]
    then
        type="bug"
    else
        # Send email
        python3 $work_dir/sendmail.py "$receiver" "$title" "Get commit message failed: $@"

        /bin/rm -fr $repo_root/$proj_dir
        exit 1
    fi
fi

# Remove project
/bin/rm -fr $repo_root/$proj_dir

# Update 
python3 $work_dir/ztupdate.py $type $id $change_url
if [[ $? -ne 0 ]]
then
    # Send email
    python3 $work_dir/sendmail.py "$receiver" "$title" "Update zentao failed: $@"
    exit 1
else
    python3 $work_dir/sendmail.py "$receiver" "change-merged hook success" "Update zentao success: $@"
    exit 0
fi

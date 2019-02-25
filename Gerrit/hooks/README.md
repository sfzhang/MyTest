Add Gerrit change-url to zentao when change merged

1. put pre-push.sh and prepare-commit-msg.sh at .git/hooks
    cp pre-push.sh <proj_dir>/.git/hooks/pre-push
    cp prepare-commit-msg.sh <proj_dir>/.git/hooks/prepare-commit-msg

    mkdir -p <proj_dir>/sbin/hooks
    cp -r zentao <proj_dir>/sbin/hooks

2. put change-merged.sh at /home/gerrit/codereview/review_site/hooks
    ln -s change-merged.sh change-merged
    cp -r zentao /home/gerrit/codereview/review_site/hooks

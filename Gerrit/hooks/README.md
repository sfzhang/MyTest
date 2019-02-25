Add Gerrit change-url to zentao when change merged

0. zentao api
   (1) get sid
       get http://192.168.1.2:8090/zentao/api-getsessionid.json

       {"status":"success","data":"{\"title\":\"\",\"sessionName\":\"zentaosid\",\"sessionID\":\"n95k4mej3kigt30p6o6fv0aja1
\",\"rand\":5180,\"pager\":null}","md5":"64dbc2ab3cbfc88df3f2bdaca615a052"}

    (2) login
        post http://192.168.1.2:8090/zentao/user-login.json?zentaosid=n95k4mej3kigt30p6o6fv0aja1
        account zhangshengfa
        password 

    (3) get edit
        get http://192.168.1.2:8090/zentao/bug-edit-17.json?zentaosid=n95k4mej3kigt30p6o6fv0aja1

1. put pre-push.sh and prepare-commit-msg.sh at .git/hooks
    cp pre-push.sh <proj_dir>/.git/hooks/pre-push
    cp prepare-commit-msg.sh <proj_dir>/.git/hooks/prepare-commit-msg

    mkdir -p <proj_dir>/sbin/hooks
    cp -r zentao <proj_dir>/sbin/hooks

2. put change-merged.sh at /home/gerrit/codereview/review_site/hooks
    ln -s change-merged.sh change-merged
    cp -r zentao /home/gerrit/codereview/review_site/hooks

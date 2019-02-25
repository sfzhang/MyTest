#!/usr/bin/python3
# -*- coding: utf-8 -*-

"""
Update an existed task or bug
"""

import os
import sys
from zentao import *


init_log("DEBUG", "/home/gerrit/codereview/review_site/logs/" + os.path.basename(sys.argv[0]) + ".log")

zts = ZentaoService()

if len(sys.argv) != 4:
    error_log("Invalid argument!")
    exit(1)

id = sys.argv[2]
change_url = sys.argv[3]
msg = 'Gerrit Code Review: <a href="' + change_url + '" target="_blank">' + change_url.split('/')[-1] + '</a><br>'

if sys.argv[1] == "task" and zts.update_task(id, msg):
    exit(0)
elif sys.argv[1] == "bug" and zts.update_bug(id, msg):
    exit(0)
else:
    exit(1)


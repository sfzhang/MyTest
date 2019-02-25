#!/usr/bin/python3
# -*- coding: utf-8 -*-

"""
Edit an existed task or bug
"""

import os
import sys
from zentao import *


init_log("DEBUG", "./.git/logs/" + os.path.basename(sys.argv[0]) + ".log")

zts = ZentaoService()

if len(sys.argv) != 3:
    error_log("Invalid argument!")
    exit(1)

if sys.argv[1] == "task" and zts.check_task(sys.argv[2]):
    exit(0)
elif sys.argv[1] == "bug" and zts.check_bug(sys.argv[2]):
    exit(0)
else:
    exit(1)


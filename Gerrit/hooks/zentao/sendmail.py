#!/usr/bin/python3
# -*- coding: utf-8 -*-

"""
Send email.
"""

import os
import sys
import smtplib
from email.mime.text import MIMEText
from log import *


init_log("DEBUG", "/home/gerrit/codereview/review_site/logs/" + os.path.basename(sys.argv[0]) + ".log")

if len(sys.argv) != 4:
    error_log("Invalid argument.")
    for a in sys.argv:
        print(a)
    exit(1)

receiver = sys.argv[1]
title = sys.argv[2]
content = sys.argv[3]

sender_host = "smtp.exmail.qq.com"
sender_user = "cm@shendehc.com"
sender_pass = "cm@SD2015"

msg = MIMEText(content)
msg['Subject'] = title
msg['From'] = sender_user
msg['To'] = ";".join(receiver.split())

try:
    server = smtplib.SMTP()
    server.connect(sender_host)
    server.login(sender_user, sender_pass)
    server.sendmail(sender_user, receiver.split(), msg.as_string())
    server.close()
    info_log("Send email to receiver[%s], title[%s] success", receiver, title)
except Exception as e:
    error_log("send email failed[%s]: receiver[%s], title[%s], content[%s]", e, receiver, title, content)
    exit(1)


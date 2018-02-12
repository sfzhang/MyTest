#!/usr/bin/python3

import os
import time
import pymysql

try:
    db = pymysql.connect(host="localhost", user="doc", passwd="doc", db="docseqdb", charset='utf8', autocommit='false')
except Exception as error:
    print("Connect to database[docseqdb] failed!")
    print(error)
    exit(1)

try:
    # Get current time
    now = time.localtime()
    year = time.strftime("%y", now)
    month = time.strftime("%m", now)
    month = str(int(month))

    if int(month) > 9:
        month = chr(ord("A") + int(month) - 10)

    # Get user name
    user = os.getenv("USER")
    flag = 0
    while user.find(" ") != -1 or user.find("\t") != -1 or user == "":
        if flag > 0:
            print("Invalid user name!")
        user = input("Please input your name: ")
        user = user.strip()
        flag = 1

    # Get project name
    project_list = [ "BF", "BM", "UF", "FM" ]
    project = ""
    flag = 0
    while project not in project_list:
        if flag > 0:
            print("Invalid project name!")
        flag = 1
        project = input("Please input project name[ (BF), BM, UF, FM ]: ")
        project = project.strip()

        if project == "":
            project = "BF"

    # Begin transaction
    db.begin();

    # Get sequence
    cursor = db.cursor()

    # Get sequence id and update
    cursor.execute("select seq_id from tbl_sw_cfg where seq_year = %s and seq_month = %s for update", (year, month))
    data = cursor.fetchall()

    if len(data) > 1:
        raise pymysql.DataError("Invalid record in tbl_sw_cfg: seq_year = '" + year + "' and seq_month = '" + month + "'")

    if len(data) == 0:
        seq_id = 1
        cursor.execute("insert into tbl_sw_cfg values(%s, %s, %s)", (year, month, seq_id))
    else:
        seq_id = data[0][0] + 1
        if seq_id > 999:
            raise pymysql.DataError("reach to maximum seq_id, seq_year = '" + year + "' and seq_month = '" + month + "'")
        else :
            cursor.execute("update tbl_sw_cfg set seq_id = %s where seq_year = %s and seq_month = %s", (seq_id, year, month))

    # Insert to tbl_sw_seq
    sequence = year + month + '{:0>3}'.format(seq_id)
    cursor.execute("insert into tbl_sw_seq(sequence, project, owner) values(%s, %s, %s)", (sequence, project, user))
    db.commit()

    print("Generate doc sequence success: " + sequence)
    print("Project prefix: SDRD-SW-" + project + "-" + sequence + "-")

except Exception as error:
    db.rollback()
    print("ERROR: ", end = '')
    print(error)
    print("Generate doc sequence failed!");
    exit(1)

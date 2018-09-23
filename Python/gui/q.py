#!/usr/bin/python3

import datetime
import queue

q = queue.Queue()

begin = datetime.datetime.now()

try:
    s = q.get(block=True, timeout=0.1)
except queue.Empty:
    end = datetime.datetime.now()

ts = end - begin

print(ts.total_seconds())

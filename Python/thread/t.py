#!/usr/bin/python3

import time
import threading

def func():
    print("thread: %d created!", threading.get_ident())
    time.sleep(4)

while True:
    thread = threading.Thread(target=func, args=())
    thread.start()
    thread.join()

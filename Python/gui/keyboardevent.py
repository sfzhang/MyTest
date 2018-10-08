#!/usr/bin/python3
#
# Copyright (c) 2018, Shendehc Co., Ltd. All rights reserved.
#
# THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF SHENDEHC CO., LTD.
# AND IS PROTECTED AS AN UNPUBLISHED WORK UNDER APPLICABLE COPYRIGHT
# LAWS.
#
# The contents of this file may not be disclosed to third parties,
# copied or duplicated in any form, in whole or in part, without the
# prior written permission of Shendehc Co., Ltd.
#
# Author: sfzhang(shengfazhang@shendehc.com)
#
# -*- coding: utf-8 -*-

import signal
from multiprocessing import Queue
from pynput import keyboard


class KeyboardEvent(object):
    """
    Keyboard event message:
        [event key]
        event:
            pressed
            released
        key:
            alt/alt_gr/alt_l/alt_r/backspace/caps_lock/cmd/cmd_l/cmd_r/ctrl/ctrl_l/ctrl_r/delete/down/end/enter/esc/
            f1-f20/home/insert/left/menu/num_lock/page_down/page_up/pause/print_screen/right/scroll_lock/shift/
            shift_l/shift_r/space/tab/up...
    """

    def __init__(self, q):
        """
        Initialize
        :param q: The queue for mulitprocessing
        """
        signal.signal(signal.SIGINT, signal.SIG_IGN)
        signal.signal(signal.SIGQUIT, signal.SIG_IGN)
        signal.signal(signal.SIGTSTP, signal.SIG_IGN)
        self.q = q
        self.event = None
        self.key = None
        self.listener = keyboard.Listener(on_press=self.on_press, on_release=self.on_release)
        self.listener.start()

    def _send(self):
        """
        Send the keyboard event
        """
        msg = "keyboard " + self.event + " " + self.key
        self.q.put(msg)

    def stop(self):
        """
        Stop listen
        """
        self.listener.stop()

    def join(self):
        """
        Join the thread
        """
        self.listener.join()

    def on_press(self, key):
        """
        Press event
        :param key: The key pressed
        """
        try:
            self.key = key.char
        except AttributeError:
            self.key = str(key).split('.')[1]

        self.event = "pressed"
        self._send()

    def on_release(self, key):
        """
        Release event
        :param key: The key released
        """
        try:
            self.key = key.char
        except AttributeError:
            self.key = str(key).split('.')[1]

        self.event = "released"
        self._send()


if __name__ == '__main__':
    q = Queue()
    k = KeyboardEvent(q)
    k.join()

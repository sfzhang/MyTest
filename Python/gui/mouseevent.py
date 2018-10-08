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

from multiprocessing import Queue
from pynput import mouse


class MouseEvent(object):
    """
    Mouse event message:
        [event button x,y dx,dy]
        event:
            pressed
            released
            scrolled
        button:
            none
            left
            right
            middle
        x,y: x and y position
        dx,dy: dx and dy exist when scrolled
    """

    def __init__(self, q):
        """
        Initialize
        :param q: The queue for mulitprocessing
        """
        self.q = q
        self.listener = mouse.Listener(on_move=self.on_move, on_click=self.on_click, on_scroll=self.on_scroll)
        self.listener.start()

        self.event = None
        self.button = None
        self.x = 0
        self.y = 0
        self.dx = 0
        self.dy = 0

    def _send(self):
        """
        Send the mouse event by queue
        """
        msg = "mouse " + self.event + " " + self.button + " " + str(self.x) + "," + str(self.y)
        if self.event == "scrolled":
            msg += " " + str(self.dx) + "," + str(self.dy)
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

    def on_move(self, x, y):
        """
        Mouse move event
        :param x: The x position
        :param y: The y position
        """
        pass

    def on_click(self, x, y, button, pressed):
        """
        Mouse click event
        :param x: The x position
        :param y: The y position
        :param button: The event button
        :param pressed: Pressed or released
        """
        self.x, self.y = x, y
        if pressed:
            self.event = "pressed"
        else:
            self.event = "released"

        if button == mouse.Button.left:
            self.button = "left"
        elif button == mouse.Button.right:
            self.button = "right"
        elif button == mouse.Button.middle:
            self.button = "middle"
        else:
            return

        self._send()

    def on_scroll(self, x, y, dx, dy):
        """
        Mouse scroll event
        :param x: The x position
        :param y: The y position
        :param dx: The delta x
        :param dy: The delat y
        """
        self.event = "scrolled"
        self.button = "none"
        self.x, self.y = x, y
        self.dx, self.dy = dx, dy

        self._send()


if __name__ == '__main__':
    q = Queue()
    m = MouseEvent(q)
    m.join()

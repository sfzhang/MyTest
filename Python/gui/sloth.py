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

import os
import sys
import re
import datetime
from multiprocessing import Process, Queue
import mouseevent
import keyboardevent
import screenshot
import checklog
import runscript
import includefile
import waiting


class Sloth(object):
    """
    Command:
    F2: Start to record
    F3: Pause record
    F4: Finish record
    F5: Screen shot
    F6: Check log
    F7: Add script to run
    F8: Include other file
    F9: Waiting

    Message protocol between process:
        [type message]
        type:
            include: include other message
            wait: wait for a moment
            mouse: mouse event
            keyboard: keyboard event
            screen_shot: check point by screen_shot
            check_log: check point by log
            run_script: run other script

        Include message:
            [file]
            file: message file name

        Wait message:
            [seconds]
            seconds: sleep seconds

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

        Keyboard event message:
            [event key]
            event:
                pressed
                released
            key:
                alt/alt_gr/alt_l/alt_r/backspace/caps_lock/cmd/cmd_l/cmd_r/ctrl/ctrl_l/ctrl_r/delete/down/end/enter/esc/
                f1-f20/home/insert/left/menu/num_lock/page_down/page_up/pause/print_screen/right/scroll_lock/shift/
                shift_l/shift_r/space/tab/up...

        Screen shot event:
            [x,y w,h file]
            x,y: top left position
            w,h: image width and height
            file: The saved file path name

        Check log:
            [type log file]
            type:
                include
                exclude
            log: The log to check
            file: The log file name

        Run script:
            [type script func]
            type: ignored if func existed
                sync: run script in the same process
                async: run the script in the different process
            script: The script file
            func: The function in script

    Generated XML format:
    <?xml version="1.0" encoding="UTF-8"?>
    <gui_auto_test>
        <include interval="xx" file="xx.xml" />
        <wait seconds="xx" />
        <mouse interval="xx" event="pressed" button="left/middle/right" x="xx" y="xx" />
        <mouse interval="xx" event="released" button="left/middle/right" x="xx" y="xx" />
        <mouse interval="xx" event="clicked" button="left/middle/right" x="xx" y="xx" />
        <mouse interval="xx" event="double_clicked" button="left/middle/right" x="xx" y="xx" />
        <mouse interval="xx" event="scrolled" button="none" x="xx" y="xx" dx="xx" dy="xx"/>
        <mouse interval="xx" event="dragged" button="left/middle/right" x="xx" y="xx" dx="xx" dy="xx" duration="xx"/>
        <keyboard interval="xx" event="pressed" key="xx" />
        <keyboard interval="xx" event="released" key="xx" />
        <keyboard interval="xx" event="type" key="xx" />
        <screen_shot interval="xx" x="xx" y="xx" w="xx" h="xx" file="xx" />
        <check_log interval="xx" type="include/exclude" log="xx" file="xx" />
        <run_script interval="xx" type="sync/async" script="xx" />
    </gui_auto_test>
    """

    click_interval = 400000
    double_click_interval = 500000
    key_interval = 500000

    def __init__(self, file):
        """
        Initialized
        :param file: The file to dump
        """
        self.file = file
        self.exit = False
        self.ignore_key = False

        self.q = Queue()
        self.start = False
        self.timestamp = None

        self.child_process = None

        self.m = mouseevent.MouseEvent(self.q)
        self.k = keyboardevent.KeyboardEvent(self.q)

        self.event_list = []

    @staticmethod
    def _replace(s):
        """
        Replace the path by env
        :param s: The path string
        :return: The replaced path
        """
        if "GAT_ROOT" in os.environ:
            s = re.sub(os.environ["GAT_ROOT"], "$GAT_ROOT", s)
        return s

    @staticmethod
    def _escape(s):
        """
        Escape string for XML attribute
        :param s: The string for attribute
        :return: The escaped string
        """
        return s.replace("&", "&amp;").replace("<", "&lt;").replace(">", "&gt;").replace('"', "&quot;")\
            .replace("'", "&apos;")

    def _valid_key(self, key):
        """
        Check if valid key
        :param key:
        :return: True if valid otherwise False
        """
        for event in reversed(self.event_list):
            if event[1] == "keyboard" and event[3] == key:
                if event[2] == "pressed":
                    return True
                else:
                    return False
        return False

    def _get_interval(self):
        """
        Get the time interval
        :return: interval in ms
        """
        now = datetime.datetime.now()
        interval = (now - self.timestamp).microseconds + 1000000 * (now - self.timestamp).seconds
        self.timestamp = now
        return interval

    def _append_mouse_event(self, *msg):
        """
        Append mouse event
        :param msg: (event, button, x, y, dx, dy)
        """
        interval = self._get_interval()

        if msg[0] == "pressed":
            self.event_list.append([interval, "mouse", msg[0], msg[1], msg[2], msg[3]])
        elif msg[0] == "released":
            if len(self.event_list) > 0:
                if self.event_list[-1][1] == "mouse" and self.event_list[-1][2] == "pressed" and \
                        self.event_list[-1][3] == msg[1]:
                    if self.event_list[-1][4] == msg[2] and self.event_list[-1][5] == msg[3]:
                        if interval <= Sloth.click_interval:
                            if len(self.event_list) > 1 and self.event_list[-2][1] == "mouse" and \
                                self.event_list[-2][2] == "clicked" and self.event_list[-2][3] == msg[1] and \
                                    self.event_list[-2][4] == msg[2] and self.event_list[-2][5] == msg[3] and \
                                    interval + self.event_list[-2][6] <= Sloth.double_click_interval:
                                self.event_list.pop()
                                self.event_list[-1][2] = "double_clicked"
                            else:
                                self.event_list[-1][2] = "clicked"
                                self.event_list[-1].append(interval)
                        else:
                            self.event_list.append([interval, "mouse", msg[0], msg[1], msg[2], msg[3]])
                    else:
                        self.event_list[-1][2] = "dragged"
                        self.event_list[-1].append(msg[2])
                        self.event_list[-1].append(msg[3])
                        self.event_list[-1].append(interval)
                else:
                    self.event_list.append([interval, "mouse", msg[0], msg[1], msg[2], msg[3]])
            else:
                print("Match error: " + msg[1] + " button released at (", msg[2], ", ", msg[3],
                      ") without pressed event")
        elif msg[0] == "scrolled":
            if len(self.event_list) > 0 and self.event_list[-1][2] == "scrolled" and \
                self.event_list[-1][3] == msg[1] and self.event_list[-1][4] == msg[2] and \
                    self.event_list[-1][5] == msg[3] and \
                    (self.event_list[-1][6] * msg[4] == 0 and self.event_list[-1][7] * msg[5] > 0 or \
                     self.event_list[-1][6] * msg[4] > 0 and self.event_list[-1][7] * msg[5] == 0):
                self.event_list[-1][6] += msg[4]
                self.event_list[-1][7] += msg[5]
            else:
                self.event_list.append([interval, "mouse", msg[0], msg[1], msg[2], msg[3], msg[4], msg[5]])
        else:
            print("Invalid error: " + msg[1] + " button " + msg[0] + " at (" + msg[2] + ", " + msg[3] + ")")

    def _append_key_event(self, event, key):
        """
        Append a key
        :param event: pressed or released
        :param key: The key
        """
        interval = self._get_interval()

        if event == "pressed":
            self.event_list.append([interval, "keyboard", "pressed", key])
        elif event == "released":
            if not self._valid_key(key):
                if not self.ignore_key:
                    print("Invalid error: " + key + " released without pressed")
                else:
                    self.ignore_key = False
            else:
                if len(key) == 1 and self.event_list[-1][1] == "keyboard" and self.event_list[-1][2] == "pressed" and \
                        self.event_list[-1][3] == key and interval <= Sloth.key_interval:
                    self.event_list[-1][2] = "type"
                else:
                    self.event_list.append([interval, "keyboard", event, key])
        else:
            print("Invalid error: unknown event[" + event + "]")

    def _append_event(self, msg):
        """
        Append message to event
        :param msg: The event message
        """
        now = datetime.datetime.now()
        interval = str((now - self.timestamp).microseconds)

        split_msg = msg.split(' ')
        msg_item = [str(interval)]
        for i in split_msg:
            msg_item.append(i.replace('\x00', ' '))
        self.event_list.append(msg_item)
        self.timestamp = now

    def _finish(self):
        """
        Write the command to XML file
        """
        if len(self.event_list) > 0:
            with open(self.file, 'w') as f:
                f.write('<?xml version="1.0" encoding="UTF-8"?>\n')
                f.write('<gui_auto_test>\n')

                for event in self.event_list:
                    s = '    <' + event[1]

                    if event[1] != "wait":
                        s += ' interval="' + str(float(event[0]) / 1000000) + '"'

                    if event[1] == "mouse":
                        s += ' event="' + event[2] + '" button="' + event[3] + '" x="' + str(event[4]) + '" y="' + \
                             str(event[5]) + '"'
                        if len(event) == 8:
                            s += ' dx="' + str(event[6]) + '" dy="' + str(event[7]) + '"'
                        elif len(event) == 9:
                            s += ' dx="' + str(event[6] - event[4]) + '" dy="' + str(event[7] - event[5]) + \
                                 '" duration="' + str(event[8] / 1000000.) + '"'
                    elif event[1] == "keyboard":
                        s += ' event="' + event[2] + '" key="' + event[3] + '"'
                    elif event[1] == "screen_shot":
                        s += ' x="' + event[2].split(',')[0] + '" y="' + event[2].split(',')[1] + '" w="' + \
                             event[3].split(',')[0] + '" h="' + event[3].split(',')[1] + '" file="' + \
                             Sloth._escape(Sloth._replace(event[4])) + '"'
                    elif event[1] == "check_log":
                        s += ' type="' + event[2] + '" file="' + Sloth._escape(Sloth._replace(event[3])) + '" log="' + \
                             Sloth._escape(event[4]) + '"'
                    elif event[1] == "run_script":
                        s += ' type="' + event[2] + '" script="' + Sloth._escape(Sloth._replace(event[3])) + '"'
                    elif event[1] == "include":
                        s += ' file="' + Sloth._escape(Sloth._replace(event[2])) + '"'
                    elif event[1] == "wait":
                        s += ' second="' + event[2] + '"'
                    s += ' />\n'
                    f.write(s)
                f.write("</gui_auto_test>\n")

    def _screen_shot(self):
        """
        Get the screen shot
        """
        self.start = False
        self.child_process = Process(target=screenshot.get_screen_shot, args=(self.q,))
        self.child_process.start()

    def _check_log(self):
        """
        Get the check log
        """
        self.start = False
        self.child_process = Process(target=checklog.get_check_log, args=(self.q,))
        self.child_process.start()

    def _run_script(self):
        """
        Get the run script
        """
        self.start = False
        self.child_process = Process(target=runscript.get_run_script, args=(self.q,))
        self.child_process.start()

    def _include_file(self):
        """
        Get the include file
        """
        self.start = False
        self.child_process = Process(target=includefile.get_include_file, args=(self.q,))
        self.child_process.start()

    def _waiting(self):
        """
        Get the wait time
        """
        self.start = False
        self.child_process = Process(target=waiting.get_waiting, args=(self.q,))
        self.child_process.start()

    def _join_child_process(self):
        """
        Join the child process
        """
        self.child_process.join()
        self.child_process = None

    def process(self):
        """
        Process the queue message
        """
        while True:
            msg = self.q.get()
            split_msg = msg.split()

            if split_msg[0] == "screen_shot" or split_msg[0] == "check_log" or split_msg[0] == "run_script" or \
                    split_msg[0] == "include" or split_msg[0] == "waiting":
                self._join_child_process()
                if len(split_msg) > 1:
                    self._append_event(msg)
                self.timestamp = datetime.datetime.now()
                self.start = True
                continue

            if not self.start:
                if split_msg[0] == "keyboard" and split_msg[1] == "pressed":
                    if split_msg[2] == "f2":
                        self.timestamp = datetime.datetime.now()
                        self.start = True
                    elif self.child_process is not None and (split_msg[2] == "esc" or split_msg[2] == "enter"):
                        self.ignore_key = True
                continue

            if split_msg[0] == "mouse":
                if split_msg[1] == "scrolled":
                    self._append_mouse_event(split_msg[1], split_msg[2], int(split_msg[3].split(',')[0]),
                                             int(split_msg[3].split(',')[1]),  int(split_msg[4].split(',')[0]),
                                             int(split_msg[4].split(',')[1]))
                else:
                    self._append_mouse_event(split_msg[1], split_msg[2], int(split_msg[3].split(',')[0]),
                                             int(split_msg[3].split(',')[1]),)
            elif split_msg[0] == "keyboard":
                if split_msg[1] == "released" and split_msg[2] == "f2":
                    continue
                elif split_msg[1] == "pressed" and split_msg[2] == "f3":
                    self.start = False
                    continue
                elif split_msg[1] == "pressed" and split_msg[2] == "f4":
                    self._finish()
                    return
                elif split_msg[1] == "pressed" and split_msg[2] == "f5":
                    self._screen_shot()
                    continue
                elif split_msg[1] == "pressed" and split_msg[2] == "f6":
                    self._check_log()
                    continue
                elif split_msg[1] == "pressed" and split_msg[2] == "f7":
                    self._run_script()
                    continue
                elif split_msg[1] == "pressed" and split_msg[2] == "f8":
                    self._include_file()
                    continue
                elif split_msg[1] == "pressed" and split_msg[2] == "f9":
                    self._waiting()
                    continue

                self._append_key_event(split_msg[1], split_msg[2])


if __name__ == "__main__":
    if len(sys.argv) != 2:
        print("Usage: " + sys.argv[0] + " file")
    else:
        s = Sloth(sys.argv[1])
        s.process()

#!/usr/bin/python3


import sys
import datetime
from multiprocessing import Process, Queue
import mouseevent
import keyboardevent
import screenshot
import checklog
import runscript


class Sloth(object):
    """
    Command:
    F2: Start to record
    F3: Pause record
    F4: Finish record
    F5: Screen shot
    F6: Check log
    F7: Add script to run

    Message protocol:
        [timestamp type message]
        timestamp: The timestamp
        type:
            include: include other message
            sleep: sleep for a moment
            mouse: mouse event
            keyboard: keyboard event
            screen_shot: check point by screen_shot
            check_log: check point by log
            run_script: run other script

        Include message:
            [file]
            file: message file name

        Sleep message:
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

        Screen shot event:(alt+s)
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
            [type script]
            type:
                sync: run script in the same process
                async: run the script in the different process
            script: The script file
    """

    def __init__(self, file):
        self.file = file
        self.exit = False

        self.q = Queue()
        self.start = False
        self.timestamp = None

        self.child_process = None

        self.m = mouseevent.MouseEvent(self.q)
        self.k = keyboardevent.KeyboardEvent(self.q)

        self.event_list = []

    def _valid_key(self, key):
        for event in reversed(self.event_list):
            if event[1] == "keyboard" and event[3] == key:
                if event[2] == "pressed":
                    return True
                else:
                    return False
        return False

    def _append_event(self, msg):
        now = datetime.datetime.now()
        interval = str((now - self.timestamp).microseconds)

        split_msg = msg.split(' ')
        msg_item = [str(interval)]
        for i in split_msg:
            msg_item.append(i.replace('\x00', ' '))
        self.event_list.append(msg_item)
        self.timestamp = now

    def _finish(self):
        if len(self.event_list) == 0:
            return

        with open(self.file, 'w') as f:
            f.write('<?xml version="1.0" encoding="UTF-8"?>\n')
            f.write('<auto_test>\n')
            f.write('    <sleep interval="0" seconds="8" />\n')
            for event in self.event_list:
                s = '    <' + event[1] + ' interval="' + event[0] + '"'
                if event[1] == "mouse":
                    s += ' event="' + event[2] + '" button="' + event[3] + '" x="' + event[4].split(',')[0] + \
                         '" y="' + event[4].split(',')[1] + '"'
                    if len(event) > 5:
                        s += ' dx="' + event[5].split(',')[0] + '" dy="' + event[5].split(',')[1] + '"'
                elif event[1] == "keyboard":
                    s += ' event="' + event[2] + '" key="' + event[3] + '"'
                elif event[1] == "screen_shot":
                    s += ' x="' + event[2].split(',')[0] + '" y="' + event[2].split(',')[1] + '" w="' + \
                         event[3].split(',')[0] + '" h="' + event[3].split(',')[1] + '" file="' + event[4] + '"'
                elif event[1] == "check_log":
                    s += ' type="' + event[2] + '" file="' + event[3] + '" log="' + event[4] + '"'
                elif event[1] == "run_script":
                    s += ' type="' + event[2] + '" file="' + event[3] + '"'
                s += ' />\n'
                f.write(s)

            f.write("</auto_test>\n")

    def _screen_shot(self):
        self.start = False
        self.child_process = Process(target=screenshot.get_screen_shot, args=(self.q,))
        self.child_process.start()

    def _check_log(self):
        self.start = False
        self.child_process = Process(target=checklog.get_check_log, args=(self.q,))
        self.child_process.start()

    def _run_script(self):
        self.start = False
        self.child_process = Process(target=runscript.get_run_script, args=(self.q,))
        self.child_process.start()

    def _join_child_process(self):
        self.child_process.join()
        self.child_process = None

    def process(self):
        while True:
            msg = self.q.get()
            split_msg = msg.split()

            if split_msg[0] == "screen_shot" or split_msg[0] == "check_log" or split_msg[0] == "run_script":
                self._join_child_process()
                if len(split_msg) > 1:
                    self._append_event(msg)
                self.timestamp = datetime.datetime.now()
                self.start = True
                continue

            if not self.start:
                if split_msg[0] == "keyboard" and split_msg[1] == "pressed" and split_msg[2] == "f2":
                    self.timestamp = datetime.datetime.now()
                    self.start = True
                continue

            if split_msg[0] == "mouse":
                self._append_event(msg)
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

                if split_msg[1] == "released" and not self._valid_key(split_msg[2]):
                    continue
                else:
                    self._append_event(msg)


if __name__ == "__main__":
    if len(sys.argv) != 2:
        print("Usage: " + sys.argv[0] + " file")
    else:
        s = Sloth(sys.argv[1])
        s.process()

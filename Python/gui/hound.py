#!/usr/bin/python3


import sys
import time
import getopt
import pyautogui
import pynput
from pynput.keyboard import Key
import xml.etree.ElementTree as ET


class Hound(object):
    """
    Parse XML and run.
    The XML format:
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
        <check_log type="include/exclude" log="xx" file="xx" />
        <run_script type="sync/async" file="xx" />
        <run_script file="xx" func="xx" />
    </gui_auto_test>
    """

    key_dict = {"alt": Key.alt, "alt_gr": Key.alt_gr, "alt_l": Key.alt_l, "alt_r": Key.alt_r,
                "backspace": Key.backspace, "caps_lock": Key.caps_lock, "cmd": Key.cmd, "cmd_l": Key.cmd_l,
                "cmd_r": Key.cmd_r, "ctrl": Key.ctrl, "ctrl_l": Key.ctrl_l, "ctrl_r": Key.ctrl_r,
                "delete": Key.delete, "down": Key.down, "end": Key.end, "enter": Key.enter, "esc": Key.esc,
                "f1": Key.f1, "f2": Key.f2, "f3": Key.f3, "f4": Key.f4, "f5": Key.f5, "f6": Key.f6, "f7": Key.f7,
                "f8": Key.f8, "f9": Key.f9, "f10": Key.f10, "f11": Key.f11, "f12": Key.f12, "f13": Key.f13,
                "f14": Key.f14, "f15": Key.f15, "f16": Key.f16, "f17": Key.f17, "f18": Key.f18, "f19": Key.f19,
                "f20": Key.f20, "home": Key.home, "insert": Key.insert, "left": Key.left, "menu": Key.menu,
                "num_lock": Key.num_lock, "page_down": Key.page_down, "page_up": Key.page_up, "pause": Key.pause,
                "print_screen": Key.print_screen, "right": Key.right, "scroll_lock": Key.scroll_lock,
                "shift": Key.shift, "shift_l": Key.shift_l, "shift_r": Key.shift_r, "space": Key.space,
                "tab": Key.tab, "up": Key.up}

    keyboard_ctrl = pynput.keyboard.Controller() # Use pynput.keyboard to avoid translate special key

    def run(self, file):
        """
        Run the XML file
        :param file: xml command file
        :return: True if succeed, otherwise False
        """
        tree = ET.parse(file)
        root = tree.getroot()
        for child in root:
            time.sleep(float(child.attrib["interval"]) / 1000000)
            if child.tag == "include":
                if not Hound._process_include_stmt(child.attrib["file"]):
                    print("_process_include_stmt() failed")
                    return False
            elif child.tag == "wait":
                Hound._process_wait_stmt(float(child.attrib["seconds"]))
            elif child.tag == "mouse":
                if child.attrib["event"] == "scrolled":
                    Hound._process_mouse_stmt(child.attrib["event"], child.attrib["button"], int(child.attrib["x"]),
                                              int(child.attrib["y"]), int(child.attrib["dx"]), int(child.attrib["dy"]))
                elif child.attrib["event"] == "dragged":
                    Hound._process_mouse_stmt(child.attrib["event"], child.attrib["button"], int(child.attrib["x"]),
                                              int(child.attrib["y"]), int(child.attrib["dx"]), int(child.attrib["dy"]),
                                              int(child.attrib["duration"]))
                else:
                    Hound._process_mouse_stmt(child.attrib["event"], child.attrib["button"], int(child.attrib["x"]),
                                              int(child.attrib["y"]))
            elif child.tag == "keyboard":
                Hound._process_keyboard_stmt(child.attrib["event"], child.attrib["key"])
            elif child.tag == "screen_shot":
                if not Hound._process_screen_shot_stmt(child.attrib["file"], int(child.attrib["x"]),
                                                       int(child.attrib["y"]), int(child.attrib["w"]),
                                                       int(child.attrib["h"])):
                    print("_process_screen_shot_stmt() failed")
                    return False
            elif child.tag == "check_log":
                if not Hound._process_check_log_stmt(child.attrib["type"], child.attrib["log"], child.attrib["file"]):
                    print("_process_check_log_stmt() failed")
                    return False
            elif child.tag == "run_script":
                if not Hound._process_run_script_stmt(child.attrib["type"], child.attrib["file"]):
                    print("_process_run_script_stmt() failed")
                    return False
        return True

    @staticmethod
    def _process_include_stmt(file):
        """
        Process include statement
        :param file: The included file
        :return: True if succeed, otherwise False
        """
        hound = Hound()
        return hound.run(file)

    @staticmethod
    def _process_wait_stmt(seconds):
        """
        Process wait statement
        :param seconds: The time in s to wait
        """
        time.sleep(seconds)

    @staticmethod
    def _process_mouse_stmt(event, button, x, y, dx=None, dy=None, duration=None):
        """
        Process mouse event
        :param event: The mouse event, pressed/released/scrolled/clicked/double_clicked/dragged
        :param button: The action button
        :param x: The position X
        :param y: The position Y
        :param dx: The delta X, only for scrolled and dragged
        :param dy: The delta Y, only for scrolled and dragged
        :param duration: The dragging duration
        """
        if event == "pressed":
            pyautogui.mouseDown(x, y, button)
        elif event == "released":
            pyautogui.mouseUp(x, y, button)
        elif event == "scrolled":
            pyautogui.scroll(dx + dy, x, y)
        elif event == "clicked":
            pyautogui.click(x=x, y=y, button=button)
        elif event == "double_clicked":
            pyautogui.doubleClick(x=x, y=y, button=button)
        elif event == "dragged":
            pyautogui.moveTo(x=x, y=y)
            pyautogui.dragRel(xOffset=dx, yOffset=dy, duration=duration, button=button)

    @staticmethod
    def _process_keyboard_stmt(event, key):
        """
        Process keyboard statement
        :param event: The keyboard event
        :param key: The action key
        """
        if key in Hound.key_dict:
            k = Hound.key_dict[key]
        else:
            k = key

        if event == "pressed":
            Hound.keyboard_ctrl.press(k)
        elif event == "released":
            Hound.keyboard_ctrl.release(k)
        elif event == "type":
            Hound.keyboard_ctrl.type(k)

    @staticmethod
    def _process_screen_shot_stmt(file, x, y, width, height):
        """
        Process screen shot matched statement
        :param file: The file to matched
        :param x: The left position
        :param y: The right position
        :param width: The image width
        :param height: The image height
        :return: True if matched, otherwise False
        """
        if pyautogui.locateOnScreen(file, minSearchTime=5, region=(x, y, width, height)) is None:
            return False
        else:
            return True

    @staticmethod
    def _process_check_log_stmt(match_type, log, file):
        """
        Process check log statement
        :param match_type: include or exclude
        :param log: The log to check
        :param file: The log file
        :return: True if fitted, otherwise False
        """
        try:
            with open(file) as f:
                for line in f:
                    if line.find(log) != -1:
                        if match_type == "include":
                            return True
                        else:
                            return False

            if match_type == "include":
                return False
            else:
                return True
        except:
            return False

    @staticmethod
    def _process_run_script_stmt(run_type, script):
        """
        Process run script statement
        :param run_type: The run type, sync/async
        :param script: The script to run
        :return: True if succeed, otherwise False
        """
        return True


def usage(app):
    """
    Print usage
    :param app: The application name
    """
    print("Usage: " + app + " [-h] [-w time] [-n count] -f file")
    print("    -h:       Print help")
    print("    -i:       Ignore error, default False")
    print("    -w time:  Wait for <time>(s) before each running, default 10s")
    print("    -n count: Run time, default 1")
    print("    -f file:  The file to run")


if __name__ == "__main__":
    opts, args = getopt.getopt(sys.argv[1:], "w:n:f:hi")
    file = ""
    wait = 10
    count = 1
    ignored = False

    for opt, value in opts:
        if opt == "w":
            wait = int(value)
        elif opt == "n":
            count = int(value)
        elif opt == "f":
            file = value
        elif opt == "i":
            ignored = True
        else:
            usage(sys.argv[0])
            exit(1)

    if wait < 0 or count <= 0 or file == "":
        usage()
        exit(1)

    while count > 0:
        if wait > 0:
            time.sleep(wait)

        h = Hound()
        if h.run(file):
            print("Process " + file + " success!")
        else:
            print("Process " + file + " failed!")

            if not ignored:
                exit(1)

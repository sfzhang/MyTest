#!/usr/bin/python3


import sys
import time
import pyautogui
import pynput
from pynput.mouse import Button
from pynput.keyboard import Key
import xml.etree.ElementTree as ET


class Hound(object):
    """
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

    button_dict = {"left": Button.left, "middle": Button.middle, "right": Button.right}

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

    mouse_ctrl = pynput.mouse.Controller()
    keyboard_ctrl = pynput.keyboard.Controller()

    def run(self, file):
        tree = ET.parse(file)
        root = tree.getroot()
        for child in root:
            time.sleep(float(child.attrib["interval"]) / 1000000)
            if child.tag == "include":
                if not Hound._process_include_stmt(child.attrib["file"]):
                    print("_process_include_stmt() failed")
                    return False
            elif child.tag == "sleep":
                Hound._process_sleep_stmt(float(child.attrib["seconds"]))
            elif child.tag == "mouse":
                if child.attrib["event"] == "scrolled":
                    Hound._process_mouse_stmt(child.attrib["event"], child.attrib["button"], int(child.attrib["x"]),
                                              int(child.attrib["y"]), int(child.attrib["dx"]), int(child.attrib["dy"]))
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
        hound = Hound()
        return hound.run(file)

    @staticmethod
    def _process_sleep_stmt(seconds):
        time.sleep(seconds)

    @staticmethod
    def _process_mouse_stmt(event, button, x, y, dx=None, dy=None):
        if event == "pressed":
            pyautogui.mouseDown(x, y, button)
        elif event == "released":
            pyautogui.mouseUp(x, y, button)
        elif event == "scrolled":
            pyautogui.scroll(dx + dy, x, y)

    @staticmethod
    def _process_keyboard_stmt(event, key):
        if key in Hound.key_dict:
            k = Hound.key_dict[key]
        else:
            k = key

        if event == "pressed":
            Hound.keyboard_ctrl.press(k)
        elif event == "released":
            Hound.keyboard_ctrl.release(k)

    @staticmethod
    def _process_screen_shot_stmt(file, x, y, width, height):
        if pyautogui.locateOnScreen(file, minSearchTime=5, region=(x, y, width, height)) is None:
            return False
        else:
            return True

    @staticmethod
    def _process_check_log_stmt(match_type, log, file):
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
        return True


if __name__ == "__main__":
    if len(sys.argv) != 2:
        print("Usage: " + sys.argv[0] + " file")
    else:
        h = Hound()
        if h.run(sys.argv[1]):
            print("Auto test success!")
        else:
            print("Auto test failed!")

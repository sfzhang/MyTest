#!/usr/bin/python3


import queue
import signal
from pynput import keyboard


class KeyboardEvent(object):
    """
    Message protocol:
        [type message]
        type:
            0: Mouse event
            1: Keyboard event
            2: Screen shot event
            3: Log event
        
    Keyboard event message:
        [event key]
        event:
            0: Pressed
            1: Released
        key:
            alt/alt_gr/alt_l/alt_r/backspace/caps_lock/cmd/cmd_l/cmd_r/ctrl/ctrl_l/ctrl_r/delete/down/end/enter/esc/
            f1-f20/home/insert/left/menu/num_lock/page_down/page_up/pause/print_screen/right/scroll_lock/shift/shift_l/
            shift_r/space/tab/up/...
    """

    def __init__(self, q):
        signal.signal(signal.SIGINT, signal.SIG_IGN)
        signal.signal(signal.SIGQUIT, signal.SIG_IGN)
        signal.signal(signal.SIGTSTP, signal.SIG_IGN)
        self.q = q
        self.event = 0
        self.key = None
        self.listener = keyboard.Listener(on_press=self.on_press, on_release=self.on_release)
        self.listener.start()

    def _send(self):
        msg = "1 " + str(self.event) + " " + self.key
        self.q.put(msg)

    def stop(self):
        self.listener.stop()

    def join(self):
        self.listener.join()

    def on_press(self, key):
        try:
            print('alphanumeric key {0} pressed'.format(key.char))
            self.key = key.char
        except AttributeError:
            print('special key {0} pressed'.format(key))
            self.key = str(key).split('.')[1]

        self.event = 0
        self._send()

    def on_release(self, key):
        try:
            print('alphanumeric key {0} released'.format(key.char))
            self.key = key.char
        except AttributeError:
            print('special key {0} released'.format(key))
            self.key = str(key).split('.')[1]

        self.event = 1
        self._send()


if __name__ == '__main__':
    q = queue.Queue()
    k = KeyboardEvent(q)
    k.join()

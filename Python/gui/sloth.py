#!/usr/bin/python3


import queue
import datetime
import mouseevent
import keyboardevent
import screenshot


"""
Message protocol:
    [type message]
        type:
            0: Mouse event
            1: Keyboard event
            2: Screen shot event
            3: Log event
        
Mouse event message:
    [button event x|y dx|dy]
        button:
            0: No button
            1: Left
            2: Right
            3: Middle
        event:
            0: None
            1: Pressed
            2: Released
            3: Scrolled
        x|y:
            x and y position
        dx|dy:
            dx and dy exist when scrolled

Keyboard event message:
    [event key]
        event:
            0: Pressed
            1: Released
        key:
            alt/alt_gr/alt_l/alt_r/backspace/caps_lock/cmd/cmd_l/cmd_r/ctrl/ctrl_l/ctrl_r/delete/down/end/enter/esc/
            f1-f20/home/insert/left/menu/num_lock/page_down/page_up/pause/print_screen/right/scroll_lock/shift/shift_l/
            shift_r/space/tab/up

Screen shot event:
    [x|y w|h file]
        x|y:
            top left position
        w|h:
            image width and height
        file:
            The saved file path name
"""


q = queue.Queue()
timeout = None

m = mouseevent.MouseEvent(q)
k = keyboardevent.KeyboardEvent(q)


while True:
    msg = q.get()
    print(msg)

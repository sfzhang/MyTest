#!/usr/bin/python3


import queue
from pynput import mouse


class MouseEvent(object):
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
    """

    def __init__(self, q):
        self.q = q
        self.button = 0
        self.event = 0
        self.x = 0
        self.y = 0
        self.dx = 0
        self.dy = 0
        self.listener = mouse.Listener(on_move=self.on_move, on_click=self.on_click, on_scroll=self.on_scroll)
        self.listener.start()

    def _send(self):
        msg = "0 " + str(self.button) + " " + str(self.event) + " " + str(self.x) + "|" + str(self.y)
        if self.event == 3:
            msg += " " + str(self.dx) + "|" + str(self.dy)

        self.q.put(msg)

    def stop(self):
        self.listener.stop()

    def join(self):
        self.listener.join()

    def on_move(self, x, y):
        self.x = x
        self.y = y

    def on_click(self, x, y, button, pressed):
        print('{0} at {1} with button {2}'.format('Pressed' if pressed else 'Released', (x, y), button))

        self.x, self.y = x, y
        if button == mouse.Button.left:
            self.button = 1
        elif button == mouse.Button.right:
            self.button = 2
        elif button == mouse.Button.middle:
            self.button = 3
        else:
            self.button = 0

        if pressed:
            self.event = 1
        else:
            self.event = 2

        if self.button != 0:
            self._send()

    def on_scroll(self, x, y, dx, dy):
        print('Scrolled {0} at {1} with ({2})'.format('down' if dy < 0 else 'up', (x, y), (dx, dy)))

        self.button = 0
        self.event = 3
        self.x, self.y = x, y
        self.dx, self.dy = dx, dy

        self._send()


if __name__ == '__main__':
    q = queue.Queue()
    m = MouseEvent(q)
    m.join()

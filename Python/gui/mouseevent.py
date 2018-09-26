#!/usr/bin/python3


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
        msg = "mouse " + self.event + " " + self.button + " " + str(self.x) + "," + str(self.y)
        if self.event == "scrolled":
            msg += " " + str(self.dx) + "," + str(self.dy)
        self.q.put(msg)

    def stop(self):
        self.listener.stop()

    def join(self):
        self.listener.join()

    def on_move(self, x, y):
        pass

    def on_click(self, x, y, button, pressed):
        # print('{0} at {1} with button {2}'.format('Pressed' if pressed else 'Released', (x, y), button))

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
        # print('Scrolled {0} at {1} with ({2})'.format('down' if dy < 0 else 'up', (x, y), (dx, dy)))

        self.event = "scrolled"
        self.button = "none"
        self.x, self.y = x, y
        self.dx, self.dy = dx, dy

        self._send()


if __name__ == '__main__':
    q = Queue()
    m = MouseEvent(q)
    m.join()

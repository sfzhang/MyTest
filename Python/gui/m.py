#!/usr/bin/python3

from pynput import mouse, keyboard

mouse_pressed = False
def on_move(x, y):
    if mouse_pressed:
        print('Point moved to {0}'.format((x, y)))

def on_click(x, y, button, pressed):
    print('{0} at {1} with button {2}'.format('Pressed' if pressed else 'Released', (x, y), button))
    if pressed:
        mouse_pressed = True
    else:
        mouse_pressed = False

def on_scroll(x, y, dx, dy):
    print('Scrolled {0} at {1} with ({2})'.format('down' if dy < 0 else 'up', (x, y), (dx, dy)))

def on_press(key):
    try:
        print('alphanumeric key {0} pressed'.format(key.char))
    except AttributeError:
        print('special key {0} pressed'.format(key))

def on_release(key):
    print('{0} released'.format(key))
    print('\ttype {0}'.format(key))


mouse_listener = mouse.Listener(on_move=on_move, on_click=on_click, on_scroll=on_scroll)
mouse_listener.start()

key_listener = keyboard.Listener(on_press=on_press, on_release=on_release)
key_listener.start()

mouse_listener.join()
key_listener.join()

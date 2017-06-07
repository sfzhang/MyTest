#include <cstdio>
#include <cstdlib>
#include <cstring>

#include <unistd.h>
#include <X11/X.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/keysym.h>
#include <X11/extensions/XTest.h>

Display *display;
Window root;

void init()
{
    display = XOpenDisplay(NULL);
    if (!display) {
        fprintf(stderr, "XOpenDisplay() failed");
        return;
    }

    root = DefaultRootWindow(display);
}

void getCursorPos(int *x, int *y)
{
    int tmp = 0;
    unsigned int tmp2 = 0;
    Window fromroot, tmpwin;

    XQueryPointer(display, root, &fromroot, &tmpwin, x, y, &tmp,
                  &tmp, &tmp2);
}

void setCursorPos(int x, int y)
{
    int tmp;
    XWarpPointer(display, None, root, 0, 0, 0, 0, x, y);
    XFlush(display);
}

void click(int button)
{
    Display *display = XOpenDisplay(NULL);

    XEvent event;

    if(display == NULL)
    {
        printf("Errore nell'apertura del Display !!!\n");
        return;
    }

    memset(&event, 0x00, sizeof(event));

    event.type = ButtonPress;
    event.xbutton.button = button;
    event.xbutton.same_screen = True;

    XQueryPointer(display, RootWindow(display, DefaultScreen(display)), &event.xbutton.root, &event.xbutton.window, &event.xbutton.x_root, &event.xbutton.y_root, &event.xbutton.x, &event.xbutton.y, &event.xbutton.state);

    event.xbutton.subwindow = event.xbutton.window;

    while(event.xbutton.subwindow)
    {
        event.xbutton.window = event.xbutton.subwindow;

        XQueryPointer(display, event.xbutton.window, &event.xbutton.root, &event.xbutton.subwindow, &event.xbutton.x_root, &event.xbutton.y_root, &event.xbutton.x, &event.xbutton.y, &event.xbutton.state);
    }

    if(XSendEvent(display, PointerWindow, True, 0xfff, &event) == 0) printf("Errore nell'invio dell'evento !!!\n");

    XFlush(display);


    usleep(10000);

    event.type = ButtonRelease;
    event.xbutton.state = 0x100;

    if(XSendEvent(display, PointerWindow, True, 0xfff, &event) == 0) printf("Errore nell'invio dell'evento !!!\n");

    XFlush(display);

    XCloseDisplay(display);
}

void input()
{
    int keysym = XK_1;
    for (int i = 0; i < 10; i++) {
        keysym = XK_1 + i;

        sleep(1);
        XTestFakeKeyEvent (display, XKeysymToKeycode(display, keysym), True, CurrentTime);
        XTestFakeKeyEvent (display, XKeysymToKeycode(display, keysym), False, CurrentTime);
    }
}

int main(int argc, char *argv[])
{
    init();

    int x = 0;
    int y = 0;

    if (3 == argc) {
        setCursorPos(atoi(argv[1]), atoi(argv[2]));
        click(Button1);

        sleep(5);
        input();
    }

    while (1) {
        getCursorPos(&x, &y);
        printf("x[%d], y[%d]\n", x, y);
        sleep(1);
    }

    return 0;
}

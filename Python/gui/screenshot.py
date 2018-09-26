#!/usr/bin/python3


import os
import pyautogui
import datetime
from multiprocessing import Queue
from PyQt5.QtCore import *
from PyQt5.QtGui import *
from PyQt5.QtWidgets import *
from PIL.ImageQt import *
from enum import Enum


class HitPos(Enum):
    none = 0
    left = 1
    top = 2
    right = 3
    bottom = 4
    top_left = 5
    top_right = 6
    bottom_right = 7
    bottom_left = 8
    center = 9


class Rect(object):

    hit_ext = 3

    def __init__(self, width, height):
        self.width = width
        self.height = height
        self.rect = None
        self.hit_pos = HitPos.none
        self.m_prev_point = None

    def _correct_position(self, point):
        if point.x() < 0:
            x = 0
        elif point.x() > self.width:
            x = self.width
        else:
            x = point.x()

        if point.y() < 0:
            y = 0
        elif point.y() > self.height:
            y = self.height
        else:
            y = point.y()

        return QPoint(x, y)

    def _draw_text(self, painter):
        rect = self.rect.normalized()

        text = "{}x{}".format(rect.width(), rect.height())
        fm = QFontMetrics(QFont())
        bound_rect = fm.boundingRect(text)
        bound_rect.setWidth(bound_rect.width() + 5)
        bound_rect.setHeight(bound_rect.height() + 5)

        x = rect.left() + 10
        if rect.top() - bound_rect.height() >= 10:
            y = rect.top() - 10 - bound_rect.height()
        else:
            y = rect.top() + 10

        painter.save()
        painter.setPen(QPen(QColor(36, 36, 36)))
        painter.setBrush(QBrush(QColor(36, 36, 36)))
        painter.drawRect(QRect(x, y, bound_rect.width(), bound_rect.height()))

        painter.setPen(QPen(QColor(0, 255, 0)))
        painter.drawText(QRect(x, y, bound_rect.width(), bound_rect.height()), Qt.AlignVCenter | Qt.AlignHCenter, text)
        painter.restore()

    def left(self):
        return self.rect.left()

    def right(self):
        return self.rect.right()

    def top(self):
        return self.rect.top()

    def bottom(self):
        return self.rect.bottom()

    def center(self):
        return self.rect.center()

    def w(self):
        return self.rect.width()

    def h(self):
        return self.rect.height()

    def valid(self):
        return self.rect is not None

    def reset(self):
        self.rect = None
        self.hit_pos = HitPos.none
        self.m_prev_point = None

    def hit(self, point):
        self.hit_pos = HitPos.none
        if self.valid():
            point_list = ((HitPos.left, QPoint(self.rect.left(), self.rect.center().y())),
                          (HitPos.top, QPoint(self.rect.center().x(), self.rect.top())),
                          (HitPos.right, QPoint(self.rect.right(), self.rect.center().y())),
                          (HitPos.bottom, QPoint(self.rect.center().x(), self.rect.bottom())),
                          (HitPos.top_left, QPoint(self.rect.left(), self.rect.top())),
                          (HitPos.top_right, QPoint(self.rect.right(), self.rect.top())),
                          (HitPos.bottom_right, QPoint(self.rect.right(), self.rect.bottom())),
                          (HitPos.bottom_left, QPoint(self.rect.left(), self.rect.bottom())))

            for p in point_list:
                rect = QRect(p[1].x() - Rect.hit_ext, p[1].y() - Rect.hit_ext, 2 * Rect.hit_ext, 2 * Rect.hit_ext)
                if rect.contains(point):
                    self.hit_pos = p[0]
                    return self.hit_pos

            if self.rect.contains(point):
                self.hit_pos = HitPos.center
                return self.hit_pos
        else:
            return self.hit_pos

    def display(self, painter):
        if self.valid():
            painter.save()
            painter.setPen(QPen(QColor(0, 255, 0)))

            # Draw shape
            painter.drawRect(self.rect)

            painter.setBrush(QBrush(QColor(0, 255, 0)))
            point_list = (QPoint(self.rect.left(), self.rect.center().y()),
                          QPoint(self.rect.center().x(), self.rect.top()),
                          QPoint(self.rect.right(), self.rect.center().y()),
                          QPoint(self.rect.center().x(), self.rect.bottom()),
                          QPoint(self.rect.left(), self.rect.top()),
                          QPoint(self.rect.right(), self.rect.top()),
                          QPoint(self.rect.right(), self.rect.bottom()),
                          QPoint(self.rect.left(), self.rect.bottom()))
            for p in point_list:
                painter.drawRect(QRect(p.x() - Rect.hit_ext, p.y() - Rect.hit_ext, 2 * Rect.hit_ext, 2 * Rect.hit_ext))

            # Draw text
            self._draw_text(painter)

            painter.restore()

    def start_drawing(self, point):
        self.reset()
        self.m_prev_point = self._correct_position(point)

    def drawing(self, point):
        self.rect = QRect(self.m_prev_point, self._correct_position(point)).normalized()

    def finish_drawing(self, point):
        self.drawing(self._correct_position(point))
        self.rect = self.rect.normalized()

    def start_adjust(self, point):
        self.m_prev_point = self._correct_position(point)

    def adjusting(self, point):
        point = self._correct_position(point)
        if self.hit_pos == HitPos.none:
            return
        elif self.hit_pos == HitPos.left:
            self.rect.adjust(point.x() - self.m_prev_point.x(), 0, 0, 0)
            self.m_prev_point = point
        elif self.hit_pos == HitPos.right:
            self.rect.adjust(0, 0, point.x() - self.m_prev_point.x(), 0)
            self.m_prev_point = point
        elif self.hit_pos == HitPos.top:
            self.rect.adjust(0, point.y() - self.m_prev_point.y(), 0, 0)
            self.m_prev_point = point
        elif self.hit_pos == HitPos.bottom:
            self.rect.adjust(0, 0, 0, point.y() - self.m_prev_point.y())
            self.m_prev_point = point
        elif self.hit_pos == HitPos.top_left:
            self.rect.adjust(point.x() - self.m_prev_point.x(), point.y() - self.m_prev_point.y(), 0, 0)
            self.m_prev_point = point
        elif self.hit_pos == HitPos.top_right:
            self.rect.adjust(0, point.y() - self.m_prev_point.y(), point.x() - self.m_prev_point.x(), 0)
            self.m_prev_point = point
        elif self.hit_pos == HitPos.bottom_right:
            self.rect.adjust(0, 0, point.x() - self.m_prev_point.x(), point.y() - self.m_prev_point.y())
            self.m_prev_point = point
        elif self.hit_pos == HitPos.bottom_left:
            self.rect.adjust(point.x() - self.m_prev_point.x(), 0, 0, point.y() - self.m_prev_point.y())
            self.m_prev_point = point
        elif self.hit_pos == HitPos.center:
            self.rect.moveCenter(self.rect.center() + point - self.m_prev_point)
            dx = self.rect.left() if self.rect.left() < 0 else \
                (self.rect.right() - self.width if self.rect.right() > self.width else 0)
            dy = self.rect.top() if self.rect.top() < 0 else \
                (self.rect.bottom() - self.height if self.rect.bottom() > self.height else 0)

            self.rect.moveCenter(self.rect.center() - QPoint(dx, dy))
            self.m_prev_point = point - QPoint(dx, dy)

    def finish_adjusting(self, point):
        self.adjusting(point)
        self.rect = self.rect.normalized()


class ToolBar(QToolBar):

    save_clicked = pyqtSignal()
    ok_clicked = pyqtSignal()
    redo_clicked = pyqtSignal()
    exit_clicked = pyqtSignal()

    def __init__(self, parent=None):
        super(ToolBar, self).__init__(parent=parent)
        self.setMovable(False)
        self.setFloatable(True)

        path = os.path.dirname(os.path.realpath(__file__))
        self.addAction(QIcon(path + "/save.png"), "Save as...", self.save_clicked.emit)
        self.addAction(QIcon(path + "/ok.png"), "OK", self.ok_clicked.emit)
        self.addAction(QIcon(path + "/redo.png"), "Redo", self.redo_clicked.emit)
        self.addAction(QIcon(path + "/exit.png"), "Exit", self.exit_clicked.emit)

        self.setStyleSheet("QToolBar{background-color: white;\nborder: 1px solid gray;}")


class ActionState(Enum):
    idle = 0
    drawing = 1
    adjusting = 2


class ScreenShot(QWidget):

    def __init__(self, parent=None, q=None, screen_shot=None):
        super(ScreenShot, self).__init__(parent=parent)
        self.setWindowFlags(Qt.FramelessWindowHint)
        self.setMouseTracking(True)

        self.q = q
        self.file = None
        if screen_shot is not None:
            self.image = screen_shot
            self.screen_shot = ImageQt(screen_shot)
        else:
            self.screen_shot = None

        self.x = -1
        self.y = -1

        self.image_width = 40
        self.image_height = 40
        self.magnifier_width = 200
        self.magnifier_height = 200
        self.text_height = 50
        self.display_magnifier = True

        self.state = ActionState.idle

        desktop = QApplication.desktop()
        screen = desktop.screenGeometry()
        self.rect = Rect(screen.width(), screen.height())

        self.tool = ToolBar(self)
        self.tool.save_clicked.connect(self.save)
        self.tool.redo_clicked.connect(self.redo)
        self.tool.ok_clicked.connect(self.accept)
        self.tool.exit_clicked.connect(self.close)

    @staticmethod
    def _get_default_name():
        return datetime.datetime.now().strftime("screenshot-%Y%m%d-%H%M%S")

    def _save_image(self, file, fmt="png"):
        crop_image = self.image.crop((self.rect.left(), self.rect.top(), self.rect.right(), self.rect.bottom()))
        crop_image.save(file + "." + fmt, fmt)
        self.file = file + "." + fmt

    def _exit(self):
        msg = "screen_shot "
        if self.q is not None:
            if self.rect is not None:
                msg += str(self.x) + "," + str(self.y) + " " + str(self.rect.w()) + "," + str(self.rect.h()) + " " + \
                       self.file.replace(' ', '\x00')
            self.q.put(msg)
        self.close()

    def _correct_position(self, point):
        if point.x() < 0:
            self.x = 0
        elif point.x() > self.width():
            self.x = self.width()
        else:
            self.x = point.x()

        if point.y() < 0:
            self.y = 0
        elif point.y() > self.height():
            self.y = self.height()
        else:
            self.y = point.y()

    def _set_cursor(self, hit_pos):
        if hit_pos == HitPos.left or hit_pos == HitPos.right:
            self.setCursor(Qt.SizeHorCursor)
        elif hit_pos == HitPos.top or hit_pos == HitPos.bottom:
            self.setCursor(Qt.SizeVerCursor)
        elif hit_pos == HitPos.top_left or hit_pos == HitPos.bottom_right:
            self.setCursor(Qt.SizeFDiagCursor)
        elif hit_pos == HitPos.top_right or hit_pos == HitPos.bottom_left:
            self.setCursor(Qt.SizeBDiagCursor)
        elif hit_pos == HitPos.center:
            self.setCursor(Qt.SizeAllCursor)
        else:
            self.setCursor(Qt.ArrowCursor)

    def _get_magnifier_pos(self):
        off_x = 20
        off_y = 20
        width = off_x + self.magnifier_width
        height = off_y + self.magnifier_height + self.text_height

        if self.x + width > self.width() and self.x - width >= 0:
            x = self.x - width
        else:
            x = self.x + off_x

        if self.y + height > self.height() and self.y - height >= 0:
            y = self.y - height
        else:
            y = self.y + off_y

        return x, y

    def _get_rgb(self):
        rgb = self.screen_shot.pixel(self.x, self.y)
        return qRed(rgb), qGreen(rgb), qBlue(rgb)

    def _display_magnifier(self, painter):
        if self.screen_shot is not None and self.x >= 0 and self.y >= 0:
            x, y = self._get_magnifier_pos()

            painter.save()
            painter.setBrush(QBrush(QColor(36, 36, 36)))
            painter.setPen(QPen(QColor(36, 36, 36)))

            # Draw background
            painter.drawRect(x, y, self.magnifier_width, self.magnifier_height + self.text_height)

            # Draw image
            left = self.x - self.image_width / 2 if self.x - self.image_width / 2 > 0 else 0
            top = self.y - self.image_height / 2 if self.y - self.image_height / 2 > 0 else 0
            right = self.x + self.image_width / 2 if self.x + self.image_width / 2 < self.width() else self.width()
            bottom = self.y + self.image_height / 2 if self.y + self.image_height / 2 < self.height() else self.height()

            width = right - left
            height = bottom - top

            dest_width = 1.0 * self.magnifier_width * width / self.image_width
            dest_height = 1.0 * self.magnifier_height * height / self.image_height
            dest_left = x + self.magnifier_width / 2 - self.magnifier_width * (self.x - left) / self.image_width
            dest_top = y + self.magnifier_height / 2 - self.magnifier_height * (self.y - top) / self.image_height

            painter.drawImage(QRectF(dest_left, dest_top, dest_width, dest_height), self.screen_shot,
                              QRectF(left, top, width, height))

            # Draw frame
            painter.setPen(QPen(QColor(0, 255, 0)))
            painter.drawLine(x, y, x + self.magnifier_width, y)
            painter.drawLine(x + self.magnifier_width, y, x + self.magnifier_width, y + self.magnifier_height)
            painter.drawLine(x + self.magnifier_width, y + self.magnifier_height, x, y + self.magnifier_height)
            painter.drawLine(x, y + self.magnifier_height, x, y)

            painter.drawLine(x + self.magnifier_width / 2, y, x + self.magnifier_width / 2, y + self.magnifier_height)

            painter.drawLine(x, y + self.magnifier_height / 2, x + self.magnifier_width, y + self.magnifier_height / 2)

            # Draw text
            r, g, b = self._get_rgb()
            text = "POS: ({}, {})\nRGB: ({}, {}, {})".format(self.x, self.y, r, g, b)
            painter.drawText(QRectF(x + 10, y + self.magnifier_height, self.magnifier_width - 20, self.text_height),
                             Qt.AlignLeft | Qt.AlignVCenter, text)

            painter.restore()

    def _hide_tool(self):
        self.tool.hide()
        self.display_magnifier = True
        self.update()

    def _show_tool(self):
        x = self.rect.right() - self.tool.width() if self.rect.right() - self.tool.width() > 0 else 0
        y = self.rect.bottom() + 5 if self.rect.bottom() + 5 + self.tool.height() <= self.height() else \
            self.rect.bottom() - 5 - self.tool.height()

        self.tool.move(x, y)
        self.tool.show()

        self.display_magnifier = False
        self.update()

    def showEvent(self, e):
        self._hide_tool()
        super(ScreenShot, self).showEvent(e)

    def enterEvent(self, e):
        if not self.rect.valid():
            self.display_magnifier = True
            self.update()
        super(ScreenShot, self).enterEvent(e)

    def leaveEvent(self, e):
        if self.display_magnifier:
            self.display_magnifier = False
            self.update()
        super(ScreenShot, self).leaveEvent(e)

    def mousePressEvent(self, e):
        self.x, self.y = e.pos().x(), e.pos().y()

        if not self.rect.valid():
            self.state = ActionState.drawing
            self.rect.start_drawing(e.pos())
        elif self.rect.hit(e.pos()) != HitPos.none:
            self._hide_tool()
            self.state = ActionState.adjusting
            self.rect.start_adjust(e.pos())
        else:
            self.state = ActionState.idle

        self.update()
        super(ScreenShot, self).mousePressEvent(e)

    def mouseMoveEvent(self, e):
        self._correct_position(e.pos())
        if self.state == ActionState.drawing:
            self.rect.drawing(e.pos())
        elif self.state == ActionState.adjusting:
            self.rect.adjusting(e.pos())
        elif self.rect.valid():
            hit_pos = self.rect.hit(e.pos())
            self._set_cursor(hit_pos)

        self.update()
        super(ScreenShot, self).mouseMoveEvent(e)

    def mouseReleaseEvent(self, e):
        self._correct_position(e.pos())
        if self.state == ActionState.drawing:
            self.rect.finish_drawing(e.pos())
            self.setCursor(Qt.ArrowCursor)
        elif self.state == ActionState.adjusting:
            self.rect.finish_adjusting(e.pos())

        self.state = ActionState.idle
        hit_pos = self.rect.hit(e.pos())
        self._set_cursor(hit_pos)
        self._show_tool()

        self.update()
        super(ScreenShot, self).mouseReleaseEvent(e)

    def paintEvent(self, e):
        painter = QPainter(self)

        if self.screen_shot is not None:
            painter.drawImage(0, 0, self.screen_shot)

            if self.rect.valid():
                self.rect.display(painter)

            if self.display_magnifier:
                self._display_magnifier(painter)

        super(ScreenShot, self).paintEvent(e)

    def keyPressEvent(self, e):
        if e.key() == Qt.Key_Escape:
            self.rect = None
            self._exit()
        else:
            super(ScreenShot, self).keyPressEvent(e)

    @pyqtSlot()
    def save(self):
        default_file = "./" + ScreenShot._get_default_name()
        png_filter = "PNG image (*.png)"
        bmp_filter = "BMP image (*.bmp)"
        result = QFileDialog.getSaveFileName(self, "Save as", default_file, png_filter + ";;" + bmp_filter)
        if len(result) == 2 and len(result[0]) > 0:
            if result[1] == png_filter:
                self._save_image(os.path.splitext(result[0])[0], "png")
            else:
                self._save_image(os.path.splitext(result[0])[0], "bmp")
            self._exit()

    @pyqtSlot()
    def redo(self):
        self.rect.reset()
        self.tool.hide()
        self.display_magnifier = True
        self.update()

    @pyqtSlot()
    def accept(self):
        file = os.path.dirname(os.path.realpath(__file__)) + "/" + ScreenShot._get_default_name()
        self._save_image(file)
        self._exit()


def get_screen_shot(q):
    app = QApplication(sys.argv)
    screen_shot = pyautogui.screenshot()
    widget = ScreenShot(q=q, screen_shot=screen_shot)
    widget.showFullScreen()
    sys.exit(app.exec())


if __name__ == "__main__":
    q = Queue()
    get_screen_shot(q)

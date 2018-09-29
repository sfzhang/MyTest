#!/usr/bin/python3


import os
import sys
from multiprocessing import Queue
from PyQt5.QtWidgets import *
from PyQt5.QtGui import *
from PyQt5.QtCore import *


class Waiting(QDialog):

    def __init__(self, parent=None, q=None):
        super(Waiting, self).__init__(parent=parent)

        self.q = q

        path = os.path.dirname(os.path.realpath(__file__))
        self.wait_label = QLabel("Waiting(s): ")
        self.wait_line_edit = QLineEdit()

        validator = QDoubleValidator()
        self.wait_line_edit.setValidator(validator)

        self.ok_btn = QPushButton(QIcon(path + "/ok.png"), "")
        self.cancel_btn = QPushButton(QIcon(path + "/exit.png"), "")
        self.ok_btn.setDefault(True)

        self.hbox_layout = QHBoxLayout()
        self.hbox_layout.addWidget(self.wait_label)
        self.hbox_layout.addWidget(self.wait_line_edit, 2)
        self.hbox_layout.addSpacing(1)
        self.hbox_layout.addWidget(self.ok_btn)
        self.hbox_layout.addWidget(self.cancel_btn)

        self.setLayout(self.hbox_layout)
        self.setMinimumSize(400, 50)

        self.ok_btn.clicked.connect(self.accept)
        self.cancel_btn.clicked.connect(self.reject)

    @pyqtSlot()
    def _exit(self):
        msg = "waiting "
        if self.q is not None:
            if len(self.wait_line_edit.text()) > 0:
                msg += self.wait_line_edit.text()
            self.q.put(msg)

    @pyqtSlot()
    def accept(self):
        self._exit()
        super(Waiting, self).accept()

    @pyqtSlot()
    def reject(self):
        self._exit()
        super(Waiting, self).reject()


def get_waiting(q):
    try:
        app = QApplication(sys.argv)
        widget = Waiting(q=q)
        widget.show()
        sys.exit(app.exec())
    except Exception as e:
        print(e)


if __name__ == "__main__":
    q = Queue()
    get_waiting(q)

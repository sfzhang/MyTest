#!/usr/bin/python3


import os
import sys
from multiprocessing import Queue
from PyQt5.QtWidgets import *
from PyQt5.QtGui import *
from PyQt5.QtCore import *


class RunScript(QDialog):

    def __init__(self, parent=None, q=None):
        super(RunScript, self).__init__(parent=parent)

        self.q = q

        path = os.path.dirname(os.path.realpath(__file__))
        self.file_label = QLabel("Script: ")
        self.file_line_edit = QLineEdit()
        self.type_cbb = QComboBox()
        self.type_cbb.addItem("sync")
        self.type_cbb.addItem("async")
        self.open_btn = QPushButton(QIcon(path + "/open.png"), "")

        self.ok_btn = QPushButton(QIcon(path + "/ok.png"), "")
        self.cancel_btn = QPushButton(QIcon(path + "/exit.png"), "")

        self.hbox_layout = QHBoxLayout()
        self.hbox_layout.addWidget(self.file_label)
        self.hbox_layout.addWidget(self.file_line_edit, 2)
        self.hbox_layout.addWidget(self.type_cbb)
        self.hbox_layout.addWidget(self.open_btn)
        self.hbox_layout.addSpacing(1)
        self.hbox_layout.addWidget(self.ok_btn)
        self.hbox_layout.addWidget(self.cancel_btn)

        self.setLayout(self.hbox_layout)
        self.setMinimumSize(800, 50)

        self.open_btn.clicked.connect(self.open_file)
        self.ok_btn.clicked.connect(self.accept)
        self.cancel_btn.clicked.connect(self.reject)

    @pyqtSlot()
    def _exit(self):
        msg = "run_script "
        if self.q is not None:
            if len(self.file_line_edit.text()) > 0:
                msg += self.type_cbb.currentText() + " " + self.file_line_edit.text().replace(' ', '\x00')
            self.q.put(msg)

    @pyqtSlot()
    def accept(self):
        self._exit()
        super(RunScript, self).accept()

    @pyqtSlot()
    def reject(self):
        self._exit()
        super(RunScript, self).reject()

    @pyqtSlot()
    def open_file(self):
        file = QFileDialog.getOpenFileName(self, "Run script", filter="python script(*.py)")
        if len(file) > 0 and len(file[0]) > 0:
            self.file_line_edit.setText(file[0])


def get_run_script(q):
    try:
        app = QApplication(sys.argv)
        widget = RunScript(q=q)
        widget.show()
        sys.exit(app.exec())
    except Exception as e:
        print(e)


if __name__ == "__main__":
    q = Queue()
    get_run_script(q)

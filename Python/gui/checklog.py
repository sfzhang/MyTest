#!/usr/bin/python3


import os
import sys
from multiprocessing import Queue
from PyQt5.QtWidgets import *
from PyQt5.QtGui import *
from PyQt5.QtCore import *


class CheckLog(QDialog):

    def __init__(self, parent=None, q=None):
        super(CheckLog, self).__init__(parent=parent)

        self.q = q

        path = os.path.dirname(os.path.realpath(__file__))
        self.file_label = QLabel("File: ")
        self.file_line_edit = QLineEdit()
        self.type_cbb = QComboBox()
        self.type_cbb.addItem("Include")
        self.type_cbb.addItem("Exclude")
        self.open_btn = QPushButton(QIcon(path + "/open.png"), "")

        self.hbox_layout1 = QHBoxLayout()
        self.hbox_layout1.addWidget(self.file_label)
        self.hbox_layout1.addWidget(self.file_line_edit, 2)
        self.hbox_layout1.addWidget(self.type_cbb)
        self.hbox_layout1.addWidget(self.open_btn)

        self.log_label = QLabel("Log: ")
        self.log_text_edit = QTextEdit()

        self.hbox_layout2 = QHBoxLayout()
        self.hbox_layout2.addWidget(self.log_label)
        self.hbox_layout2.addWidget(self.log_text_edit)

        self.ok_btn = QPushButton(QIcon(path + "/ok.png"), "")
        self.cancel_btn = QPushButton(QIcon(path + "/exit.png"), "")

        self.hbox_layout3 = QHBoxLayout()
        self.hbox_layout3.addStretch(2)
        self.hbox_layout3.addWidget(self.ok_btn)
        self.hbox_layout3.addWidget(self.cancel_btn)

        self.vbox_layout = QVBoxLayout()
        self.vbox_layout.addLayout(self.hbox_layout1)
        self.vbox_layout.addLayout(self.hbox_layout2)
        self.vbox_layout.addLayout(self.hbox_layout3)

        self.setLayout(self.vbox_layout)
        self.setMinimumSize(800, 256)

        self.open_btn.clicked.connect(self.open_file)
        self.ok_btn.clicked.connect(self.accept)
        self.cancel_btn.clicked.connect(self.reject)

    @pyqtSlot()
    def _exit(self):
        msg = "check_log "
        if self.q is not None:
            if len(self.file_line_edit.text()) > 0 and len(self.log_text_edit.toPlainText()) > 0:
                msg += self.type_cbb.currentText() + " " + self.file_line_edit.text().replace(' ', '\x00') + " " + \
                       self.log_text_edit.toPlainText().replace(' ', '\x00')
            self.q.put(msg)

    @pyqtSlot()
    def accept(self):
        self._exit()
        super(CheckLog, self).accept()

    @pyqtSlot()
    def reject(self):
        self._exit()
        super(CheckLog, self).reject()

    @pyqtSlot()
    def open_file(self):
        file = QFileDialog.getOpenFileName(self, "Check log", filter="log file (*.log);; All file(*.*)")
        if len(file) > 0 and len(file[0]) > 0:
            self.file_line_edit.setText(file[0])
            os.system("gedit " + file[0])


def get_check_log(q):
    try:
        app = QApplication(sys.argv)
        widget = CheckLog(q=q)
        widget.show()
        sys.exit(app.exec())
    except Exception as e:
        print(e)


if __name__ == "__main__":
    q = Queue()
    get_check_log(q)
#!/usr/bin/python3
#
# Copyright (c) 2018, Shendehc Co., Ltd. All rights reserved.
#
# THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF SHENDEHC CO., LTD.
# AND IS PROTECTED AS AN UNPUBLISHED WORK UNDER APPLICABLE COPYRIGHT
# LAWS.
#
# The contents of this file may not be disclosed to third parties,
# copied or duplicated in any form, in whole or in part, without the
# prior written permission of Shendehc Co., Ltd.
#
# Author: sfzhang(shengfazhang@shendehc.com)
#
# -*- coding: utf-8 -*-

import os
import sys
from multiprocessing import Queue
from PyQt5.QtWidgets import *
from PyQt5.QtGui import *
from PyQt5.QtCore import *


class IncludeFile(QDialog):
    """
    Add include file
    """

    def __init__(self, parent=None, q=None):
        """
        Initialized
        :param parent: The parent widget
        :param q: The queue for multiprocessing
        """
        super(IncludeFile, self).__init__(parent=parent)
        self.setWindowTitle("Add include file")

        self.q = q

        path = os.path.dirname(os.path.realpath(__file__))
        self.file_label = QLabel("file: ")
        self.file_line_edit = QLineEdit()
        self.open_btn = QPushButton(QIcon(path + "/open.png"), "")

        self.ok_btn = QPushButton(QIcon(path + "/ok.png"), "")
        self.cancel_btn = QPushButton(QIcon(path + "/exit.png"), "")
        self.ok_btn.setDefault(True)

        self.hbox_layout = QHBoxLayout()
        self.hbox_layout.addWidget(self.file_label)
        self.hbox_layout.addWidget(self.file_line_edit, 2)
        self.hbox_layout.addSpacing(1)
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
        """
        Send include file event
        """
        msg = "include "
        if self.q is not None:
            if len(self.file_line_edit.text()) > 0:
                msg += self.file_line_edit.text().replace(' ', '\x00')
            self.q.put(msg)

    @pyqtSlot()
    def accept(self):
        """
        Accept
        """
        self._exit()
        super(IncludeFile, self).accept()

    @pyqtSlot()
    def reject(self):
        """
        Reject
        """
        self._exit()
        super(IncludeFile, self).reject()

    @pyqtSlot()
    def open_file(self):
        """
        Open file
        """
        file = QFileDialog.getOpenFileName(self, "Add include file", filter="xml file(*.xml)")
        if len(file) > 0 and len(file[0]) > 0:
            self.file_line_edit.setText(file[0])


def get_include_file(q):
    """
    Get include file
    :param q: The queue
    """
    try:
        app = QApplication(sys.argv)
        widget = IncludeFile(q=q)
        widget.show()
        sys.exit(app.exec())
    except Exception as e:
        print(e)


if __name__ == "__main__":
    q = Queue()
    get_include_file(q)

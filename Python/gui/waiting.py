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


class Waiting(QDialog):
    """
    Waiting
    """

    def __init__(self, parent=None, q=None):
        """
        Initialized
        :param parent: The parent widget
        :param q: The queue
        """
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
        """
        Send waiting event
        """
        msg = "waiting "
        if self.q is not None:
            if len(self.wait_line_edit.text()) > 0:
                msg += self.wait_line_edit.text()
            self.q.put(msg)

    @pyqtSlot()
    def accept(self):
        """
        Accept
        """
        self._exit()
        super(Waiting, self).accept()

    @pyqtSlot()
    def reject(self):
        """
        Reject
        """
        self._exit()
        super(Waiting, self).reject()


def get_waiting(q):
    """
    Get waiting
    :param q: The queue
    """
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

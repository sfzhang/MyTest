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
import subprocess


class RunScript(QDialog):
    """
    Run script
    """

    def __init__(self, parent=None, q=None):
        """
        Initialize
        :param parent: The parent widget
        :param q: The queue for multiprocessing
        """
        super(RunScript, self).__init__(parent=parent)
        self.setWindowTitle("Add script")

        self.q = q

        path = os.path.dirname(os.path.realpath(__file__))
        self.script_label = QLabel("Script: ")
        self.script_line_edit = QLineEdit()
        self.run_ckb = QCheckBox("Run")
        self.run_ckb.setChecked(True)
        self.type_cbb = QComboBox()
        self.type_cbb.addItem("sync")
        self.type_cbb.addItem("async")
        self.open_btn = QPushButton(QIcon(path + "/open.png"), "")

        self.ok_btn = QPushButton(QIcon(path + "/ok.png"), "")
        self.cancel_btn = QPushButton(QIcon(path + "/exit.png"), "")
        self.ok_btn.setDefault(True)

        self.hbox_layout = QHBoxLayout()
        self.hbox_layout.addWidget(self.script_label)
        self.hbox_layout.addWidget(self.script_line_edit, 2)
        self.hbox_layout.addWidget(self.run_ckb)
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
        """
        Send run script event and exit
        """
        msg = "run_script "
        if self.q is not None:
            if len(self.script_line_edit.text()) > 0:
                msg += self.type_cbb.currentText() + " " + self.script_line_edit.text().replace(' ', '\x00')
            self.q.put(msg)

    @pyqtSlot()
    def accept(self):
        """
        Accept
        """
        if self.run_ckb.isChecked():
            if self.type_cbb.currentText() == "sync":
                subprocess.call(self.script_line_edit.text().split())
            else:
                subprocess.Popen(self.script_line_edit.text().split())

        self._exit()
        super(RunScript, self).accept()

    @pyqtSlot()
    def reject(self):
        """
        Reject
        """
        self._exit()
        super(RunScript, self).reject()

    @pyqtSlot()
    def open_file(self):
        """
        Open script file
        """
        file = QFileDialog.getOpenFileName(self, "Run script",
                                           filter="Python script(*.py);;Shell script(*.sh);;All files(*.*)")
        if len(file) > 0 and len(file[0]) > 0:
            self.script_line_edit.setText(file[0])


def get_run_script(q):
    """
    Get run script
    :param q: The queue
    """
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

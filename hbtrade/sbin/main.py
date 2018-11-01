#!/usr/bin/python3
# -*- coding: utf-8 -*-

"""
Main for huobi trading.

Copyright (C) 2018 by Zhang Shengfa(shengfazhang@126.com)
"""

import service
import tschart
import sys
from log import *
from PyQt5.QtCore import *
from PyQt5.QtWidgets import *


class MainWidget(QWidget):
    """
    MainWidget.
    """

    def __init__(self):
        """
        Initialize.
        """
        QWidget.__init__(self)
        self.tschart = tschart.TimeSharingChart(parent=self)
        self.layout = QHBoxLayout()
        self.layout.addWidget(self.tschart)
        self.setLayout(self.layout)

        self.market_service = service.WSMarketService()
        self.market_service.opened.connect(self._get_ts_data)
        self.market_service.message_received.connect(self._handle_ws_message)

        self.market_service.start("api.huobi.br.com", "/ws", "eda0541b-6701190d-05fb558b-ae4df",
                                  "6d3a366d-57b181cb-2fd48679-df0fe")
        self.ch = ""
        self.ticks = {} # { id: close }
        self.req_kline = False
        self.update_data = False
        self.rep = ""

    @pyqtSlot()
    def _get_ts_data(self):
        """
        Get time-sharing data.
        """
        self.tschart.clear()
        self.market_service.kline("sub", "btcusdt", "1min")

    @pyqtSlot("PyQt_PyObject")
    def _handle_ws_message(self, msg):
        """
        Handle WebSocket message
        :param msg: The WebSocket message
        """
        if "subbed" in msg:
            debug_log("subbed!")
            self.ch = msg["subbed"]
        elif "ch" in msg and self.ch == msg["ch"]:
            if not self.req_kline:
                self.ticks[msg["tick"]["id"]] = msg["tick"]["close"]
                self.market_service.req_kline("btcusdt", "1min", None, msg["tick"]["id"] * 1000)
                self.req_kline = True
                self.rep = "market.btcusdt.kline.1min"
            else:
                if self.update_data:
                    self.tschart.update_data(msg["tick"]["id"], msg["tick"]["close"])
                else:
                    self.ticks[msg["tick"]["id"]] = msg["tick"]["close"]
        elif "rep" in msg and self.rep == msg["rep"]:
            for data in msg["data"]:
                self.tschart.append_data(data["id"], data["close"])

            for (x, y) in self.ticks.items():
                self.tschart.update_data(x, y)

            self.update_data = True


if __name__ == "__main__":
    init_log("DEBUG", "../log/main.log")
    app = QApplication(sys.argv)
    main = MainWidget()
    main.show()
    sys.exit(app.exec())

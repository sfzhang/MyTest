# -*- coding: utf-8 -*-

"""
Service for huobi trading.

Copyright (C) 2018 by Zhang Shengfa(shengfazhang@126.com)
"""

import wsbase
import math
import time
import sys
import gzip
import json
from log import *
from PyQt5.QtCore import *


class WebSocketService(QObject):
    """
    WebSocket trade service.
    """

    opened = pyqtSignal()
    closed = pyqtSignal()
    message_received = pyqtSignal("PyQt_PyObject")
    error_occurred = pyqtSignal(str)

    def __init__(self, name, parent=None):
        """
        Initializing.
        :param parent: The QObject parent.
        """
        QObject.__init__(self, parent)
        self.id = 0
        self.host = ""
        self.path = ""
        self.access_key = ""
        self.secret_key = ""

        self.active = False
        self.reconnect = True
        self.try_time = 5
        self.current_try_time = self.try_time
        self.name = name

        self.ws = None

    def _id(self):
        """
        Get current ID and increased.
        :return: Current ID with string.
        """
        return str(self.id + 1)

    def _create_ws(self):
        """
        Create WebSocket client.
        :return: WebSocket client.
        """
        ws = wsbase.WebSocketBase(self.host, self.path, self.access_key, self.secret_key)

        ws.opened.connect(self.on_open, Qt.QueuedConnection)
        ws.closed.connect(self.on_close, Qt.QueuedConnection)
        ws.message_received.connect(self.on_message, Qt.QueuedConnection)
        ws.error_occurred.connect(self.on_error, Qt.QueuedConnection)

        ws.start(self.name)
        return ws

    def _pong(self, ts):
        """
        Send pong message to server.
        :param ts: The time stampe.
        """
        msg = {
            "pong": ts
        }
        if self.ws.send(msg):
            debug_log("Send pong message[%s] success!", ts)
        else:
            error_log("Send pong message[%s] failed!", ts)

    def start(self, host, path, access_key, secret_key, reconnect=True, try_time=5):
        """
        Start a WebSocket client.
        :param host: The host URL.
        :param path: The request path.
        :param access_key: The access key.
        :param secret_key: The secret key.
        :param reconnect: Reconnect if closed.
        :param try_time: The try to connect time.
        """
        self.host = host
        self.path = path
        self.access_key = access_key
        self.secret_key = secret_key
        self.reconnect = reconnect
        self.try_time = try_time
        self.current_try_time = self.try_time

        self.ws = self._create_ws()

    def stop(self):
        """
        Stop WebSocket service.
        """
        if self.ws:
            self.ws.stop()
            self.ws = None
            self.reconnect = False

    @pyqtSlot()
    def on_open(self):
        """
        Handle WebSocket opened event.
        """
        self.active = True
        self.opened.emit()
        self.current_try_time = self.try_time

    @pyqtSlot()
    def on_close(self):
        """
        Handle WebSocket closed event.
        """
        self.active = False

        self.ws.stop()
        self.ws = None

        if self.reconnect and self.current_try_time > 0:
            self.current_try_time -= 1
            warn_log("Disconnect from WebSocket with host[%s], try to connect with time[%d]",
                     self.host, self.try_time - self.current_try_time)
            self.ws = self._create_ws()
        else:
            error_log("Failed to connect to WebSocket with host[%s]", self.host)
            self.closed.emit()

    @pyqtSlot(bytes)
    def on_message(self, msg):
        """
        Handle received message.
        :param msg: The received message.
        """
        json_data = gzip.decompress(msg).decode()
        dict_msg = json.loads(json_data)
        debug_log("Receive message:\n%s", dict_msg)

        try:
            if "ping" in dict_msg:
                self._pong(dict_msg["ping"])
            else:
                self.message_received.emit(dict_msg)
        except BaseException as e:
            error_log("Receive invalid message:\n%s", dict_msg)

    @pyqtSlot(str)
    def on_error(self, error):
        """
        Handle error message.
        :param error: The error message.
        """
        error_log("Receive error message[%s]", error)
        self.error_occurred.emit(error)


class WSMarketService(WebSocketService):
    """
    Market service with WebSocket.
    """

    def __init__(self, parent=None):
        """
        Initializing.
        :param parent: QObject parent.
        """
        WebSocketService.__init__(self, "ws_market", parent)

    def overview(self, op):
        """
        Subcribe or unsubcribe overview.
        :param op: sub or unsub.
        """
        if self.active:
            msg = {
                op: "market.overview",
                "id": self._id()
            }
            self.ws.send(msg)
            debug_log("%s market.overview", op)

    @pyqtSlot()
    def on_open(self):
        """
        Handle WebSocket opened event.
        """
        WebSocketService.on_open(self)

        #self.kline("sub", "btcusdt", "1min")
        #self.req_kline("ethbtc", "1min", None, math.ceil(time.time() / 60) * 60 * 1000)
        #self.trade_detail("sub", "ethbtc")

    def kline(self, op, symbol, period):
        """
        Subscribe or unsubcribe K-line.
        :param op: sub or unsub.
        :param symbol: Trade pair, such as(ethbtc, ltcbtc, etcbtc, bchbtc...).
        :param period: The K-line period with (1min, 5min, 15min, 30min, 60min, 1day, 1mon, 1weak, 1year).
        """
        if self.active:
            msg = {
                op: "market." + symbol + ".kline." + period,
                "id": self._id()
            }
            self.ws.send(msg)
            debug_log("%s K-line with symbol[%s], period[%s]", op, symbol, period)

    def req_kline(self, symbol, period, from_ts, to_ts):
        """
        Request K-line.
        :param symbol: Trade pair, such as(ethbtc, ltcbtc, etcbtc, bchbtc...).
        :param period: The K-line period with (1min, 5min, 15min, 30min, 60min, 1day, 1mon, 1weak, 1year).
        :param from_ts: time in ms, optional if to_ts provided
        :param to_ts: time in ms, optional if from_ts provided
        """
        if self.active:
            if from_ts is None and to_ts is None:
                error_log("Invalid argument as from_ts and to_ts are all None")
                return

            msg = {
                "req": "market." + symbol + ".kline." + period,
                "id": self._id()
            }

            if from_ts is not None:
                msg["from_ts"] = from_ts

            if to_ts is not None:
                msg["to_ts"] = to_ts

            self.ws.send(msg)
            debug_log("Request K-line with symbol[%s], period[%s]", symbol, period)

    def depth(self, op, symbol, depth=0):
        """
        Subscribe or unsubcribe depth.
        :param op: sub or unsub.
        :param symbol: Trade pair, such as(ethbtc, ltcbtc, etcbtc, bchbtc...).
        :param depth: 0-5
        """
        if self.active:
            msg = {
                op: "market." + symbol + ".depth.step" + depth,
                "id": self._id()
            }
            self.ws.send(msg)
            debug_log("%s depth with symbol[%s], depth[%s]", op, symbol, depth)

    def trade_detail(self, op, symbol):
        """
        Subscribe or unsubcribe trade detail.
        :param op: sub or unsub.
        :param symbol: Trade pair, such as(ethbtc, ltcbtc, etcbtc, bchbtc...).
        """
        if self.active:
            msg = {
                op: "market." + symbol + ".trade.detail",
                "id": self._id()
            }
            self.ws.send(msg)
            debug_log("%s trade detail with symbol[%s]", op, symbol)


if __name__ == "__main__":
    init_log("DEBUG", "../log/main.log")
    app = QCoreApplication(sys.argv)
    service = WSMarketService()
    service.start("api.huobi.br.com", "/ws", "eda0541b-6701190d-05fb558b-ae4df", "6d3a366d-57b181cb-2fd48679-df0fe")
    sys.exit(app.exec())


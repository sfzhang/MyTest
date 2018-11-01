# -*- coding: utf-8 -*-

"""
WebSocket base for huobi trading.

Copyright (C) 2018 by Zhang Shengfa(shengfazhang@126.com)
"""

import websocket
import threading
import json
from log import *
from PyQt5.QtCore import *


class WebSocketBase(QObject):
    """
    WebSocket base class. Notify the event by Qt signal.
    """

    opened = pyqtSignal()
    closed = pyqtSignal()
    message_received = pyqtSignal(bytes)
    error_occurred = pyqtSignal(str)

    def __init__(self, host, path, access_key, secret_key, parent = None):
        """
        Initializing.
        :param host: The host URL.
        :param path: The request path.
        :param access_key: The access key.
        :param secret_key: The secret key.
        """
        QObject.__init__(self, parent)
        self.ws = None
        self.url = "wss://" + host + path
        self.access_key = access_key
        self.secret_key = secret_key

        self.event = threading.Event()
        self.thread = None

    def stop(self):
        """
        Stop webservice
        """
        if self.thread is not None and self.thread.is_alive():
            warn_log("Wait for WebSocket thread exit!")
            self.event.set()
            self.thread.join()
            self.thread = None

    def send(self, msg):
        """
        Send json message to WebSocket server
        :return True if succeed, otherwise False
        """
        try:
            json_msg = json.dumps(msg).encode()
            self.ws.send(json_msg)
            return True
        except BaseException as e:
            error_log("Send message[%s] failed: error[%s]", msg, e)
            return False

    def on_open(self):
        """
        Connect successfully.
        """
        info_log("Connect to host[%s] success", self.url)
        self.opened.emit()

    def on_close(self):
        """
        WebSocket closed.
        """
        fatal_log("Disconnected from host[%s]", self.url)
        self.closed.emit()

    def on_message(self, msg):
        """
        Message received.
        :param msg: The received message.
        """
        self.message_received.emit(msg)

        if self.event.is_set():
            warn_log("Received thread exit notification, close WebSocket and exit now!")
            self.ws.close()

    def on_error(self, error):
        """
        Error occurred.
        :param error: The error message.
        """
        error_log("Error[%s] occurred", error)
        self.error_occurred(error)

    def run(self, log_level, log_file):
        """
        Run the task
        :param log_level: The log level
        :param log_file: The log file
        """
        init_log(log_level, log_file, threading.current_thread().name)
        self.ws = websocket.WebSocketApp(
            self.url,
            on_open=self.on_open,
            on_close=self.on_close,
            on_message=self.on_message,
            on_error=self.on_error
        )
        self.ws.run_forever()
        error_log("Thread exit!")

    def start(self, name, log_path="./", log_level="DEBUG"):
        """
        Start to run.
        :param name: The thread name
        :param log_path: The log path
        :param log_level: The log level string in [DEBUG, INFO, WARN, ERROR, FATAL]
        """
        log_file = log_path + name + ".log"
        self.thread = threading.Thread(target=self.run, name=name, args=(log_level, log_file))
        self.thread.start()


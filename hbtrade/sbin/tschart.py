# -*- coding: utf-8 -*-

"""
Time-sharing chart for huobi trading.

Copyright (C) 2018 by Zhang Shengfa(shengfazhang@126.com)
"""

from PyQt5.QtWidgets import *
from PyQt5.QtChart import *
from PyQt5.QtCore import *
from PyQt5.QtGui import *


class TimeSharingChart(QWidget):
    """
    Implement Time-Sharing chart of the past 5 hours.
    """

    def __init__(self, max_count=300, parent=None):
        """
        Initialize.
        :param parent: The parent widget
        """
        QWidget.__init__(self, parent)

        self.max_count = max_count
        self.series = QLineSeries(self)
        pen = QPen(Qt.green)
        pen.setWidth(3)
        self.series.setPen(pen)
        self.xaxis = QDateTimeAxis()
        self.xaxis.setFormat("MM-dd HH:mm")
        self.chartview = QChartView()
        self.chart = QChart()

        self.chart.addSeries(self.series)
        self.chart.setAnimationOptions(QChart.SeriesAnimations)
        self.chart.createDefaultAxes()
        self.chart.setTitle("Time-Sharing Chart(BTC/USDT)")
        self.chart.setAxisX(self.xaxis, self.series)
        self.chart.legend().hide()

        self.chartview.setChart(self.chart)
        self.layout = QHBoxLayout()
        self.layout.addWidget(self.chartview)
        self.setLayout(self.layout)

    def _shrink(self):
        """
        Shrink the data to max_count
        """
        while self.series.count() > self.max_count:
            self.series.remove(0)

    def _update_range(self):
        """
        Update axis range
        """
        min_y = self.series.at(0).y()
        max_y = min_y
        i = 1
        while i < self.series.count():
            y = self.series.at(i).y()
            if min_y > y:
                min_y = y
            if max_y < y:
                max_y = y
            i += 1

        self.chartview.chart().axisX().setRange(QDateTime.fromMSecsSinceEpoch(self.series.at(0).x()),
                                                QDateTime.fromMSecsSinceEpoch(self.series.at(i - 1).x() + 600000))
        self.chartview.chart().axisY().setRange(min_y, max_y)

    def clear(self):
        """
        Clear chart.
        """
        self.series.clear()

    def append_data(self, x, y):
        """
        Append new data with (x, y)
        :param x: Epoch time with second
        :param y: price
        """
        x *= 1000
        self.series.append(x, y)
        self._shrink()
        self._update_range()

    def update_data(self, x, y):
        """
        Update the latest data or append
        :param x:
        :param y:
        :return:
        """
        x *= 1000
        count = self.series.count()
        if count > 0 and self.series.at(count - 1).x() == x:
            self.series.replace(count - 1, x, y)
            self._update_range()
        elif count == 0 or self.series.at(count - 1).x() < x:
            self.append_data(x / 1000, y)

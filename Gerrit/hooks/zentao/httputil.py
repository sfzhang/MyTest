#!/usr/bin/python3
# -*- coding: utf-8 -*-

"""
HTTP utilities
"""

import requests
from log import *


__all__ = [
    "http_get",
    "http_post",
]


def http_get(url, params=None, timeout=10):
    """
    http GET method.
    :param url: The url.
    :param params: The parameters.
    :param timeout: The timeout in second to get.
    :return: (True, Response object) if succeed, otherwise (False, None)
    """
    headers = {
        "Accept": "application/json",
        "Content-type": "application/x-www-form-urlencoded",
        "User-Agent": "Mozilla/5.0 (Windows NT 6.1; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) "
                      "Chrome/39.0.2171.71 Safari/537.36"
    }

    try:
        response = requests.get(url, params=params, headers=headers, timeout=timeout)
        if response.status_code == 200:
            info_log("requests.get() success: url[%s]", url)
            return True, response
        else:
            error_log("requests.get() failed: url[%s], error[%s]", url, response.text)
            return False, None
    except BaseException as e:
        error_log("requests.get() failed: url[%s], exception[%s]", url, e)
        return False, None


def http_post(url, data=None, timeout=10):
    """
    http POST method.
    :param url: The url.
    :param data: The data.
    :param timeout: The timeout in second to get.
    :return: (True, Response object) if succeed, otherwise (False, None)
    """
    headers = {
        "Accept": "application/json",
        "Content-type": "application/x-www-form-urlencoded",
        "Accept-Language": "zh-cn"
    }

    try:
        response = requests.post(url, data=data, headers=headers, timeout=timeout)
        if response.status_code == 200:
            info_log("requests.post() success: url[%s]", url)
            return True, response
        else:
            error_log("requests.post() failed: url[%s], error[%s]", url, response.text)
            return False, None
    except BaseException as e:
        error_log("requests.post() failed: url[%s], exception[%s]", url, e)
        return False, None


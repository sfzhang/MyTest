# -*- coding: utf-8 -*-

"""
Utility for huobi trade from https://github.com/huobiapi/REST-Python3-demo.
"""

import datetime
import urllib
import hmac
import hashlib
import base64
import requests
import json
from log import *

__all__ = [
    "http_get",
    "http_post",
    "api_key_get",
    "api_key_post"
]


def _get_utc_timestamp():
    """
    Get current time at UTC zone with format YYYY-mm-ddTHH:MM:SS.
    :return: Current time at UTC zone.
    """
    return datetime.datetime.utcnow().strftime('%Y-%m-%dT%H:%M%S')


def _create_signature(method, url, path, secret_key, params):
    """
    Create signature.
    :param method: GET or POST method.
    :param url: Host URL.
    :param path: The request path.
    :param secret_key: The secret key.
    :param params: The parameters.
    :return: The signature.
    """
    sorted_params = sorted(params.items(), key=lambda x: x[0])
    encoded_params = urllib.parse.urlencode(sorted_params)
    payload = "\n".join([method, url, path, encoded_params])
    encoded_payload = payload.encode(encoding="UTF8")
    encoded_secret_key = secret_key.encode(encoding="UTF8")

    digest = hmac.new(encoded_secret_key, encoded_payload, digestmod=hashlib.sha256).digest()
    signature = base64.b64encode(digest).decode()
    return signature


def http_get(url, params, ext_headers=None, timeout=5):
    """
    http GET method.
    :param url: The host url.
    :param params: The params.
    :param ext_headers: The external headers.
    :param timeout: The timeout in second to get.
    :return: True if succeed, otherwise False
    """
    headers = {
        "Content-type": "application/x-www-form-urlencoded",
        "User-Agent": "Mozilla/5.0 (Windows NT 6.1; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) "
                      "Chrome/39.0.2171.71 Safari/537.36"
    }

    if ext_headers:
        headers.update(ext_headers)

    encoded_params = urllib.parse.urlencode(params)

    try:
        response = requests.get(url, encoded_params, headers=headers, timeout=timeout)
        if response.status_code == 200:
            info_log("requests.get() success: url[%s]", url)
            return requests.json()
        else:
            error_log("requests.get() failed: url[%s], error[%s]", url, response.text)
            return False
    except BaseException as e:
        error_log("requests.get() failed: url[%s], exception[%s]", url, e)
        return False


def http_post(url, params, ext_headers=None, timeout=10):
    """
    http POST method.
    :param url: The host url.
    :param params: The params.
    :param ext_headers: The external headers.
    :param timeout: The timeout in second to get.
    :return: True if succeed, otherwise False.
    """
    headers = {
        "Accept": "application/json",
        "Content-Type": "application/json",
        "Accept-Language": "zh-cn"
    }

    if ext_headers:
        headers.update(ext_headers)

    post_data = json.dump(params)
    try:
        response = requests.post(url, post_data, headers=headers, timeout=timeout)
        if response.status_code == 200:
            info_log("requests.post() success: url[%s]", url)
            print(response.text)
            return response.text
        else:
            error_log("requests.post() failed: url[%s], error[%s]", url, response.text)


def api_key_get(url, path, params, access_key, secret_key):
    """
    REST API GET method with access_key and secret_key.
    :param url: The host URL.
    :param path: The request path.
    :param params: The parameters.
    :param access_key: The access key.
    :param secret_key: The secret key.
    :return: True if succeed, otherwise False
    """
    params.update({
        "AccessKeyID": access_key,
        "SignatureMethod": "HmacSHA256",
        "SignatureVersion": "2",
        "Timestamp": _get_utc_timestamp()
    })

    host_url = urllib.parse.urlparse(url).hostname.lower()
    params["Signature"] = _create_signature("GET", host_url, path, secret_key, params)
    new_url = host_url + path

    return http_get(new_url, params)


def api_key_post(url, path, params, access_key, secret_key):
    """
    REST API POST method with access_key and secret_key.
    :param url: The host URL.
    :param path: The request path.
    :param params: The parameters.
    :param access_key: The access key.
    :param secret_key: The secret key.
    :return: True if succeed, otherwise False
    """
    params_to_sign = {
        "AccessKeyId": access_key,
        "SignatureMethod": "HmacSHA256",
        "SignatureVersion": "2",
        "Timestamp": _get_utc_timestamp()
    }

    host_url = urllib.parse.urlparse(url).hostname.lower()
    params_to_sign["Signature"] = _create_signature("POST", host_url, path, secret_key, params_to_sign)
    new_url = host_url + path + "?" + urllib.parse.urlencode(params_to_sign)

    return http_post(new_url, params)


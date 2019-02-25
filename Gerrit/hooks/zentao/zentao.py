#!/usr/bin/python3
# -*- coding: utf-8 -*-

"""
Zentao service
"""

import urllib
import requests
import json
from log import *
from httputil import *


class ZentaoFailed(Exception):
    """
    Zento http operation failed.
    """

    def __init__(self, err_msg=None):
        """
        Initialization.
        :param err_msg: The error message.
        """
        super().__init__(self)
        self.err_msg = err_msg

    def __str__(self):
        """
        Get string.
        :return: The exception message.
        """
        return self.err_msg


class ZentaoService:
    """
    Zentao service
    """

    def __init__(self, host='http://192.168.1.2:8090', user="cmshende", password="cmshende"):
        """
        Initialization
        :param host: The zentao host
        """
        self.host = host
        self.user = user
        self.password = password

        # Get session ID
        result = self.http_get("/zentao/api-getsessionid.json")
        data = json.loads(result["data"])
        self.session_id = data["sessionID"]

        # Login
        data = {
            "account": user,
            "password": password
        }

        self.http_post_with_sid("/zentao/user-login.json", data)

    def check_task(self, id):
        """
        Check if the given task is exist.
        :param id: The task ID.
        :return True if exist, otherwise False
        """
        try:
            result = self.http_get_with_sid("/zentao/task-view-" + id + ".json")
            if json.loads(result["data"])["task"]["id"] == id:
                return True
            else:
                return False
        except:
            return False

    def check_bug(self, id):
        """
        Check if the given bug is exist.
        :param id: The bug ID.
        :return True if exist, otherwise False.
        """
        try:
            result = self.http_get_with_sid("/zentao/bug-view-" + id + ".json")
            if json.loads(result["data"])["bug"]["id"] == id:
                return True
            else:
                return False
        except:
            return False

    def update_task(self, id, msg):
        """
        Update task with the new message at the given ID.
        :param id: The task ID.
        :param msg: The new message.
        :return: True if succeed, otherwise False.
        """
        try:
            result = self.http_get_with_sid("/zentao/task-edit-" + id + ".json")
            task = json.loads(result["data"])["task"]

            new_data = {
                "desc": msg + task["desc"],
                "consumed": task["consumed"],
                "deadline": task["deadline"]
            }
            result = self.http_post_with_sid("/zentao/task-edit-" + id + ".json", new_data)
            if type(result) is not str or result.find("parent.location='/zentao/task-view-" + id + ".json") == -1:
                return False
            else:
                return True
        except:
            return False

    def update_bug(self, id, msg):
        """
        Update bug with the new message at the given ID.
        :param id: The bug ID.
        :param msg: The new message.
        :return: True if succeed, otherwise False.
        """
        try:
            result = self.http_get_with_sid("/zentao/bug-edit-" + id + ".json")
            bug = json.loads(result["data"])["bug"]

            new_data = {
                "steps": msg + bug["steps"],
                "module": bug["module"],
                "openedBuild": bug["openedBuild"]
            }
            result = self.http_post_with_sid("/zentao/bug-edit-" + id + ".json", new_data)
            if type(result) is not str or result.find("parent.location='/zentao/bug-view-" + id + ".json") == -1:
                return False
            else:
                return True
        except:
            return False

    def http_get_with_sid(self, url, params=None, timeout=10):
        """
        Http get with session UID
        :param url: The url
        :param params: The parameters
        :param timeout: The timeout
        :return: response data
        """
        if params is None:
            params = {}
        params["zentaosid"] = self.session_id

        return self.http_get(url, params, timeout)

    def http_get(self, url, params=None, timeout=10):
        """
        Wrap http_get
        :param url: The url
        :param params: The parameters
        :param timeout: The timeout
        :return: response data
        """
        success, response = http_get(self.host + url, params, timeout)
        if not success:
            raise ZentaoFailed("http_get() failed!")

        try:
            result = response.json()
            if result["status"] != "success":
                raise ZentaoFailed("http_get() success, but response failed: " + response.text)
            return result
        except:
            warn_log("http_get() success, but response is not json: %s", response.text)
            return response.text

    def http_post_with_sid(self, url, data=None, timeout=10):
        """
        Http post with session UID
        :param url: The url
        :param data: The data
        :param timeout: The timeout
        :return: response data
        """
        return self.http_post(url + "?zentaosid=" + self.session_id, data, timeout)

    def http_post(self, url, data=None, timeout=10):
        """
        Wrap http_post
        :param url: The url
        :param data: The data
        :param timeout: The timeout
        :return: response data
        """
        success, response = http_post(self.host + url, data, timeout)
        if not success:
            raise ZentaoFailed("http_post() failed!")

        try:
            result = response.json()
            if result["status"] != "success":
                raise ZentaoFailed("http_post() success, but response failed: " + response.text)
            return result
        except:
            warn_log("http_post() success, but response is not json: %s", response.text)
            return response.text


if __name__ == "__main__":
    init_log("DEBUG", "zentao.log")

    zts = ZentaoService()

    print(zts.check_bug("1"))
    print(zts.check_bug("1111111"))

    print(zts.check_task("20"))
    print(zts.check_task("300000"))

    print(zts.update_bug("17", "hello<br>"))
    print(zts.update_bug("1700", "hello<br>"))

    change_url = "http://192.168.1.2/100"
    msg = 'Gerrit Code Review: <a href="' + change_url + '" target="_blank">' + change_url.split('/')[-1] + '</a><br>'

    print(zts.update_task("950", msg))
    print(zts.update_task("9500", msg))

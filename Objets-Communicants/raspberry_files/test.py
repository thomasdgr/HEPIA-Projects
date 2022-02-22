#!/usr/bin/env python3
"""Unit test"""

import nose
import data
import presence
import scan
from time import sleep
import datetime

__author__ = ["Quentin Rod", "Thomas Dagier", "Xavier Perret"]
__email__ = [
    "quentin.rod@etu.hesge.ch",
    "thomas.dagier@etu.hesge.ch",
    "xavier.perret@etu.hesge.ch",
]
__date__ = "23/11/2021"


def test_gen_presence():
    print("Testing gen_presence()")
    now = presence.gen_presence()
    presence.print_presence(now)
    sleep(1)
    later = presence.gen_presence()
    presence.print_presence(later)
    assert now.start_date == now.end_date
    assert now.start_date != later.start_date

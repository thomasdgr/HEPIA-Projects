#!/usr/bin/env python3
"""Contains datastructures

"""

from dataclasses import dataclass
from typing import List, Set, Dict, Tuple, Optional
from datetime import datetime


__author__ = ["Quentin Rod", "Thomas Dagier", "Xavier Perret"]
__email__ = [
    "quentin.rod@etu.hesge.ch",
    "thomas.dagier@etu.hesge.ch",
    "xavier.perret@etu.hesge.ch",
]
__date__ = "23/11/2021"


@dataclass
class Presence:
    """Represent a person"""

    start_date: str
    end_date: str

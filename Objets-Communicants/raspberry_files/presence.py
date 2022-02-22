#!/usr/bin/env python3
"""In charge of maintaining the list of present people at 'x' stand
"""

from datetime import datetime
from typing import List, Set, Dict, Tuple, Optional
import data
from RFID import Tag

__author__ = ["Quentin Rod", "Thomas Dagier", "Xavier Perret"]
__email__ = [
    "quentin.rod@etu.hesge.ch",
    "thomas.dagier@etu.hesge.ch",
    "xavier.perret@etu.hesge.ch",
]
__date__ = "07/12/2021"


def gen_presence() -> data.Presence:
    """Generate and return new presence which contains the present time"""
    now: str = str(datetime.now().timestamp())
    return data.Presence(now, now)


def print_presence(p: data.Presence) -> None:
    """"""
    print(
        "Present from "
        + datetime.fromtimestamp(float(p.start_date)).strftime("%m")
        + " to "
        + datetime.fromtimestamp(float(p.end_date)).strftime("%m")
    )


def add_new_user(user: str, user_dict: Dict[str, data.Presence]):
    """"""
    user_dict[user] = gen_presence()


def transfer_user(
    user: str,
    user_dict: Dict[str, data.Presence],
    new_user_dict: Dict[str, data.Presence],
):
    """"""
    new_user_dict[user] = user_dict[user]
    new_user_dict[user].end_date = str(datetime.now().timestamp())
    del user_dict[user]


class UsersPresence:
    """"""

    def __init__(self):
        """"""
        self.present_dict_person: Dict[str, data.Presence] = {}
        self.past_dict_person: Dict[str, data.Presence] = {}

    def get_present_persons(self) -> Dict[str, data.Presence]:
        """"""
        return self.present_dict_person

    def get_past__persons(self) -> Dict[str, data.Presence]:
        """"""
        return self.past_dict_person

    def transfer_past_persons(self) -> Dict[str, data.Presence]:
        """Return dict and empty"""
        res = self.past_dict_person
        self.past_dict_person = {}
        return res

    def update_presence(self, current_users: List[Tag], rssi_min_for_presence : float) -> Dict[str, data.Presence]:
        """Return the new user and update user that are there and user that went away"""
        current_users_RFIDTags = [
            x.id_tag for x in current_users #if x.RSSI >= rssi_min_for_presence
        ]  # get all the tags uuid

        # START - Remove user that went away from the reader
        gone_users: List[str] = []
        is_user_present: bool = False
        for present_user in self.present_dict_person.keys():
            for current_user in current_users:
                if present_user == current_user.id_tag and current_user.RSSI > rssi_min_for_presence:
                    is_user_present = True
                    break
            if not is_user_present:
                gone_users.append(present_user)
            else:
                is_user_present = False

        for gone_user in gone_users:
            transfer_user(gone_user, self.present_dict_person, self.past_dict_person)
        # END - Remove user that went away from the reader

        # START - Add new user and make list of new additions
        new_user: Dict[str, data.Presence] = {}
        for current_user in current_users:
            if current_user.id_tag not in self.present_dict_person and current_user.RSSI > rssi_min_for_presence:
                add_new_user(current_user.id_tag, self.present_dict_person)
                new_user[current_user.id_tag] = self.present_dict_person[current_user.id_tag]
        # END - Add new user and make list of new additions
        return new_user

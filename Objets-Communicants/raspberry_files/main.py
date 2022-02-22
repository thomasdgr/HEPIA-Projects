#!/usr/bin/env python3

""""""

import data
import scan
import yaml
import time
import serial
import RFID
from presence import UsersPresence
from data import Presence
import sys
from typing import List, Set, Dict, Tuple, Optional
import json
from json import JSONEncoder
import requests
import os


__author__ = ["Quentin Rod", "Thomas Dagier", "Xavier Perret"]
__email__ = [
    "quentin.rod@etu.hesge.ch",
    "thomas.dagier@etu.hesge.ch",
    "xavier.perret@etu.hesge.ch",
]
__date__ = "07/12/2021"


class Data_Encoder(JSONEncoder):
    def default(self, obj):
        if isinstance(obj, Presence):
            return obj.__dict__
        return JSONEncoder.default(self, obj)


if __name__ == "__main__":
    if len(sys.argv) != 2:
        print("Please use ./" + sys.argv[0] + " PATH_YAML_CONFIG_FILE")
        sys.exit(1)

    stand_id : int = 0
    yaml_config : str = sys.argv[1]

    f = open(yaml_config)
    config : Dict = yaml.load(f, Loader=yaml.FullLoader)
    stand_id :int = config['stand_id']
    use_reader : bool = config["use_reader"]
    api_address_post: str = config["api_address_post"]
    refresh_read_rate_s: int = config["refresh_read_rate_s"]
    rssi_min_for_presence : int = config["rssi_min_for_presence"]

    if use_reader: #Otherwise, generates random read tags
        scan.RFID_reader_init(config["timeout_read_one_mess_ms"], config["timeout_wait_cmd_answ_ms"], config["serial_port"], True, False, False)

    config_to_send: Dict[str, int] = {"stand_id": stand_id}
    up: UsersPresence = UsersPresence()
    data_for_backend: Dict[str, Dict] = {}
    data_for_backend["config"] = config_to_send
    while True:
        tags_read = scan.RFID_read_tags() if use_reader else RFID.RFID_generate_random_read_tags()
        new_people = up.update_presence(tags_read, rssi_min_for_presence)
        present_people = up.get_present_persons()
        past_people = up.transfer_past_persons()
        os.system('cls' if os.name == 'nt' else 'clear')
        if use_reader:
            print("\n---READER TAGS DETECTION MODE---\n")
        else:
            print("\n----GENERATION TAGS DETECTION MODE---\n")

        print("\npresent_people:")
        for user in present_people.keys():
            print(
                user,
                ": START_DATE='",
                present_people[user].start_date,
                " END_DATE='",
                present_people[user].end_date,
            )
        print("\nnew_people:")
        for user in new_people.keys():
            print(
                user,
                ": START_DATE='",
                new_people[user].start_date,
                " END_DATE='",
                new_people[user].end_date,
            )
        print("\npast_people:")
        for user in past_people.keys():
            print(
                user,
                ": START_DATE='",
                past_people[user].start_date,
                " END_DATE='",
                past_people[user].end_date,
            )
        data_for_backend["new_people"] = new_people
        data_for_backend["past_people"] = past_people
        ready_to_send = json.dumps(data_for_backend, indent=3, cls=Data_Encoder)

        x = requests.post(api_address_post, data = ready_to_send)

        time.sleep(refresh_read_rate_s)

from typing import List, Set, Dict, Tuple, Optional
import random

random.seed()


class Tag:
    """"""

    def __init__(self, id_tag : str, RSSI : int):
        self.id_tag = id_tag
        self.RSSI = int(RSSI)

    def __str__(self):
        """"""
        return "ID: " + self.id_tag + ", RSSI: " + str(self.RSSI)

    @staticmethod
    def print_list(list_tags):
        """"""
        print("---------------------------")
        for tag in list_tags:
            print(tag)
        print("---------------------------")


def RFID_generate_random_read_tags() -> List[Tag]:
    """Demo function to return hardcoded tags real one is in scan.py"""
    rand = random.randrange(0, 4)
    demo_current_users = []

    #print("---\nGENERATION TAGS DETECTION MODE\n---")
    if rand == 0:
        demo_current_users.append(Tag("000000000000000000000075", "10"))
        demo_current_users.append(Tag("000000000000000000000076", "10"))
        demo_current_users.append(Tag("000000000000000000000077", "10"))
        demo_current_users.append(Tag("000000000000000000000078", "10"))
    elif rand == 1:
        demo_current_users.append(Tag("000000000000000000000076", "10"))
        demo_current_users.append(Tag("000000000000000000000076", "10"))
        demo_current_users.append(Tag("000000000000000000000078", "10"))
    elif rand == 2:
        demo_current_users.append(Tag("000000000000000000000076", "10"))
        demo_current_users.append(Tag("000000000000000000000078", "10"))
    else:
        print("current_users : nobody")

    return demo_current_users

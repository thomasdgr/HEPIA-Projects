from typing import Dict
from datetime import datetime, timedelta

#Informations of a presence to keep in cache
class PresenceMemorised():
    stand_id: int
    last_presence_date: str
    #Timestamp when data is added in cache
    timestamp : datetime

    def __init__(self, stand_id, last_presence_date):
        self.stand_id = stand_id
        self.last_presence_date = last_presence_date
        self.timestamp = datetime.now().timestamp()

    #Return the usefull data for external use
    def get_transmit_form(self) -> Dict:
        #Copy, otherwise we remove an attribute of the object
        dict_of_object = self.__dict__.copy()
        dict_of_object.pop("timestamp", None)
        return dict_of_object

    #Return false if it is in the cache for a too long period of time
    def is_still_valid_for_cache(self) -> bool:
        current_time = datetime.now().timestamp()
        delta_time_min = (current_time - self.timestamp) / 60

        if delta_time_min>= 30:
            return False

        return True

#Keep in cache only none serialized data -> People who came to a stand and has not leaved it yet. { tag_id, info_presence}
presences_cache : Dict[str, PresenceMemorised] = {}
check_time_in_minutes : int = 30

#Add a presence to memorise in cache associated to the tag id_RFID_tag
def add_in_cache(id_RFID_tag : int, presence_to_memorize: PresenceMemorised) -> None:
    global presences_cache
    presences_cache[id_RFID_tag] = presence_to_memorize;

#Remove a presence to memorise in cache associated to the tag id_RFID_tag
def remove_from_cache(id_RFID_tag : int) -> None:
    global presences_cache
    #If does not exist, do nothing.
    presences_cache.pop(id_RFID_tag, None)

def is_tag_id_present_in_cache(id_RFID_tag : int) -> bool:
    return id_RFID_tag in presences_cache

#Checks if elements in cache are to be removed because they are in it for a too long period of time.
#If it's the case, element is removed
def check_presences_cache() -> None:
    #Copy obligated to iterate and remove data in original one
    for id_RFID_tag, presence_memorised in presences_cache.copy().items():
        if not presence_memorised.is_still_valid_for_cache():
            print(presences_cache)
            remove_from_cache(id_RFID_tag)
            print(presences_cache)

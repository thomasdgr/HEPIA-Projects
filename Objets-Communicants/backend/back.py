import mysql.connector
from pydantic import BaseModel
from typing import Dict
import json
from cache import *

mydb = mysql.connector.connect(
    host="localhost", user="user", password="test", database="bdd"
)
mycursor = mydb.cursor()

content = []

# Structure of received messages from raspberrys
class DataFromRaspberry(BaseModel):
    config: Dict
    new_people: Dict
    past_people: Dict


# Represents the presence of a person in a stand
class Presence(BaseModel):
    tag_id: str
    stand_id: int
    start_date: str
    end_date: str


# Return the person associated to the RFID tag tag_id
def get_person_of(tag_id: str) -> Dict:
    mycursor.execute(
        "SELECT Personne.user_id, Personne.nom, Personne.prenom FROM `Personne` INNER JOIN Possession ON Personne.user_id = Possession.user_id WHERE Possession.tag_id ="
        + '"'
        + tag_id
        + '"'
    )
    user_id_from_db = mycursor.fetchall()
    return {"user_id": user_id_from_db[0][0]}


# Return the RFID tag id associated to the person id_pers
def get_tag_id_of(id_pers: int) -> Dict:
    mycursor.execute(
        "SELECT TagRFID.tag_id FROM `TagRFID` INNER JOIN Possession ON TagRFID.tag_id = Possession.tag_id WHERE Possession.user_id ="
        + '"'
        + str(id_pers)
        + '"'
    )
    tag_id_from_db = mycursor.fetchall()
    return {"tag_id": tag_id_from_db[0][0]}


# Return all persons contained in the database
def get_all_pers() -> Dict:
    mycursor.execute("SELECT * FROM `Personne`")
    all_pers_from_db = mycursor.fetchall()

    dict_persons: Dict[str, Dict] = {}
    i = 0
    for tuple_info_pers in all_pers_from_db:
        dict_person = {}
        dict_person["user_id"] = tuple_info_pers[0]
        dict_person["name"] = tuple_info_pers[1]
        dict_person["surname"] = tuple_info_pers[2]
        dict_person["mail"] = tuple_info_pers[3]
        dict_person["phone_number"] = tuple_info_pers[4]

        dict_persons[str(i)] = dict_person
        i += 1

    return dict_persons


# Return all persons contained in the database
def get_all_stand() -> Dict:
    mycursor.execute("SELECT * FROM `Stand`")
    all_stands_from_db = mycursor.fetchall()
    dict_stands: Dict[str, Dict] = {}
    i = 0
    for tuple_info_stand in all_stands_from_db:
        dict_stand = {}
        dict_stand["stand_id"] = tuple_info_stand[0]
        dict_stand["nom"] = tuple_info_stand[1]
        dict_stand["marque"] = tuple_info_stand[2]

        dict_stands[str(i)] = dict_stand
        i += 1

    return dict_stands


# Add a new presence in the database
def add_presence_in_database(presence: Presence) -> None:
    val = (presence.tag_id, presence.stand_id, presence.start_date, presence.end_date)
    mycursor.execute(
        "INSERT INTO `PresenceStand`(`tag_id`, `stand_id`, `temps_initial`, `temps_final`) VALUES (%s, %s, %s, %s)",
        val,
    )
    mydb.commit()


# Get the last presence of the person id_pers
def get_presence_from_user_id(id_pers: int) -> Dict:
    id_tag_associated = get_tag_id_of(id_pers)["tag_id"]
    return get_presence_from_tag_id(id_tag_associated)


# Get the last presence of the tag id_tag
def get_presence_from_tag_id(tag_id) -> Dict:
    presence_data = ""
    if not is_tag_id_present_in_cache(tag_id):
        print("INFO: Data not found in cache. Takes it from database")
        mycursor.execute(
            "SELECT stand_id, temps_final FROM `PresenceStand` INNER JOIN Possession ON Possession.tag_id = PresenceStand.tag_id WHERE Possession.tag_id = "
            + '"'
            + tag_id
            + '"'
            + " ORDER BY temps_final DESC LIMIT 1"
        )
        presence_from_db = mycursor.fetchall()
        presence_data = PresenceMemorised(
            presence_from_db[0][0], presence_from_db[0][1]
        )
    else:
        print("INFO: Data successfully found in cache")

        presence_data = presences_cache[tag_id]
    return presence_data.get_transmit_form()


def handle_new_infos_from_raspberry(new_infos: DataFromRaspberry) -> None:
    # Check each time a new message is received, it could be less. Example a dedicated thread that awakes each 30 minutes.
    check_presences_cache()

    stand_id = new_infos.config["stand_id"]

    for id_RFID_tag, timing_dict in new_infos.past_people.items():
        presence_info = Presence(
            tag_id=id_RFID_tag,
            stand_id=stand_id,
            start_date=timing_dict["start_date"],
            end_date=timing_dict["end_date"],
        )
        # Data will be now serialized so we don't need it anymore in the cache.
        remove_from_cache(id_RFID_tag)
        add_presence_in_database(presence_info)

    for id_RFID_tag, timing_dict in new_infos.new_people.items():
        presence_to_memorize = PresenceMemorised(
            stand_id=stand_id, last_presence_date=timing_dict["start_date"]
        )
        add_in_cache(id_RFID_tag, presence_to_memorize)

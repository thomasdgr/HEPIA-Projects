var serverIp = "http://192.168.1.146:8000/";
final API_ROUTES = {
  "getAllStands": "stand/",
  "getAllPersons": "person/",
  "getPersonIDFromRFIDTag": "person/get_from_tag_id/", // "user_id": 0
  "getRFIDTagFromPersonID": "tag/get_from_user_id/",
  "getPresenceFromPersonID":
      "presence/get_from_user_id/", // stand_id & timestamp
  "getPresenceFromRFIDTag": "presence/get_from_tag_id/"
};

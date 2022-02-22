import 'package:flute/Data/location.dart';
import 'package:http/http.dart' as http;
import 'package:flute/Data/routes.dart';
import 'package:flute/Data/json_parser.dart';

Future<http.Response> fetchRFIDTagFromPersonID(int personID) {
  /// Retrieve the information about a person
  return http.get(Uri.parse(
      serverIp + API_ROUTES["getRFIDTagFromPersonID"]! + personID.toString()));
}

Future<PersonID> fetchPersonIDFromRFIDTag(String rfidTag) async {
  final apiCallPersonIDFromRFIDTag = await http.get(
      Uri.parse(serverIp + API_ROUTES["getPersonIDFromRFIDTag"]! + rfidTag));

  if (apiCallPersonIDFromRFIDTag.statusCode == 200) {
    return personIDFromJson(apiCallPersonIDFromRFIDTag.body);
  } else {
    throw Exception("Failed to load person id");
  }
}

Future<Presence> fetchPresenceFromPersonID(int personID) async {
  final apiCallPresenceFromID = await http.get(Uri.parse(
      serverIp + API_ROUTES["getPresenceFromPersonID"]! + personID.toString()));

  if (apiCallPresenceFromID.statusCode == 200) {
    return presenceFromJson(apiCallPresenceFromID.body);
  } else {
    throw Exception("Failed to load stand list");
  }
}

Future<Map<String, Stand>> fetchAllStands() async {
  final apiCallStands =
      await http.get(Uri.parse(serverIp + API_ROUTES["getAllStands"]!));

  if (apiCallStands.statusCode == 200) {
    return standFromJson(apiCallStands.body);
  } else {
    throw Exception("Failed to load stand list");
  }
}

Future<Map<String, Person>> fetchAllPerson() async {
  print("\n---\nfetchAllPerson\n---\n");
  print("Calling " + serverIp + API_ROUTES["getAllPersons"]!);
  final apiCallPersons =
      await http.get(Uri.parse(serverIp + API_ROUTES["getAllPersons"]!));

  if (apiCallPersons.statusCode == 200) {
    print("=>Success!!");
    return personFromJson(apiCallPersons.body);
  } else {
    print("Noooooo");
    throw Exception("Failed to load person list");
  }
}

Future<Map<Person, Presence>> fetchAllPersonAndPresence() async {
  Map<Person, Presence> resMap = Map<Person, Presence>();
  var personList = fetchAllPerson();

  personList.then((res) => (res.forEach((s, p) => () {
        fetchPresenceFromPersonID(p.userId).then((pres) => () {
              resMap[p] = pres;
            });
      })));

  return resMap;
}

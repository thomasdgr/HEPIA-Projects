// To parse this JSON data, do
//
//     final welcome = welcomeFromJson(jsonString);

import 'dart:convert';

Map<String, Person> personFromJson(String str) => Map.from(json.decode(str))
    .map((k, v) => MapEntry<String, Person>(k, Person.fromJson(v)));

String personToJson(Map<String, Person> data) => json.encode(
    Map.from(data).map((k, v) => MapEntry<String, dynamic>(k, v.toJson())));

class Person {
  Person({
    required this.userId,
    required this.name,
    required this.surname,
    required this.mail,
    required this.phoneNumber,
  });

  int userId;
  String name;
  String surname;
  String mail;
  String phoneNumber;

  factory Person.fromJson(Map<String, dynamic> json) => Person(
        userId: json["user_id"],
        name: json["name"],
        surname: json["surname"],
        mail: json["mail"],
        phoneNumber: json["phone_number"],
      );

  Map<String, dynamic> toJson() => {
        "user_id": userId,
        "name": name,
        "surname": surname,
        "mail": mail,
        "phone_number": phoneNumber,
      };
}

Presence presenceFromJson(String str) => Presence.fromJson(json.decode(str));

String presenceToJson(Presence data) => json.encode(data.toJson());

class Presence {
  Presence({
    required this.standId,
    required this.lastPresenceDate,
  });

  int standId;
  String lastPresenceDate;

  factory Presence.fromJson(Map<String, dynamic> json) => Presence(
        standId: json["stand_id"],
        lastPresenceDate: json["last_presence_date"],
      );

  Map<String, dynamic> toJson() => {
        "stand_id": standId,
        "last_presence_date": lastPresenceDate,
      };
}

Map<String, Stand> standFromJson(String str) => Map.from(json.decode(str))
    .map((k, v) => MapEntry<String, Stand>(k, Stand.fromJson(v)));

String standToJson(Map<String, Stand> data) => json.encode(
    Map.from(data).map((k, v) => MapEntry<String, dynamic>(k, v.toJson())));

class Stand {
  Stand({
    required this.standId,
    required this.nom,
    required this.marque,
  });

  int standId;
  String nom;
  String marque;

  factory Stand.fromJson(Map<String, dynamic> json) => Stand(
        standId: json["stand_id"],
        nom: json["nom"],
        marque: json["marque"],
      );

  Map<String, dynamic> toJson() => {
        "stand_id": standId,
        "nom": nom,
        "marque": marque,
      };
}

PersonID personIDFromJson(String str) => PersonID.fromJson(json.decode(str));

String personIdToJson(PersonID data) => json.encode(data.toJson());

class PersonID {
  PersonID({
    required this.userId,
  });

  int userId;

  factory PersonID.fromJson(Map<String, dynamic> json) => PersonID(
        userId: json["user_id"],
      );

  Map<String, dynamic> toJson() => {
        "user_id": userId,
      };
}

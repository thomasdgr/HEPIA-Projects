import 'dart:math';

List<String> locationNames = [
  "Conference Room 1",
  "Conference Room 2",
  "Gala",
  "Cantina",
  "Stand 1",
  "Stand 2",
  "Stand 3",
  "Stand 4",
  "Stand 6",
  "Stand 7",
  "Stand 8",
  "Stand 9",
  "Entrance",
  "Exit",
];

class Location {
  String? locationName;
  int? xCoords;
  int? yCoords;

  Location(String? locationName, int? xCoords, int? yCoords) {
    this.locationName = locationName;
    this.xCoords = xCoords;
    this.yCoords = yCoords;
  }
}

Location generateRandomLocation() {
  var rnd = Random();
  return Location(locationNames[rnd.nextInt(locationNames.length)], 0, 0);
}

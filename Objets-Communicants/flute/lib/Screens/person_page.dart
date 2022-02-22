import 'package:flutter/material.dart';
import 'package:flute/Data/json_parser.dart';
import 'package:transparent_image/transparent_image.dart';
import 'package:flute/Data/api.dart';

class PersonPage extends StatelessWidget {
  final Person person;

  const PersonPage({Key? key, required this.person}) : super(key: key);

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        title: Text("Success"),
      ),
      body: Column(
        mainAxisAlignment: MainAxisAlignment.start,
        children: <Widget>[
          Card(
            child: ListTile(
              title: Text(person.surname + " " + person.name.toUpperCase()),
              subtitle: Text("Person ID: " + person.userId.toString()),
              leading: FadeInImage.memoryNetwork(
                  placeholder: kTransparentImage,
                  image:
                      "https://upload.wikimedia.org/wikipedia/commons/7/7c/Profile_avatar_placeholder_large.png"),
            ),
          ),
          Card(
              child: ListTile(
            leading: const Icon(Icons.phone),
            title: Text("Phone number: " + person.phoneNumber),
          )),
          Card(
              child: ListTile(
            leading: const Icon(Icons.tag),
            title: Text("Email: " + person.mail),
          )),
          Card(
              child: const ListTile(
            leading: Icon(Icons.list),
            title: Text("List of registrations"),
            trailing: Icon(Icons.chevron_right),
          )),
          FutureBuilder<Presence>(
            future: fetchPresenceFromPersonID(person.userId),
            builder: (context, snapshot) {
              if (!snapshot.hasData) {
                return const Text("No location data yet for this user");
              } else if (snapshot.hasError) {
                return const Text("Error");
              } else {
                var tmp = snapshot.data!.standId.toString();
                return Card(
                    child: ListTile(
                  leading: const Icon(Icons.location_on),
                  title: FutureBuilder<Map<String, Stand>>(
                    future: fetchAllStands(),
                    builder: (context, snapshot) {
                      if (!snapshot.hasData) {
                        return Text("Last location: " + tmp);
                      } else if (snapshot.hasError) {
                        return Text("Last location: " + tmp);
                      } else {
                        var standList = snapshot.data!.values.toList();
                        for (int i = 0; i < standList.length; i++) {
                          if (standList[i].standId == int.parse(tmp)) {
                            return Text("Last location: " +
                                standList[i].nom +
                                " which is owned by " +
                                standList[i].marque);
                          }
                        }
                        return Text("Problem retrieving location");
                      }
                    },
                  ),
                  subtitle: Text("Last moment seen: " +
                      DateTime.fromMillisecondsSinceEpoch(
                              (double.parse(snapshot.data!.lastPresenceDate) *
                                      1000)
                                  .round())
                          .toString()),
                  trailing: const Icon(Icons.chevron_right),
                ));
              }
            },
          ),
          Card(
              child: const ListTile(
            leading: Icon(Icons.location_history),
            title: Text("Location list"),
            trailing: Icon(Icons.chevron_right),
          )),
          Card(
              child: const ListTile(
            leading: Icon(Icons.bar_chart),
            title: Text("Stats"),
            trailing: Icon(Icons.chevron_right),
          )),
          ElevatedButton(
            onPressed: () {},
            child: const Text("Check-in guest to Event"),
          ),
        ],
      ),
    );
  }
}

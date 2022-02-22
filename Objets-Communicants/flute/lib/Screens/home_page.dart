import 'package:flute/Data/api.dart';
import 'package:flutter/material.dart';
import 'package:flute/Data/json_parser.dart';
import 'package:flute/Screens/person_page.dart';

class HomePage extends StatefulWidget {
  const HomePage({Key? key, required this.title}) : super(key: key);

  final String title;

  @override
  State<HomePage> createState() => _HomePageState();
}

class _HomePageState extends State<HomePage> {
  int tabs = 0;

  void _changePage(BuildContext context) {
    setState(() {
      // each time this is called it will update the page
    });
  }

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        title: Text(widget.title),
      ),
      body: FutureBuilder<Map<String, Person>>(
          future: fetchAllPerson(),
          builder: (context, snapshot) {
            if (!snapshot.hasData) {
              return const Center(
                child: CircularProgressIndicator(),
              );
            } else if (snapshot.hasError) {
              return Center(
                child: Column(
                  mainAxisAlignment: MainAxisAlignment.center,
                  children: <Widget>[
                    const Text(
                      ':(',
                    ),
                  ],
                ),
              );
            } else {
              var persons = snapshot.data?.entries.toList();
              var colors = [
                Colors.blue.shade300,
                Colors.blue.shade700,
              ];
              return ListView.builder(
                itemCount: persons?.length,
                itemBuilder: (context, index) {
                  return Card(
                      color: colors[index % colors.length],
                      child: ListTile(
                        onTap: () {
                          print("callling");
                          Navigator.push(
                              context,
                              MaterialPageRoute(
                                  builder: (context) => PersonPage(
                                        person: persons![index].value,
                                      )));
                        },
                        leading: Icon(Icons.person),
                        title: Text("#" +
                            persons![index].value.userId.toString() +
                            " " +
                            persons[index].value.surname +
                            " " +
                            persons[index].value.name),
                        trailing: Icon(Icons.chevron_right),
                      ));
                },
              );
            }
          }),
    );
  }
}

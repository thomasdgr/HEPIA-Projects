import 'package:flutter/material.dart';
import 'package:flute/Data/api.dart';
import 'package:flute/Screens/person_page.dart';
import 'package:http/http.dart';
import 'package:flute/Screens/error_page.dart';

class SearchPage extends StatefulWidget {
  const SearchPage({Key? key, required this.title}) : super(key: key);

  final String title;

  @override
  State<SearchPage> createState() => _SearchPageState();
}

class _SearchPageState extends State<SearchPage> {
  int tabs = 0;
  // identifies the form widget for validation
  final _formKey = GlobalKey<FormState>();
  final _textFormsController = {
    "rfidTag": TextEditingController(),
    "userId": TextEditingController(),
  };

  void _changePage(BuildContext context) {
    setState(() {
      // each time this is called it will update the page
    });
  }

  void launchSearch(String type, String values) async {
    List<String> args = values.split(" ");
    bool demo = true;
    if (values.isEmpty || values == "") {
      return;
    }
    switch (type) {
      case "rfidTag":
        {
          try {
            var personID = await fetchPersonIDFromRFIDTag(values);
            var persons = await fetchAllPerson();
            var personList = persons.entries.toList();
            for (int i = 0; i < personList.length; i++) {
              if (personList[i].value.userId == personID.userId) {
                Navigator.push(
                    context,
                    MaterialPageRoute(
                        builder: (context) =>
                            PersonPage(person: personList[i].value)));
                return;
              }
            }
            Navigator.push(
                context,
                MaterialPageRoute(
                    builder: (context) =>
                        ErrorPage(type: type, values: values)));
          } catch (Exception) {
            Navigator.push(
                context,
                MaterialPageRoute(
                    builder: (context) =>
                        ErrorPage(type: type, values: values)));
          }
        }
        break;
      case "userId":
        {
          try {
            var persons = await fetchAllPerson();
            var personList = persons.entries.toList();
            for (int i = 0; i < personList.length; i++) {
              if (personList[i].value.userId == int.parse(values)) {
                Navigator.push(
                    context,
                    MaterialPageRoute(
                        builder: (context) =>
                            PersonPage(person: personList[i].value)));
                return;
              }
            }
            Navigator.push(
                context,
                MaterialPageRoute(
                    builder: (context) =>
                        ErrorPage(type: type, values: values)));
          } catch (Exception) {
            Navigator.push(
                context,
                MaterialPageRoute(
                    builder: (context) =>
                        ErrorPage(type: type, values: values)));
          }
          // Person? p = getPersonByID(args[0], demo);
          // if (p != null) {
          //   print("Launching person page");
          // } else {}
        }
        break;
      default:
        break;
    }
  }

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        title: Text(widget.title),
      ),
      body: Center(
        child: Column(
          mainAxisAlignment: MainAxisAlignment.start,
          children: <Widget>[
            Container(
              margin: const EdgeInsets.fromLTRB(0, 25, 0, 0),
              child: const Text(
                'Search for a specific user, list of user for an event, ...',
                style: TextStyle(fontSize: 20),
              ),
            ),
            Container(
              margin: const EdgeInsets.fromLTRB(25, 0, 25, 0),
              child: Form(
                key: _formKey,
                child: Column(
                  children: <Widget>[
                    TextFormField(
                      controller: _textFormsController["rfidTag"],
                      decoration: const InputDecoration(
                        icon: Icon(Icons.tag),
                        hintText: '<tag>',
                        labelText: 'By RFID Tag number',
                      ),
                    ),
                    TextFormField(
                      controller: _textFormsController["userId"],
                      decoration: const InputDecoration(
                        icon: Icon(Icons.perm_identity),
                        hintText: '<id>',
                        labelText: 'By User id',
                      ),
                    ),
                    Row(
                      mainAxisAlignment: MainAxisAlignment.center,
                      children: [
                        Padding(
                          padding: const EdgeInsets.all(8.0),
                          child: ElevatedButton(
                              onPressed: () {
                                print("bim1");
                                print(_textFormsController);
                                _textFormsController.forEach(
                                    (textFormName, contr) =>
                                        launchSearch(textFormName, contr.text));
                              },
                              child: const Text('Submit')),
                        ),
                        Padding(
                          padding: const EdgeInsets.all(8.0),
                          child: ElevatedButton(
                              onPressed: () {
                                _textFormsController
                                    .forEach((_, contr) => contr.text = "");
                              },
                              child: const Text('Clear')),
                        ),
                      ],
                    )
                  ],
                ),
              ),
            ),
          ],
        ),
      ),
    );
  }
}

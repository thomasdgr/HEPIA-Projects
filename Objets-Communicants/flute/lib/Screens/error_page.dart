import 'package:flutter/material.dart';

class ErrorPage extends StatelessWidget {
  const ErrorPage({Key? key, required this.type, required this.values})
      : super(key: key);

  final String type;
  final String values;

  @override
  Widget build(BuildContext context) {
    return Scaffold(
        appBar: AppBar(
          title: Text("Failure"),
        ),
        body: Column(
          children: <Widget>[
            Text("Search for " + this.type + " has failed"),
            Text("Value " + this.values + " might not exist"),
          ],
        ));
  }
}

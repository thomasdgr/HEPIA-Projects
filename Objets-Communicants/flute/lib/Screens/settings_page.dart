import 'package:flutter/material.dart';
import 'package:flute/Widgets/nav_bar.dart';

class SettingsPage extends StatefulWidget {
  const SettingsPage({Key? key, required this.title}) : super(key: key);

  final String title;

  @override
  State<SettingsPage> createState() => _SettingsPageState();
}

class _SettingsPageState extends State<SettingsPage> {
  int tabs = 0;
  String bottomBarIndex = "home";

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
    );
  }
}

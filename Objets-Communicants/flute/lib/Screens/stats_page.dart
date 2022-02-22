import 'package:flutter/material.dart';
import 'package:flute/Widgets/nav_bar.dart';

class StatsPage extends StatefulWidget {
  const StatsPage({Key? key, required this.title}) : super(key: key);

  final String title;

  @override
  State<StatsPage> createState() => _StatsPageState();
}

class _StatsPageState extends State<StatsPage> {
  int tabs = 0;

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        title: Text(widget.title),
      ),
      body: GridView.count(
        primary: false,
        padding: const EdgeInsets.all(20),
        crossAxisSpacing: 10,
        mainAxisSpacing: 10,
        crossAxisCount: 2,
        children: <Widget>[
          Container(
            padding: const EdgeInsets.all(8),
            child: Column(
              mainAxisAlignment: MainAxisAlignment.center,
              children: [
                const Text(
                  "Guests inside the Convention today",
                  textAlign: TextAlign.center,
                  style: TextStyle(
                    fontSize: 20,
                  ),
                ),
                const Text(
                  "129",
                  style: TextStyle(
                    fontSize: 50,
                  ),
                ),
              ],
            ),
            color: Colors.blue[100],
          ),
          Container(
            padding: const EdgeInsets.all(8),
            child: Column(
              mainAxisAlignment: MainAxisAlignment.center,
              children: [
                const Text(
                  "Guests outside the Convention today",
                  textAlign: TextAlign.center,
                  style: TextStyle(
                    fontSize: 20,
                  ),
                ),
                const Text(
                  "69",
                  style: TextStyle(
                    fontSize: 50,
                  ),
                ),
              ],
            ),
            color: Colors.blue[200],
          ),
          Container(
            padding: const EdgeInsets.all(8),
            child: Column(
              mainAxisAlignment: MainAxisAlignment.center,
              children: [
                const Text(
                  "Most successful stand is Microsoft at",
                  textAlign: TextAlign.center,
                  style: TextStyle(
                    fontSize: 20,
                  ),
                ),
                const Text(
                  "40 visits",
                  style: TextStyle(
                    fontSize: 50,
                  ),
                ),
              ],
            ),
            color: Colors.blue[300],
          ),
          Container(
            padding: const EdgeInsets.all(8),
            child: Column(
              mainAxisAlignment: MainAxisAlignment.center,
              children: [
                const Text(
                  "Busiest hour is",
                  textAlign: TextAlign.center,
                  style: TextStyle(
                    fontSize: 20,
                  ),
                ),
                const Text(
                  "14h31",
                  style: TextStyle(
                    fontSize: 50,
                  ),
                ),
              ],
            ),
            color: Colors.blue[400],
          ),
          Container(
            padding: const EdgeInsets.all(8),
            child: Column(
              mainAxisAlignment: MainAxisAlignment.center,
              children: [
                const Text(
                  "The conference #1 has ",
                  textAlign: TextAlign.center,
                  style: TextStyle(
                    fontSize: 20,
                  ),
                ),
                const Text(
                  "39 guests",
                  style: TextStyle(
                    fontSize: 50,
                  ),
                ),
                const Text(
                  "View",
                  style: TextStyle(
                    fontSize: 20,
                  ),
                ),
                const Icon(Icons.arrow_downward),
              ],
            ),
            color: Colors.blue[500],
          ),
          Container(
            padding: const EdgeInsets.all(8),
            child: Column(
              mainAxisAlignment: MainAxisAlignment.center,
              children: [
                const Text(
                  "Guest that are not in Workshop #3",
                  textAlign: TextAlign.center,
                  style: TextStyle(
                    fontSize: 20,
                  ),
                ),
                const Text(
                  "2",
                  style: TextStyle(
                    fontSize: 50,
                  ),
                ),
                const Text(
                  "View",
                  style: TextStyle(
                    fontSize: 20,
                  ),
                ),
                const Icon(Icons.arrow_downward),
              ],
            ),
            color: Colors.red[600],
          ),
        ],
      ),
    );
  }
}

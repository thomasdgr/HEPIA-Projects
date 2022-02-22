import 'package:flutter/material.dart';
import 'package:flute/Screens/home_page.dart';
import 'package:flute/Screens/stats_page.dart';
import 'package:flute/Screens/search_page.dart';
import 'package:flute/Screens/settings_page.dart';
import 'package:flute/Widgets/nav_bar.dart';
import 'package:flute/Data/api.dart';

void main() {
  runApp(const MyApp());
}

class MyApp extends StatelessWidget {
  const MyApp({Key? key}) : super(key: key);

  // This widget is the root of your application.
  @override
  Widget build(BuildContext context) {
    return MaterialApp(
      title: 'Event Tracker App',
      theme: ThemeData(
        brightness: Brightness.dark,
        primarySwatch: Colors.blue,
      ),
      home: const RouterPage(title: 'Event Tracker App'),
      debugShowCheckedModeBanner: false,
    );
  }
}

class RouterPage extends StatefulWidget {
  const RouterPage({Key? key, required this.title}) : super(key: key);

  final String title;

  @override
  _RouterPageState createState() => _RouterPageState();
}

class _RouterPageState extends State<RouterPage> {
  int _currentPage = 0;
  final PageController _pageController = PageController();

  List<Widget> _screens = const <Widget>[
    HomePage(title: "Guest List"),
    StatsPage(title: "Stats"),
    SearchPage(title: "Search for guests"),
    SettingsPage(title: "Settings")
  ];

  void _onPageChanged(int index) {
    setState(() {
      _currentPage = index;
    });
  }

  void _onItemTapped(int selectedIndex) {
    _pageController.jumpToPage(selectedIndex);
  }

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      body: PageView(
        controller: _pageController,
        children: _screens,
        onPageChanged: _onPageChanged,
        physics: const NeverScrollableScrollPhysics(),
      ),
      bottomNavigationBar:
          NavBar(onBottomNavBarItemPress: _onItemTapped, index: _currentPage),
    );
  }
}

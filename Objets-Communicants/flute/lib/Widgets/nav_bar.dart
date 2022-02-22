import 'package:flutter/material.dart';
import 'package:flute/Data/routes.dart';

class NavBar extends StatefulWidget {
  final void Function(int) onBottomNavBarItemPress;
  final int index;

  const NavBar(
      {Key? key, required this.onBottomNavBarItemPress, required this.index})
      : super(key: key);

  @override
  State<NavBar> createState() => _NavBarState();
}

class _NavBarState extends State<NavBar> {
  @override
  Widget build(BuildContext context) {
    return BottomNavigationBar(
      items: const <BottomNavigationBarItem>[
        BottomNavigationBarItem(
          icon: Icon(Icons.home),
          label: 'Home',
        ),
        BottomNavigationBarItem(
          icon: Icon(Icons.bar_chart),
          label: 'Stats',
        ),
        BottomNavigationBarItem(
          icon: Icon(Icons.person_search),
          label: 'Search',
        ),
        BottomNavigationBarItem(
          icon: Icon(Icons.settings),
          label: 'Settings',
        )
      ],
      currentIndex: widget.index,
      onTap: widget.onBottomNavBarItemPress,
      selectedItemColor: Colors.blue,
      unselectedItemColor: Colors.grey,
      showUnselectedLabels: true,
    );
  }
}

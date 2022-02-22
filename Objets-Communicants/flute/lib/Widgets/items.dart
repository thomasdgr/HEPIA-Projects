import 'package:flutter/widgets.dart';
import 'package:flute/person.dart';

abstract class ListItem {
  Widget buildTitle(BuildContext context);

  Widget buildSubtitle(BuildContext context);

  Widget buildImage(BuildContext context);
}

class SearchPersonItem implements ListItem {
  List<Person>? p;

  @override
  Widget buildImage(BuildContext context) {
    // TODO: implement buildImage
    throw UnimplementedError();
  }

  @override
  Widget buildSubtitle(BuildContext context) {
    // TODO: implement buildSubtitle
    throw UnimplementedError();
  }

  @override
  Widget buildTitle(BuildContext context) {
    // TODO: implement buildTitle
    throw UnimplementedError();
  }
}

class PlacePersonItem implements ListItem {
  List<Person>? p;

  @override
  Widget buildImage(BuildContext context) {
    // TODO: implement buildImage
    throw UnimplementedError();
  }

  @override
  Widget buildSubtitle(BuildContext context) {
    // TODO: implement buildSubtitle
    throw UnimplementedError();
  }

  @override
  Widget buildTitle(BuildContext context) {
    // TODO: implement buildTitle
    throw UnimplementedError();
  }
}

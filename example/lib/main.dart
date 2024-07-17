import 'dart:async';

import 'package:flutter/material.dart';
import 'package:flutter_timezone/flutter_timezone.dart';

void main() => runApp(MyApp());

class MyApp extends StatefulWidget {
  @override
  _MyAppState createState() => _MyAppState();
}

class _MyAppState extends State<MyApp> {
  String _timezone = 'Unknown';
  List<String> _availableTimezones = <String>[];

  @override
  void initState() {
    super.initState();
    _initData();
  }

  Future<void> _initData() async {
    try {
      _timezone = await FlutterTimezone.getLocalTimezone();
    } catch (e) {
      print('Could not get the local timezone');
    }
    try {
      _availableTimezones = await FlutterTimezone.getAvailableTimezones();
      _availableTimezones.sort();
    } catch (e) {
      print('Could not get available timezones');
    }
    if (mounted) {
      setState(() {});
    }
  }

  @override
  Widget build(BuildContext context) {
    return MaterialApp(
      home: Scaffold(
        floatingActionButton: FloatingActionButton(
          onPressed: () async {
            await _initData();
          },
          child: Icon(Icons.refresh),
        ),
        body: Padding(
          padding: const EdgeInsets.all(12.0),
          child: Column(
            crossAxisAlignment: CrossAxisAlignment.start,
            children: <Widget>[
              Text(
                'Local Time Zone',
                style: Theme.of(context).textTheme.titleMedium,
              ),
              Text(
                _timezone,
                key: const ValueKey('timeZoneLabel'),
              ),
              SizedBox(height: 12),
              Text(
                'Available Time Zones (${_availableTimezones.length})',
                style: Theme.of(context).textTheme.titleMedium,
              ),
              Expanded(
                child: ListView.builder(
                  itemCount: _availableTimezones.length,
                  itemBuilder: (_, index) => Text(_availableTimezones[index]),
                ),
              )
            ],
          ),
        ),
      ),
    );
  }
}

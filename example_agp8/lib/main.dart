import 'dart:async';

import 'package:flutter/material.dart';
import 'package:flutter_timezone/flutter_timezone.dart';

void main() => runApp(const MyApp());

class MyApp extends StatefulWidget {
  const MyApp({super.key});

  @override
  State<MyApp> createState() => _MyAppState();
}

class _MyAppState extends State<MyApp> {
  TimezoneInfo? _timezone;
  List<TimezoneInfo> _availableTimezones = [];

  @override
  void initState() {
    super.initState();
    _initData();
  }

  Future<void> _initData() async {
    _timezone = await FlutterTimezone.getLocalTimezone();
    _availableTimezones = await FlutterTimezone.getAvailableTimezones();
    _availableTimezones.sort((a, b) => a.identifier.compareTo(b.identifier));
    if (mounted) {
      setState(() {});
    }
  }

  @override
  Widget build(BuildContext context) {
    return MaterialApp(
      home: Scaffold(
        floatingActionButton: FloatingActionButton(
          onPressed: _initData,
          child: const Icon(Icons.refresh),
        ),
        body: Padding(
          padding: const EdgeInsets.all(12),
          child: Column(
            crossAxisAlignment: CrossAxisAlignment.start,
            children: <Widget>[
              Text(
                'Local Time Zone',
                style: Theme.of(context).textTheme.titleMedium,
              ),
              Text(
                '${_timezone?.identifier ?? 'Unknown'} - ${_timezone?.localizedName?.name ?? 'Unknown'}',
                key: const ValueKey('timeZoneLabel'),
              ),
              const SizedBox(height: 12),
              Text(
                'Available Time Zones (${_availableTimezones.length})',
                style: Theme.of(context).textTheme.titleMedium,
              ),
              Expanded(
                child: ListView.builder(
                  itemCount: _availableTimezones.length,
                  itemBuilder: (_, index) {
                    final info = _availableTimezones[index];
                    return Text('${info.identifier} - ${info.localizedName?.name ?? 'Unknown'}');
                  },
                ),
              )
            ],
          ),
        ),
      ),
    );
  }
}

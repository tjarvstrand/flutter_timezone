@TestOn('browser')
import 'package:flutter/services.dart';
import 'package:flutter_test/flutter_test.dart';
import 'package:flutter_timezone/flutter_timezone_web.dart';

void main() {
  TestWidgetsFlutterBinding.ensureInitialized();

  test('web plugin uses real JS interop for timezone data', () async {
    final plugin = FlutterTimezonePlugin();

    final local =
        await plugin.handleMethodCall(const MethodCall('getLocalTimezone'));
    expect(local, isA<String>());
    expect((local as String).isNotEmpty, isTrue);

    final available = await plugin
        .handleMethodCall(const MethodCall('getAvailableTimezones'));
    expect(available, isA<List<String>>());
    final list = available as List<String>;
    expect(list.isNotEmpty, isTrue);
    expect(list.every((value) => value.isNotEmpty), isTrue);

    const stableSample = <String>[
      'Africa/Abidjan',
      'Africa/Accra',
      'Africa/Cairo',
      'Africa/Johannesburg',
      'America/New_York',
      'America/Chicago',
      'America/Denver',
      'America/Los_Angeles',
      'Asia/Tokyo',
      'Asia/Shanghai',
      'Europe/London',
      'Europe/Paris',
    ];
    for (final zone in stableSample) {
      expect(list, contains(zone));
    }
  });
}

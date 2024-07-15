import 'package:flutter/material.dart';
import 'package:flutter_test/flutter_test.dart';
import 'package:flutter_timezone_example/main.dart';
import 'package:integration_test/integration_test.dart';

void main() {
  IntegrationTestWidgetsFlutterBinding.ensureInitialized();

  group('getLocalTimezone', () {
    final expected = const String.fromEnvironment('EXPECTED_TZ');

    testWidgets('check that the local timezone is $expected', (tester) async {
      await tester.pumpWidget(MyApp());
      await tester.pumpAndSettle();

      Text tzTextWidget = find
          .byKey(const ValueKey('timeZoneLabel'))
          .evaluate()
          .first
          .widget as Text;

      expect(tzTextWidget.data, expected);
    });
  });
}

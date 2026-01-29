import 'dart:async';

import 'package:flutter/services.dart';
import 'package:flutter_timezone/timezone_info.dart';

export 'package:flutter_timezone/timezone_info.dart';

///
/// Class for getting the native timezone.
///
class FlutterTimezone {
  static const MethodChannel _channel = MethodChannel('flutter_timezone');

  ///
  /// Returns local timezone from the native layer.
  ///
  /// On supported platforms (see README), you can optionally provide a locale code (e.g. "en_US", "de") to get the
  /// localized name of the timezone in that locale, if provided by the underlying platform.
  static Future<TimezoneInfo> getLocalTimezone([String? locale]) async {
    final localTimezone =
        await _channel.invokeMethod('getLocalTimezone', locale);
    if (localTimezone == null) {
      throw ArgumentError('Invalid return from platform getLocalTimezone()');
    }
    if (localTimezone is String) {
      return TimezoneInfo(identifier: localTimezone);
    }
    return TimezoneInfo.fromJson(localTimezone);
  }

  ///
  /// Gets the list of available timezones from the native layer.
  ///
  /// On supported platforms (see README), you can optionally provide a locale code (e.g. "en_US", "de") to get the
  /// localized names of the timezones in that locale, if provided by the underlying platform.
  static Future<List<TimezoneInfo>> getAvailableTimezones(
      [String? locale]) async {
    final availableTimezones =
        await _channel.invokeListMethod('getAvailableTimezones', locale);
    if (availableTimezones == null) {
      throw ArgumentError(
          'Invalid return from platform getAvailableTimezones()');
    }
    return availableTimezones.map((timezone) {
      if (timezone is String) {
        return TimezoneInfo(identifier: timezone);
      }
      return TimezoneInfo.fromJson(timezone);
    }).toList();
  }
}

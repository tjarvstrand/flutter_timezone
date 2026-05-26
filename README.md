# flutter_timezone

[![pub package](https://img.shields.io/pub/v/flutter_timezone.svg)](https://pub.dev/packages/flutter_timezone)
[![Keep a Changelog v1.1.0](https://img.shields.io/badge/changelog-Keep%20a%20Changelog%20v1.1.0-%23E05735)](https://keepachangelog.com/en/1.1.0/)

A flutter plugin for getting the local timezone of the OS.

This is a fork of the original [flutter_native_timezone](https://pub.dev/packages/flutter_native_timezone) due to lack of maintenance of that package.

## Getting Started

Install this package and everything good will just follow along with you.

## Usage examples

### Get the timezone
```dart
final TimezoneInfo currentTimeZone = await FlutterTimezone.getLocalTimezone();
```

### Localized timezone names

On supported platforms Timezone info will contain the localized timezone name. Currently, this is supported on:
 - Android
 - MacOS
 - iOS

## Reference

[Wikipedia's list of TZ database names](https://en.wikipedia.org/wiki/List_of_tz_database_time_zones)

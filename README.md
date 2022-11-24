# flutter_timezone

A flutter plugin for getting the local timezone of the OS.

This is a fork of the original [flutter_native_timezone](https://pub.dev/packages/flutter_native_timezone) due to lack of maintenance of that package.

## Getting Started

Install this package and update the `build.gradle` file of your Android app to enable [desugaring](https://developer.android.com/studio/releases/gradle-plugin#j8-library-desugaring). Please see the link on desugaring for details but the main parts needed in this Gradle file would be

```gradle
android {
  defaultConfig {
    multiDexEnabled true
  }

  compileOptions {
    // Flag to enable support for the new language APIs
    coreLibraryDesugaringEnabled true
    // Sets Java compatibility to Java 8
    sourceCompatibility JavaVersion.VERSION_1_8
    targetCompatibility JavaVersion.VERSION_1_8
  }
}

dependencies {
  coreLibraryDesugaring 'com.android.tools:desugar_jdk_libs:1.2.0'
}
```

## Usage examples

### Get the timezone
```dart
final String currentTimeZone = await FlutterTimezone.getLocalTimezone();
```

## Reference

[Wikipedia's list of TZ database names](https://en.wikipedia.org/wiki/List_of_tz_database_time_zones)

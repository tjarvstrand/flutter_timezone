## 2.0.1

Remove unused dependencies.

## 2.0.0

Support for Wasm compilation.

This updates the code to use the new web and js_interop libraries, which means that Flutter 3.22.0
or later is required.

## 1.0.8

Android:
 - Bump Kotlin version to 1.6.21. Fixes [#15](https://github.com/tjarvstrand/flutter_timezone/issues/15).

Note: This version may require running a Gradle clean BEFORE you upgrade.

## 1.0.7

Android:
- Set JVM target to Java 8 for Kotlin language. Fixes [#10](https://github.com/tjarvstrand/flutter_timezone/issues/10).

## 1.0.6

Re-add lost example file.

## 1.0.5

Support for Android Gradle Plugin version 8.

## 1.0.4

Revert Android minSDKVersion to 16 since calls to newer APIs are guarded.

## 1.0.3

Enable MacOS support

## 1.0.2

Enable web support

## 1.0.1

* iOS fixes for example app
* Change package name to net.wolverinebeach
* Fix method channel name typo on iOS

## 1.0.0

Initial release as flutter_timezone. This release is built on top of 
[flutter_native_timezone](https://github.com/pinkfish/flutter_native_timezone) v2.0.1, with the 
following additional changes cherry-picked:
* [#37 minSDkVersion set to 26 because...](https://github.com/pinkfish/flutter_native_timezone/pull/37)
* [#42 Added link to Wikipedia's list of TZs; fixed typos](https://github.com/pinkfish/flutter_native_timezone/pull/42)
* [#48 Fixing issue "The Android Gradle plugin supports only Kotlin Gradle plugin version 1.5.20 and higher."](https://github.com/pinkfish/flutter_native_timezone/pull/48)

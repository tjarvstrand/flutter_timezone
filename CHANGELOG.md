# Changelog

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.1.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

## [Unreleased]

### Added

- Support for Android Gradle Plugin 9.x. Thanks [@giaquo](https://github.com/giaquo).

### Fixed

- Adhere to "Keep a Changelog" format

## [5.0.2] - 2026-03-15

### Fixed

- JS interop types ([#57](https://github.com/tjarvstrand/flutter_timezone/issues/57),
  [#59](https://github.com/tjarvstrand/flutter_timezone/pull/59)).
  Thanks [@bsutton](https://github.com/bsutton) and
  [@lacostej](https://github.com/lacostej).

## [5.0.1]

### Fixed

- macOS localized timezone name retrieval on OSX 13+.

## [5.0.0]

### Changed

- **Breaking:** API return values are now `TimezoneInfo` objects containing both
  the timezone name and, on supported platforms, the localized timezone name.
- Minimum macOS version bumped to 10.14
  ([#50](https://github.com/tjarvstrand/flutter_timezone/pull/50)).
  Thanks [@bqubique](https://github.com/bqubique).

## [4.1.1]

### Fixed

- Linux: don't always return `true`.

## [4.1.0]

### Added

- Swift Package Manager support
  ([#44](https://github.com/tjarvstrand/flutter_timezone/pull/44)).
  Thanks [@MaikuB](https://github.com/MaikuB).

## [4.0.0]

### Added

- Linux support
  ([#40](https://github.com/tjarvstrand/flutter_timezone/pull/40)).
  Thanks [@dg76](https://github.com/dg76).

### Changed

- **Breaking:** On Android, this plugin now requires Java 17
  ([#42](https://github.com/tjarvstrand/flutter_timezone/pull/42)).
  Thanks [@kuhnroyal](https://github.com/kuhnroyal).

## [3.0.1]

### Removed

- Leftover reference to v1 Android embedding API
  ([#35](https://github.com/tjarvstrand/flutter_timezone/issues/35)).

## [3.0.0]

### Added

- Fetch a list of all available time zones on web in browsers that support it
  ([#34](https://github.com/tjarvstrand/flutter_timezone/pull/34)).
  Thanks [@HosamHasanRamadan](https://github.com/HosamHasanRamadan).

### Changed

- **Breaking:** Removed support for the old Android v1 embedding API which is no
  longer supported in Flutter > 3.24.x
  ([#35](https://github.com/tjarvstrand/flutter_timezone/issues/35)).

### Fixed

- Support for Windows < 11
  ([#36](https://github.com/tjarvstrand/flutter_timezone/pull/36)).
  Thanks [@domyd](https://github.com/domyd).

## [2.1.0]

### Added

- Windows support.

## [2.0.1]

### Removed

- Unused dependencies.

## [2.0.0]

### Changed

- Support for Wasm compilation. Updated to use the new web and `js_interop`
  libraries; Flutter 3.22.0 or later is now required.

## [1.0.8]

### Changed

- Android: bump Kotlin version to 1.6.21.
  Fixes [#15](https://github.com/tjarvstrand/flutter_timezone/issues/15).

  Note: this version may require running a Gradle clean BEFORE you upgrade.

## [1.0.7]

### Fixed

- Android: set JVM target to Java 8 for Kotlin language.
  Fixes [#10](https://github.com/tjarvstrand/flutter_timezone/issues/10).

## [1.0.6]

### Fixed

- Re-add lost example file.

## [1.0.5]

### Added

- Support for Android Gradle Plugin version 8.

## [1.0.4]

### Changed

- Revert Android `minSDKVersion` to 16 since calls to newer APIs are guarded.

## [1.0.3]

### Added

- macOS support.

## [1.0.2]

### Added

- Web support.

## [1.0.1]

### Changed

- Change package name to `net.wolverinebeach`.

### Fixed

- iOS example app.
- Method channel name typo on iOS.

## [1.0.0]

### Added

- Initial release as `flutter_timezone`, built on top of
  [flutter_native_timezone](https://github.com/pinkfish/flutter_native_timezone)
  v2.0.1 with the following changes cherry-picked:
  - [#37 minSDkVersion set to 26](https://github.com/pinkfish/flutter_native_timezone/pull/37)
  - [#42 Wikipedia TZ list link, typo fixes](https://github.com/pinkfish/flutter_native_timezone/pull/42)
  - [#48 Fix Kotlin Gradle plugin version requirement](https://github.com/pinkfish/flutter_native_timezone/pull/48)

[Unreleased]: https://github.com/tjarvstrand/flutter_timezone/compare/v5.0.2...HEAD
[5.0.2]: https://github.com/tjarvstrand/flutter_timezone/compare/v5.0.1...v5.0.2
[5.0.1]: https://github.com/tjarvstrand/flutter_timezone/compare/v5.0.0...v5.0.1
[5.0.0]: https://github.com/tjarvstrand/flutter_timezone/compare/v4.1.1...v5.0.0
[4.1.1]: https://github.com/tjarvstrand/flutter_timezone/compare/v4.1.0...v4.1.1
[4.1.0]: https://github.com/tjarvstrand/flutter_timezone/compare/v4.0.0...v4.1.0
[4.0.0]: https://github.com/tjarvstrand/flutter_timezone/compare/v3.0.1...v4.0.0
[3.0.1]: https://github.com/tjarvstrand/flutter_timezone/compare/v3.0.0...v3.0.1
[3.0.0]: https://github.com/tjarvstrand/flutter_timezone/compare/v2.1.0...v3.0.0
[2.1.0]: https://github.com/tjarvstrand/flutter_timezone/releases/tag/v2.1.0
[2.0.1]: https://github.com/tjarvstrand/flutter_timezone/releases/tag/v2.0.1
[2.0.0]: https://github.com/tjarvstrand/flutter_timezone/releases/tag/v2.0.0
[1.0.8]: https://github.com/tjarvstrand/flutter_timezone/releases/tag/v1.0.8
[1.0.7]: https://github.com/tjarvstrand/flutter_timezone/releases/tag/v1.0.7
[1.0.6]: https://github.com/tjarvstrand/flutter_timezone/releases/tag/v1.0.6
[1.0.5]: https://github.com/tjarvstrand/flutter_timezone/releases/tag/v1.0.5
[1.0.4]: https://github.com/tjarvstrand/flutter_timezone/releases/tag/v1.0.4
[1.0.3]: https://github.com/tjarvstrand/flutter_timezone/releases/tag/v1.0.3
[1.0.2]: https://github.com/tjarvstrand/flutter_timezone/releases/tag/v1.0.2
[1.0.1]: https://github.com/tjarvstrand/flutter_timezone/releases/tag/v1.0.1
[1.0.0]: https://github.com/tjarvstrand/flutter_timezone/releases/tag/v1.0.0

[agp9-guide]: https://docs.flutter.dev/release/breaking-changes/migrate-to-built-in-kotlin/for-plugin-authors

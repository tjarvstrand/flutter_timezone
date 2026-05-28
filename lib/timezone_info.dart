import 'package:equatable/equatable.dart';
import 'package:meta/meta.dart';

@immutable
class TimezoneInfo with EquatableMixin {
  TimezoneInfo({required this.identifier, this.localizedName});

  factory TimezoneInfo.fromJson(Map json) {
    final localizedName = json['localizedName'];
    return TimezoneInfo(
        identifier: json['identifier'] as String,
        localizedName: localizedName == null ? null : (name: localizedName, locale: json['locale']),);
  }

  /// The standardized IANA identifier for this timezone, e.g. "America/Los_Angeles", as reported by the underlying
  /// platform.
  final String identifier;

  /// The localized name for this timezone, e.g. "Central European Standard Time", as reported by the
  /// underlying platform.
  ///
  /// This is available if:
  ///  - flutter_timezone supports localized names on the current platform (see README for details).
  ///  - The requested locale exists on the current platform.
  ///  - The current platform provides a localized name for the current timezone in the requested locale.
  final ({String name, String locale})? localizedName;

  @override
  List<Object?> get props => [identifier, localizedName];
}

import 'dart:async';
import 'dart:js_interop';

import 'package:flutter/services.dart';
import 'package:flutter_web_plugins/flutter_web_plugins.dart';

///
/// The plugin class for the web, acts as the plugin inside bits
/// and connects to the js world.
///
class FlutterTimezonePlugin {
  static void registerWith(Registrar registrar) {
    final MethodChannel channel = MethodChannel(
      'flutter_timezone',
      const StandardMethodCodec(),
      registrar,
    );
    final FlutterTimezonePlugin instance = FlutterTimezonePlugin();
    channel.setMethodCallHandler(instance.handleMethodCall);
  }

  Future<dynamic> handleMethodCall(MethodCall call) async {
    switch (call.method) {
      case 'getLocalTimezone':
        return _getLocalTimeZone();
      case 'getAvailableTimezones':
        return _getAvailableTimezones();
      default:
        throw PlatformException(
            code: 'Unimplemented',
            details:
                "The flutter_native_timezone plugin for web doesn't implement "
                "the method '${call.method}'");
    }
  }

  /// Platform-specific implementation of determining the user's
  /// local time zone when running on the web.
  ///
  String _getLocalTimeZone() {
    return jsDateTimeFormat().resolvedOptions().timeZone;
  }

  List<String> _getAvailableTimezones() {
    final function = supportedValuesOf as _DartFunctionSupportedValuesOf?;
    return function?.call('timeZone') ?? [_getLocalTimeZone()];
  }
}

typedef _DartFunctionSupportedValuesOf = List<String> Function(String value);

@JS('Intl.supportedValuesOf')
external JSFunction? supportedValuesOf;

@JS('Intl.DateTimeFormat')
external _JSDateTimeFormat jsDateTimeFormat();

@JS('Intl.DateTimeFormat.prototype')
@staticInterop
abstract class _JSDateTimeFormat {}

extension on _JSDateTimeFormat {
  @JS()
  external _JSResolvedOptions resolvedOptions();
}

@JS()
@staticInterop
abstract class _JSResolvedOptions {}

extension on _JSResolvedOptions {
  @JS()
  external String get timeZone;
}

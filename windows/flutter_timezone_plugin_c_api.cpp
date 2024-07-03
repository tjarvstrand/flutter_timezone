#include "include/flutter_timezone/flutter_timezone_plugin_c_api.h"

#include <flutter/plugin_registrar_windows.h>

#include "flutter_timezone_plugin.h"

void FlutterTimezonePluginCApiRegisterWithRegistrar(
    FlutterDesktopPluginRegistrarRef registrar) {
  flutter_timezone::FlutterTimezonePlugin::RegisterWithRegistrar(
      flutter::PluginRegistrarManager::GetInstance()
          ->GetRegistrar<flutter::PluginRegistrarWindows>(registrar));
}

#ifndef FLUTTER_PLUGIN_FLUTTER_TIMEZONE_PLUGIN_H_
#define FLUTTER_PLUGIN_FLUTTER_TIMEZONE_PLUGIN_H_

#include <flutter/method_channel.h>
#include <flutter/plugin_registrar_windows.h>

#include <memory>

namespace flutter_timezone {
    constexpr auto kGetLocalTimezone = "getLocalTimezone";
    constexpr auto kGetAvailableTimezones = "getAvailableTimezones";

    class FlutterTimezonePlugin : public flutter::Plugin {
    public:
        static void RegisterWithRegistrar(flutter::PluginRegistrarWindows* registrar);

        FlutterTimezonePlugin();

        virtual ~FlutterTimezonePlugin();

        // Disallow copy and assign.
        FlutterTimezonePlugin(const FlutterTimezonePlugin&) = delete;
        FlutterTimezonePlugin& operator=(const FlutterTimezonePlugin&) = delete;

        // Called when a method is called on this plugin's channel from Dart.
        void HandleMethodCall(
            const flutter::MethodCall<flutter::EncodableValue>& method_call,
            std::unique_ptr<flutter::MethodResult<flutter::EncodableValue>> result);

    private:
        void GetLocalTimezone(std::unique_ptr<flutter::MethodResult<flutter::EncodableValue>>& result);
        void GetAvailableTimezones(std::unique_ptr<flutter::MethodResult<flutter::EncodableValue>>& result);
    };

}  // namespace flutter_timezone

#endif  // FLUTTER_PLUGIN_FLUTTER_TIMEZONE_PLUGIN_H_

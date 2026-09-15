#include "flutter_timezone_plugin.h"

// Includes <windows.h> and <icu.h>; must come before many other Windows headers.
#include "icu_loader.h"

#include <flutter/method_channel.h>
#include <flutter/plugin_registrar_windows.h>
#include <flutter/standard_method_codec.h>

#include <memory>
#include <sstream>

namespace flutter_timezone {

    namespace {

        constexpr auto kIcuUnavailableCode = "ICU_UNAVAILABLE";
        constexpr auto kIcuUnavailableMessage =
            "System ICU not found (requires Windows 10 version 1703 or later).";

        const IcuApi& SystemIcu() {
            static const IcuApi api = LoadIcuApi(kSystemIcuDlls);
            return api;
        }

    }  // namespace

    // static
    void FlutterTimezonePlugin::RegisterWithRegistrar(
        flutter::PluginRegistrarWindows* registrar) {
        auto channel =
            std::make_unique<flutter::MethodChannel<flutter::EncodableValue>>(
                registrar->messenger(), "flutter_timezone",
                &flutter::StandardMethodCodec::GetInstance());

        auto plugin = std::make_unique<FlutterTimezonePlugin>();

        channel->SetMethodCallHandler(
            [plugin_pointer = plugin.get()](const auto& call, auto result) {
                plugin_pointer->HandleMethodCall(call, std::move(result));
            });

        registrar->AddPlugin(std::move(plugin));
    }

    FlutterTimezonePlugin::FlutterTimezonePlugin() {}

    FlutterTimezonePlugin::~FlutterTimezonePlugin() {}

    void FlutterTimezonePlugin::HandleMethodCall(
        const flutter::MethodCall<flutter::EncodableValue>& method_call,
        std::unique_ptr<flutter::MethodResult<flutter::EncodableValue>> result) {

        if (method_call.method_name().compare(kGetLocalTimezone) == 0) {
            GetLocalTimezone(result);
        }
        else if (method_call.method_name().compare(kGetAvailableTimezones) == 0) {
            GetAvailableTimezones(result);
        }
        else {
            result->NotImplemented();
        }
    }

    /// <summary>
    /// Gets the local time zone as an IANA identifier.
    /// </summary>
    /// <remarks>
    /// If the local windows time zone cannot be matched with a valid IANA one, "Etc/Unknown" is
    /// returned.
    /// </remarks>
    void FlutterTimezonePlugin::GetLocalTimezone(
        std::unique_ptr<flutter::MethodResult<flutter::EncodableValue>>& result) {
        auto timezone = LocalTimezoneId(SystemIcu());
        if (!timezone) {
            result->Error(kIcuUnavailableCode, kIcuUnavailableMessage);
            return;
        }
        result->Success(flutter::EncodableValue(*timezone));
    }

    /// <summary>
    /// Gets all the available canonical IANA time zones.
    /// </summary>
    /// <returns>A vector of timezones as EncodableValue's.</returns>
    void FlutterTimezonePlugin::GetAvailableTimezones(
        std::unique_ptr<flutter::MethodResult<flutter::EncodableValue>>& result) {
        const auto& icu = SystemIcu();
        if (!icu.IsAvailable()) {
            result->Error(kIcuUnavailableCode, kIcuUnavailableMessage);
            return;
        }

        UErrorCode status = U_ZERO_ERROR;

        // open an enumeration for any kind of available timezone without country/offset filtering.
        auto tzEnumeration = icu.openTimeZoneIDEnumeration(
            USystemTimeZoneType::UCAL_ZONE_TYPE_CANONICAL,
            nullptr,
            nullptr,
            &status);

        if (U_FAILURE(status)) {
            result->Error(std::string(icu.errorName(status)), "Could not fetch available timezones.");
            return;
        }

        auto count = icu.enumCount(tzEnumeration, &status);

        std::vector<flutter::EncodableValue> timezones{};
        timezones.reserve(count);

        for (auto i = 0; i < count; i++) {
            auto buffer = icu.enumNext(tzEnumeration, nullptr, &status);

            if (U_FAILURE(status)) {
                // Failed to read the current value, try the next one.
                continue;
            }

            timezones.push_back(flutter::EncodableValue(std::string(buffer)));
        }

        // close the enumeration
        icu.enumClose(tzEnumeration);

        result->Success(flutter::EncodableList(timezones));
    }

} // namespace flutter_timezone

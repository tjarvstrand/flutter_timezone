#include "flutter_timezone_plugin.h"

// This must be included before many other Windows headers.
#include <windows.h>

// By default, the icu.h header uses char16_t to represent UTF-16 code units. Windows, however, uses
// wchar_t, so we define UCHAR_TYPE to get the type we want.
#define UCHAR_TYPE wchar_t
#include <icu.h>

#include <flutter/method_channel.h>
#include <flutter/plugin_registrar_windows.h>
#include <flutter/standard_method_codec.h>

#include <memory>
#include <sstream>

namespace flutter_timezone {

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
        // This entire function body could be replaced with a call to `ucal_getHostTimeZone`.
        // However, that function as only added in ICU 65, which is only available on Windows 11.
        // Once we drop support for older Windows versions, this should be replaced.

        // Get the current Windows time zone
        DYNAMIC_TIME_ZONE_INFORMATION tzInfo;
        GetDynamicTimeZoneInformation(&tzInfo);

        // Get the user's region
        wchar_t geoBuffer[4];
        GetUserDefaultGeoName(geoBuffer, ARRAYSIZE(geoBuffer));

        // Convert the `geoBuffer` to a single byte string, which is fine since the contents are
        // supposed to be basic ASCII.
        std::wstring geoW(geoBuffer);
#pragma warning(suppress : 4244)
        std::string geo(geoW.begin(), geoW.end());

        // Map the (Windows Time Zone, Region) pair to an IANA time zone ID
        UErrorCode status = U_ZERO_ERROR;
        UChar buffer[128];
        auto length = ucal_getTimeZoneIDForWindowsID(
            tzInfo.TimeZoneKeyName,
            -1,
            geo.c_str(),
            buffer,
            ARRAYSIZE(buffer),
            &status);

        if (length == 0) {
            // No mapping found between Windows and IANA time zone ids
            result->Success(flutter::EncodableValue(std::string(UCAL_UNKNOWN_ZONE_ID)));
        }

        std::wstring tz(buffer);
#pragma warning(suppress : 4244)
        result->Success(flutter::EncodableValue(std::string(tz.begin(), tz.end())));
    }

    /// <summary>
    /// Gets all the available canonical IANA time zones.
    /// </summary>
    /// <returns>A vector of timezones as EncodableValue's.</returns>
    void FlutterTimezonePlugin::GetAvailableTimezones(
        std::unique_ptr<flutter::MethodResult<flutter::EncodableValue>>& result) {
        UErrorCode status = U_ZERO_ERROR;

        // open an enumeration for any kind of available timezone without country/offset filtering.
        auto tzEnumeration = ucal_openTimeZoneIDEnumeration(
            USystemTimeZoneType::UCAL_ZONE_TYPE_CANONICAL,
            nullptr,
            nullptr,
            &status);

        if (U_FAILURE(status)) {
            result->Error(std::string(u_errorName(status)), "Could not fetch available timezones.");
        }

        auto count = uenum_count(tzEnumeration, &status);

        std::vector<flutter::EncodableValue> timezones{};
        timezones.reserve(count);

        for (auto i = 0; i < count; i++) {
            auto buffer = uenum_next(tzEnumeration, nullptr, &status);

            if (U_FAILURE(status)) {
                // Failed to read the current value, try the next one.
                continue;
            }

            timezones.push_back(flutter::EncodableValue(std::string(buffer)));
        }

        // close the enumeration
        uenum_close(tzEnumeration);

        result->Success(flutter::EncodableList(timezones));
    }

} // namespace flutter_timezone

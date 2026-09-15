#ifndef FLUTTER_PLUGIN_FLUTTER_TIMEZONE_ICU_LOADER_H_
#define FLUTTER_PLUGIN_FLUTTER_TIMEZONE_ICU_LOADER_H_

// This must be included before many other Windows headers.
#include <windows.h>

// By default, the icu.h header uses char16_t to represent UTF-16 code units. Windows, however, uses
// wchar_t, so we define UCHAR_TYPE to get the type we want.
#ifndef UCHAR_TYPE
#define UCHAR_TYPE wchar_t
#endif
#include <icu.h>

#include <optional>
#include <string>

namespace flutter_timezone {

    // Windows ships ICU as icuuc.dll + icuin.dll since 1703 and as the combined icu.dll since 1903
    // (https://learn.microsoft.com/windows/win32/intl/international-components-for-unicode--icu-).
    // Linking icu.lib makes the loader require icu.dll, so the whole app fails to start on older
    // systems. Instead, every system API that is not available on all Windows 10 versions is
    // resolved at runtime. Only the declarations from icu.h are used (inside decltype), so no
    // import library is linked.
    //
    // The legacy DLLs require COM to be initialized; the Flutter Windows runner calls
    // CoInitializeEx before any plugin runs.
    struct IcuApi {
        decltype(&ucal_getTimeZoneIDForWindowsID) getTimeZoneIDForWindowsID = nullptr;
        decltype(&ucal_openTimeZoneIDEnumeration) openTimeZoneIDEnumeration = nullptr;
        decltype(&uenum_count) enumCount = nullptr;
        decltype(&uenum_next) enumNext = nullptr;
        decltype(&uenum_close) enumClose = nullptr;
        decltype(&u_errorName) errorName = nullptr;

        // GetUserDefaultGeoName was added in Windows 10 1709.
        int (WINAPI* getUserDefaultGeoName)(LPWSTR, int) = nullptr;

        // The DLL the ICU functions were resolved from, or nullptr when ICU is unavailable.
        const wchar_t* source = nullptr;

        bool IsAvailable() const {
            return getTimeZoneIDForWindowsID && openTimeZoneIDEnumeration && enumCount && enumNext &&
                enumClose && errorName;
        }
    };

    struct IcuDllNames {
        const wchar_t* combined;
        const wchar_t* i18n;
        const wchar_t* common;
    };

    inline constexpr IcuDllNames kSystemIcuDlls{ L"icu.dll", L"icuin.dll", L"icuuc.dll" };

    namespace icu_loader_internal {

        // System32 only, so an app-local file can never shadow the OS ICU.
        inline HMODULE LoadSystemDll(const wchar_t* name) {
            return LoadLibraryExW(name, nullptr, LOAD_LIBRARY_SEARCH_SYSTEM32);
        }

        template <typename T>
        inline void Resolve(HMODULE module, const char* name, T& out) {
            out = module ? reinterpret_cast<T>(GetProcAddress(module, name)) : nullptr;
        }

        inline void ResolveI18n(HMODULE module, IcuApi& api) {
            Resolve(module, "ucal_getTimeZoneIDForWindowsID", api.getTimeZoneIDForWindowsID);
            Resolve(module, "ucal_openTimeZoneIDEnumeration", api.openTimeZoneIDEnumeration);
        }

        inline void ResolveCommon(HMODULE module, IcuApi& api) {
            Resolve(module, "uenum_count", api.enumCount);
            Resolve(module, "uenum_next", api.enumNext);
            Resolve(module, "uenum_close", api.enumClose);
            Resolve(module, "u_errorName", api.errorName);
        }

    }  // namespace icu_loader_internal

    // Resolves ICU from `names.combined`, falling back to `names.i18n` + `names.common`. Modules that
    // provide a complete API stay loaded for the lifetime of the process.
    inline IcuApi LoadIcuApi(const IcuDllNames& names) {
        using namespace icu_loader_internal;

        IcuApi api;
        Resolve(GetModuleHandleW(L"kernel32.dll"), "GetUserDefaultGeoName", api.getUserDefaultGeoName);

        if (HMODULE combined = LoadSystemDll(names.combined)) {
            ResolveI18n(combined, api);
            ResolveCommon(combined, api);
            if (api.IsAvailable()) {
                api.source = names.combined;
                return api;
            }
            FreeLibrary(combined);
        }

        HMODULE i18n = LoadSystemDll(names.i18n);
        HMODULE common = LoadSystemDll(names.common);
        ResolveI18n(i18n, api);
        ResolveCommon(common, api);
        if (api.IsAvailable()) {
            api.source = names.i18n;
            return api;
        }

        if (i18n) FreeLibrary(i18n);
        if (common) FreeLibrary(common);
        IcuApi unavailable;
        unavailable.getUserDefaultGeoName = api.getUserDefaultGeoName;
        return unavailable;
    }

    // Gets the local time zone as an IANA identifier, or std::nullopt when ICU is unavailable.
    // If the local Windows time zone cannot be matched with a valid IANA one, "Etc/Unknown" is
    // returned.
    inline std::optional<std::string> LocalTimezoneId(const IcuApi& api) {
        if (!api.IsAvailable()) {
            return std::nullopt;
        }

        // This entire function body could be replaced with a call to `ucal_getHostTimeZone`.
        // However, that function as only added in ICU 65, which is only available on Windows 11.
        // Once we drop support for older Windows versions, this should be replaced.

        // Get the current Windows time zone
        DYNAMIC_TIME_ZONE_INFORMATION tzInfo;
        GetDynamicTimeZoneInformation(&tzInfo);

        // Get the user's region. Without it ICU uses the territory-neutral ("001") mapping.
        std::string geo;
        if (api.getUserDefaultGeoName) {
            wchar_t geoBuffer[4] = {};
            if (api.getUserDefaultGeoName(geoBuffer, ARRAYSIZE(geoBuffer)) > 0) {
                // The contents are supposed to be basic ASCII.
                std::wstring geoW(geoBuffer);
#pragma warning(suppress : 4244)
                geo.assign(geoW.begin(), geoW.end());
            }
        }

        // Map the (Windows Time Zone, Region) pair to an IANA time zone ID
        UErrorCode status = U_ZERO_ERROR;
        UChar buffer[128];
        auto length = api.getTimeZoneIDForWindowsID(
            tzInfo.TimeZoneKeyName,
            -1,
            geo.empty() ? nullptr : geo.c_str(),
            buffer,
            ARRAYSIZE(buffer),
            &status);

        if (U_FAILURE(status) || length <= 0) {
            // No mapping found between Windows and IANA time zone ids
            return std::string(UCAL_UNKNOWN_ZONE_ID);
        }

        std::wstring tz(buffer, length);
#pragma warning(suppress : 4244)
        return std::string(tz.begin(), tz.end());
    }

}  // namespace flutter_timezone

#endif  // FLUTTER_PLUGIN_FLUTTER_TIMEZONE_ICU_LOADER_H_

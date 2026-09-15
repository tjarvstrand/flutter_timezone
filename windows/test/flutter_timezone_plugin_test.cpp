#include <flutter/method_call.h>
#include <flutter/method_result_functions.h>
#include <flutter/standard_method_codec.h>
#include <gtest/gtest.h>
#include <windows.h>

#include <memory>
#include <string>
#include <variant>

#include "flutter_timezone_plugin.h"
#include "icu_loader.h"

namespace flutter_timezone {
    namespace test {

        namespace {
            using flutter::EncodableValue;
            using flutter::MethodCall;
            using flutter::MethodResultFunctions;

        }  // namespace

        static bool isNonEmptyString(const EncodableValue& value) {
            if (std::holds_alternative<std::string>(value)) {
                return !std::get<std::string>(value).empty();
            }
            return false;
        }

        TEST(FlutterTimezonePlugin, GetAvailableTimezones) {
            FlutterTimezonePlugin plugin;
            // Save the reply value from the success callback.
            std::vector<EncodableValue> resultVector;

            // Call the method and store the result in the result_vector.
            plugin.HandleMethodCall(
                MethodCall(kGetAvailableTimezones, std::make_unique<EncodableValue >()),
                std::make_unique<MethodResultFunctions<>>(
                    [&resultVector](const EncodableValue* result) {
                        resultVector = std::get<std::vector<EncodableValue>>(*result);
                    },
                    nullptr, nullptr)
            );

            // Since the exact count and values vary by host, just ensure that it's a list of non-empty strings
            EXPECT_GE(resultVector.size(), 1);
            for (const auto& value : resultVector) {
                EXPECT_TRUE(isNonEmptyString(value));
            }
        }

        TEST(FlutterTimezonePlugin, GetLocalTimezone) {
            FlutterTimezonePlugin plugin;
            // Save the reply value from the success callback.
            std::string resultString;

            // Call the method and store the result in the resultString.
            plugin.HandleMethodCall(
                MethodCall(kGetLocalTimezone, std::make_unique<EncodableValue>()),
                std::make_unique<MethodResultFunctions<>>(
                    [&resultString](const EncodableValue* result) {
                        resultString = std::get<std::string>(*result);
                    },
                    nullptr, nullptr));

            // Since the string varies by host, just ensure that it's a non-empty string
            EXPECT_GE(resultString.length(), 1);
        }

        // The tests below run on Windows 10 1903+, where icu.dll exists and the legacy icuin.dll /
        // icuuc.dll are kept as forwarders. Missing DLL names simulate older systems.
        constexpr auto kMissingDll = L"flutter_timezone_test_missing.dll";

        TEST(IcuLoader, ResolvesCombinedSystemIcu) {
            auto api = LoadIcuApi(kSystemIcuDlls);

            ASSERT_TRUE(api.IsAvailable());
            EXPECT_STREQ(api.source, L"icu.dll");
        }

        TEST(IcuLoader, FallsBackToLegacyIcuWhenCombinedDllIsMissing) {
            auto combined = LoadIcuApi(kSystemIcuDlls);
            auto legacy = LoadIcuApi(IcuDllNames{ kMissingDll, L"icuin.dll", L"icuuc.dll" });

            ASSERT_TRUE(legacy.IsAvailable());
            EXPECT_STREQ(legacy.source, L"icuin.dll");
            EXPECT_EQ(LocalTimezoneId(legacy), LocalTimezoneId(combined));
        }

        TEST(IcuLoader, ReportsUnavailableWithoutIcu) {
            auto api = LoadIcuApi(IcuDllNames{ kMissingDll, kMissingDll, kMissingDll });

            EXPECT_FALSE(api.IsAvailable());
            EXPECT_EQ(api.source, nullptr);
            EXPECT_EQ(LocalTimezoneId(api), std::nullopt);
        }
    }  // namespace test
}  // namespace flutter_timezone

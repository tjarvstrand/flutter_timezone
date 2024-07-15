# Runs the integration tests for this plugin on Windows.
#
# This script modifies the current system's time zone and region, and then runs
# `integration_test/local_timezone_test.dart` with the expected IANA time zone as a parameter.
#
# See https://learn.microsoft.com/en-us/windows/win32/intl/table-of-geographical-locations for the
# list of region integer codes.

$json = @"
[
    {
        "tz": "W. Europe Standard Time",
        "region": 14, // Austria
        "expected": "Europe/Vienna"
    },
    {
        "tz": "W. Europe Standard Time",
        "region": 223, // Switzerland
        "expected": "Europe/Zurich"
    },
    {
        "tz": "W. Europe Standard Time",
        "region": 244, // United States
        "expected": "Europe/Berlin"
    },
    {
        "tz": "Tokyo Standard Time",
        "region": 122,
        "expected": "Asia/Tokyo"
    }
]
"@;

$inputJson = ConvertFrom-Json $json;

foreach ($input in $inputJson) {
    Write-Output "tz: $($input.tz), region: $($input.region), expected: $($input.expected)";

    # set time zone
    tzutil /s "$($input.tz)"

    # set region
    Set-WinHomeLocation $input.region

    # test
    flutter test integration_test/local_timezone_test.dart -d windows --dart-define EXPECTED_TZ="$($input.expected)"
}

// swift-tools-version: 5.9
// The swift-tools-version declares the minimum version of Swift required to build this package.

import PackageDescription

let package = Package(
    name: "flutter_timezone",
    platforms: [
        .macOS("10.14")
    ],
    products: [
        .library(name: "flutter-timezone", targets: ["flutter_timezone"])
    ],
    dependencies: [],
    targets: [
        .target(
            name: "flutter_timezone",
            dependencies: [],
            resources: [
                .process("PrivacyInfo.xcprivacy")
            ],
            cSettings: [
                .headerSearchPath("include/flutter_timezone"),
            ]
        )
    ]
)
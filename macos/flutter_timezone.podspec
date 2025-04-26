#
# To learn more about a Podspec see http://guides.cocoapods.org/syntax/podspec.html.
# Run `pod lib lint flutter_timezone.podspec' to validate before publishing.
#
Pod::Spec.new do |s|
  s.name             = 'flutter_timezone'
  s.version          = '0.1.0'
  s.summary          = 'A new flutter plugin project.'
  s.description      = <<-DESC
A new flutter plugin project.
                       DESC
  s.homepage         = 'http://example.com'
  s.license          = { :file => '../LICENSE' }
  s.author           = { 'Your Company' => 'email@example.com' }
  s.source           = { :path => '.' }
  s.source_files = 'flutter_timezone/Sources/flutter_timezone/**/*.swift'
  s.resource_bundles = {'flutter_timezone_privacy' => ['flutter_timezone/Sources/flutter_timezone/PrivacyInfo.xcprivacy']}
  s.dependency 'FlutterMacOS'

  s.platform = :osx, '10.14'
  s.pod_target_xcconfig = { 'DEFINES_MODULE' => 'YES' }
  s.swift_version = '5.0'
end

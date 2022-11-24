package net.wolverinebeach.flutter_timezone

import android.os.Build
import androidx.annotation.NonNull
import io.flutter.embedding.engine.plugins.FlutterPlugin
import io.flutter.plugin.common.BinaryMessenger
import java.time.ZoneId
import io.flutter.plugin.common.MethodCall
import io.flutter.plugin.common.MethodChannel
import io.flutter.plugin.common.MethodChannel.MethodCallHandler
import io.flutter.plugin.common.MethodChannel.Result
import io.flutter.plugin.common.PluginRegistry.Registrar
import java.util.*
import kotlin.collections.ArrayList

class FlutterTimezonePlugin : FlutterPlugin, MethodCallHandler {

    private lateinit var channel: MethodChannel

    // backward compatibility with flutter api v1
    companion object {
        @JvmStatic
        fun registerWith(registrar: Registrar) {
            val plugin = FlutterTimezonePlugin()
            plugin.setupMethodChannel(registrar.messenger())
        }
    }

    override fun onAttachedToEngine(@NonNull binding: FlutterPlugin.FlutterPluginBinding) {
        setupMethodChannel(binding.binaryMessenger)
    }

    override fun onDetachedFromEngine(@NonNull binding: FlutterPlugin.FlutterPluginBinding) {
        channel.setMethodCallHandler(null)
    }

    override fun onMethodCall(call: MethodCall, result: Result) {
        when (call.method) {
            "getLocalTimezone" -> result.success(getLocalTimezone())

            "getAvailableTimezones" -> result.success(getAvailableTimezones())

            else -> result.notImplemented()
        }
    }

    private fun getLocalTimezone(): String {
        return ZoneId.systemDefault().id
    }

    private fun getAvailableTimezones(): List<String> {
        return ZoneId.getAvailableZoneIds().toCollection(ArrayList())
    }

    private fun setupMethodChannel(messenger: BinaryMessenger) {
        channel = MethodChannel(messenger, "flutter_timezone")
        channel.setMethodCallHandler(this)
    }
}

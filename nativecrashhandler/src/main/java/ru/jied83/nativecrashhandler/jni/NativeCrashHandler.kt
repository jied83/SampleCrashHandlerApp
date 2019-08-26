package ru.jied83.nativecrashhandler.jni

import android.content.Context
import com.getkeepsafe.relinker.ReLinker
import org.jetbrains.annotations.TestOnly
import ru.jied83.nativecrashhandler.BuildConfig
import java.util.concurrent.atomic.AtomicBoolean

class NativeCrashHandler(private val context: Context) {

    companion object {
        private const val LIB_NAME = "chandler"
    }

    private val isInitialized = AtomicBoolean(false)

    init {
        reload()
    }

    fun init() = native {
        if (isInitialized.compareAndSet(false, true)) {
            NativeCrashHandlerJni.init()
        }
    }

    @TestOnly
    fun testCrash() = native { NativeCrashHandlerJni.crash() }

    private fun reload() {
        ReLinker.recursively().loadLibrary(context, LIB_NAME, BuildConfig.LIB_VERSION_CHANDLER)
    }

    private inline fun <T> native(block: () -> T): T {
        return try {
            block()
        } catch (error: UnsatisfiedLinkError) {
            reload()
            block()
        }
    }
}
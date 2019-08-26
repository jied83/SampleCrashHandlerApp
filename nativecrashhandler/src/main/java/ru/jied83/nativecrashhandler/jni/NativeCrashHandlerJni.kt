package ru.jied83.nativecrashhandler.jni

object NativeCrashHandlerJni {
    external fun init(): Int
    external fun crash()
}


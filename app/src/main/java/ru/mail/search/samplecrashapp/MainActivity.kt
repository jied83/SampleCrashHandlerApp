package ru.mail.search.samplecrashapp

import android.content.Context
import android.os.Bundle
import android.support.v7.app.AppCompatActivity
import android.util.AttributeSet
import android.view.View
import ru.jied83.nativecrashhandler.jni.NativeCrashHandler

class MainActivity : AppCompatActivity() {
    val handler = NativeCrashHandler(this)
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)
        handler.init()
    }

    override fun onCreateView(name: String?, context: Context?, attrs: AttributeSet?): View? {
        handler.testCrash()
        return super.onCreateView(name, context, attrs)
    }
}

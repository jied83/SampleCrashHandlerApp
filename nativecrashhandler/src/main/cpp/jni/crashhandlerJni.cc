#include <jni.h>
#include <linux/handler/minidump_descriptor.h>
#include <linux/handler/exception_handler.h>

namespace {
    typedef struct tick_context {
        JavaVM *javaVM;
        jclass jniHelperClz;
        jobject jniHelperObj;
    } CallbackContxt;

    CallbackContxt ctx;

    void throwJavaException(JNIEnv *env) {
        jclass c = env->FindClass("java/lang/NullPointerException");
        env->ThrowNew(c, "native crash BUMPS!!!!!");
    }

    void Crash() {
        volatile int *a = reinterpret_cast<volatile int *>(NULL);
        *a = 1;
    }

    bool DumpCallback(const google_breakpad::MinidumpDescriptor &descriptor,
                      void *context,
                      bool succeeded) {
        printf("Dump path: %s\n", descriptor.path());
        JNIEnv *env;
        ctx.javaVM->GetEnv((void **) &env, JNI_VERSION_1_6);
        ctx.javaVM->AttachCurrentThread(&env, NULL);
        throwJavaException(env);
        return succeeded;
    }

    extern "C"
    JNIEXPORT jint JNICALL
    Java_ru_jied83_nativecrashhandler_jni_NativeCrashHandlerJni_init(JNIEnv *env,
                                                                     jobject obj /* this */) {
        google_breakpad::MinidumpDescriptor descriptor(".");
        static google_breakpad::ExceptionHandler eh(descriptor, NULL, DumpCallback, NULL, true, -1);
        return 0;
    }

    JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM *vm, void *reserved) {
        memset(&ctx, 0, sizeof(ctx));
        ctx.javaVM = vm;
        return JNI_VERSION_1_6;
    }


    extern "C"
    JNIEXPORT void JNICALL
    Java_ru_jied83_nativecrashhandler_jni_NativeCrashHandlerJni_crash(JNIEnv *env,
                                                                      jobject obj /* this */) {
        Crash();
    }
}

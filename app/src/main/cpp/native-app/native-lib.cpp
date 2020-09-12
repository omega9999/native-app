#include <jni.h>
#include <string>
#include <vector>
#include <map>
#include <functional>
#include <unistd.h>

#include "prime/PrimeNumber.h"
#include "log/Log.h"
#include "timer/Later.h"
#include "native-lib.h"
#include "manager/NativeManager.h"


static JavaVM *gJavaVM = nullptr;
static jclass globalClazz;

const char *packageClassStr = "com/example/android/nativeapp/NativeManager";
const char *methodNameStr = "callBack";
const char *methodParamsStr = "(Ljava/lang/String;Ljava/lang/String;)V";



JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM *jvm, void *reserved) {
    JNIEnv *env = nullptr;
    gJavaVM = jvm;

    LOGV("JNI_OnLoad is Main Thread ? %s", getpid() == gettid() ? "true" : "false");

    LOGV("isPrime verbose, Address of x is %p", (void *) &jvm);
    LOGD("isPrime debug %d", 3);
    LOGI("isPrime info %s, %s", "prova 1", "prova 2");
    LOGW("isPrime warn");
    LOGE("isPrime error");
    LOGF("isPrime fatal");

    LOGV("JNI_OnLoad called");
    jint returnCode = jvm->GetEnv((void **) &env, JNI_VERSION_1_6);
    if (returnCode != JNI_OK) {
        LOGE("Failed to get the environment using GetEnv(), received %d", returnCode);
        return JNI_ERR;
    }
    LOGV("find class %s", packageClassStr);
    jclass localClass = env->FindClass(packageClassStr);
    if (env->ExceptionCheck()) {
        LOGE("initClassHelper: failed to get %s class reference", packageClassStr);
        return JNI_ERR;
    }
    globalClazz = (jclass) env->NewGlobalRef(localClass);
    if (globalClazz == nullptr) {
        LOGE("initClassHelper: %s class reference is null", packageClassStr);
        return JNI_ERR;
    }
    return JNI_VERSION_1_6;
}

JNIEXPORT void JNICALL JNI_OnUnload(JavaVM *jvm, void *reserved) {
    LOGV("JNI_OnUnload called");
    LOGV("JNI_OnUnload is Main Thread ? %s", getpid() == gettid() ? "true" : "false");
    JNIEnv *env = nullptr;
    jint returnCode = jvm->GetEnv((void **) &env, JNI_VERSION_1_6);
    if (returnCode != JNI_OK) {
        LOGE("Failed to get the environment using GetEnv(), received %d", returnCode);
        return;
    }
    LOGV("delete global ref %p", globalClazz);
    env->DeleteGlobalRef(globalClazz);
}


JNIEXPORT jstring JNICALL
Java_com_example_android_nativeapp_NativeManager_stringFromJNI(JNIEnv *env, jobject thiz) {
    std::string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}

JNIEXPORT jstring JNICALL
Java_com_example_android_nativeapp_NativeManager_stringNumber(JNIEnv *env, jobject thiz) {
    std::string hello = "2003";
    return env->NewStringUTF(hello.c_str());
}

JNIEXPORT jboolean JNICALL
Java_com_example_android_nativeapp_NativeManager_isPrime(JNIEnv *env, jobject thiz, jint num) {
    auto primeNumber = new PrimeNumber(num);
    return static_cast<jboolean>(primeNumber->isPrime());
}


JNIEXPORT jint JNICALL
Java_com_example_android_nativeapp_NativeManager_numberOfObjects(JNIEnv *env, jobject thiz) {
    return 4;
}

JNIEXPORT jlong JNICALL
Java_com_example_android_nativeapp_NativeManager_createNativeObject(JNIEnv *env, jclass clazz,
                                                                    jint number) {
    auto *pointer = new PrimeNumber(number);
    if (!pointer) {
        //jniThrowRuntimeException(env, "Unable to allocate native PrimeNumber");
        return 0;
    }
    //pointer->incStrong(env);
    return reinterpret_cast<jlong>(pointer);
}

JNIEXPORT void JNICALL
Java_com_example_android_nativeapp_NativeManager_destroyNativeObject(JNIEnv *env, jclass clazz,
                                                                     jlong reference) {
    auto *pointer = reinterpret_cast<PrimeNumber *>(reference);
    //pointer->~PrimeNumber();
    delete pointer;
}

JNIEXPORT void JNICALL
Java_com_example_android_nativeapp_NativeManager_logNativeObject(JNIEnv *env, jclass clazz,
                                                                 jlong reference) {
    auto *pointer = reinterpret_cast<PrimeNumber *>(reference);
    LOGV("%d is isPrime? %s", pointer->GetNumber(), pointer->isPrime() ? "true" : "false");
}


JNIEXPORT jlong JNICALL
Java_com_example_android_nativeapp_NativeManager_getSize(JNIEnv *env, jobject thiz,
                                                         jobject object) {
    //LOGV("Size of java object with address %p", (void *) &object);
    return sizeof(object);// size of reference, not size of object

    /*
    jlong objectSize;
    globalJVMTIInterface->GetObjectSize(globalJVMTIInterface, object, &objectSize);
    return objectSize;
    */
}

void callBack(std::string identifier, std::string msg) {
    LOGV("Start native callback");
    if (gJavaVM == nullptr) {
        LOGI("VciCallback Error() %p", gJavaVM);
        return;
    }

    int status;
    JNIEnv *env = nullptr;

    bool isAttached = false;
    status = gJavaVM->GetEnv((void **) &env, JNI_VERSION_1_6);
    if (status < 0 || env == nullptr) {
        LOGW("failed to get JNI environment, assuming native thread %d %p", status, env);
        status = gJavaVM->AttachCurrentThread(&env, nullptr);
        if (status < 0) {
            LOGE("failed to attach current thread %d", status);
            return;
        }

        isAttached = true;
    }
    LOGV("Convert string to jstring");
    jstring jmsg = env->NewStringUTF(msg.c_str());
    jstring jidentifier = env->NewStringUTF(identifier.c_str());

    LOGV("find method %s %s", methodNameStr, methodParamsStr);
    jmethodID method = env->GetStaticMethodID(globalClazz, methodNameStr, methodParamsStr);
    LOGV("Call java method %p %p", globalClazz, method);
    env->CallStaticVoidMethod(globalClazz, method, jidentifier, jmsg);
    if (env->ExceptionCheck()) {
        LOGE("Failed to call Java method");
        env->ExceptionClear();
    }

    env->DeleteLocalRef(jmsg);
    env->DeleteLocalRef(jidentifier);

    if (isAttached) {
        gJavaVM->DetachCurrentThread();
    }
}


JNIEXPORT void JNICALL
Java_com_example_android_nativeapp_NativeManager_initObject(JNIEnv *env, jobject thiz,
                                                            jstring identifier) {
    auto *manager = new NativeManager(env->GetStringUTFChars(identifier, nullptr));
    manager->setNativeObject(new PrimeNumber(123));
}

JNIEXPORT void JNICALL
Java_com_example_android_nativeapp_NativeManager_destroyObject(JNIEnv *env, jobject thiz,
                                                               jstring identifier) {
    LOGV("call NativeManager::Destroy");
    NativeManager::Destroy(env->GetStringUTFChars(identifier, nullptr));
}

JNIEXPORT void JNICALL
Java_com_example_android_nativeapp_NativeManager_startTimer(JNIEnv *env, jclass clazz,
                                                            jstring identifier, jlong time_millis,
                                                            jstring msg, jboolean async) {
    std::string stringa(env->GetStringUTFChars(msg, nullptr));
    Later later_test(time_millis, async, &callBack, env->GetStringUTFChars(identifier, nullptr),
                     std::string("native message timer callback ") + stringa);
}
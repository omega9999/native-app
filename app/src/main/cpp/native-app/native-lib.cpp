#include <jni.h>
#include <string>
#include "prime/PrimeNumber.h"
#include "log/Log.h"
#include "callback/ObserverChain.h"

extern "C"
JNIEXPORT jstring JNICALL Java_com_example_android_nativeapp_NativeManager_stringFromJNI(
        JNIEnv* env,
        jobject /* this */) {
    std::string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}

extern "C"
JNIEXPORT jstring JNICALL Java_com_example_android_nativeapp_NativeManager_stringNumber(
        JNIEnv* env,
        jobject /* this */) {
    std::string hello = "2003";
    return env->NewStringUTF(hello.c_str());
}

extern "C"
JNIEXPORT jboolean JNICALL Java_com_example_android_nativeapp_NativeManager_isPrime(JNIEnv *env, jobject, jint num) {
    PrimeNumber primeNumber(num);
    LOGV( "isPrime verbose, Address of x is %p", (void *)&primeNumber);
    LOGD( "isPrime debug %d",3);
    LOGI( "isPrime info %s, %s","prova 1","prova 2");
    LOGW( "isPrime warn");
    LOGE( "isPrime error");
    LOGF( "isPrime fatal");

    Log::v( "native","A isPrime verbose");
    Log::d( "native","A isPrime debug");
    Log::i( "native","A isPrime info");
    Log::w( "native","A isPrime warn");
    Log::e( "native","A isPrime error");
    Log::f( "native","A isPrime fatal");
    return static_cast<jboolean>(primeNumber.isPrime());
}

static JavaVM *jvm = NULL;

//std::vector<ObserverChain *> store_Wlistener_vector;
JNIEnv *store_env;

extern "C"
JNIEXPORT void JNICALL
Java_com_texa_nativeapp_NativeManager_subscribeListener(JNIEnv *env, jobject instance,
                                                        jobject listener) {
    env->GetJavaVM(&jvm); //store jvm reference for later call
    store_env = env;

    jweak store_Wlistener = env->NewWeakGlobalRef(listener);
    jclass clazz = env->GetObjectClass(store_Wlistener);

    jmethodID store_method = env->GetMethodID(clazz, "onAcceptMessage", "(Ljava/lang/String;)V");
    jmethodID store_methodVAL = env->GetMethodID(clazz, "onAcceptMessageVal", "(I)V");

    ObserverChain *tmpt = new ObserverChain(store_Wlistener, store_method, store_methodVAL);

    //store_Wlistener_vector.push_back(tmpt);


    Log::v( "GetEnv:", " Subscribe to Listener  OK \n");
    if (NULL == store_method) return;

}
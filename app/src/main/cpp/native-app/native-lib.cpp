// #include <jvmti.h>
#include <jni.h>
#include <string>
#include "prime/PrimeNumber.h"
#include "log/Log.h"
#include "callback/ObserverChain.h"

static JavaVM * gJavaVM = nullptr;
// static jvmtiEnv *globalJVMTIInterface = nullptr;

/*
JNIEXPORT jint JNICALL Agent_OnLoad(JavaVM * jvm, char *options, void *reserved)
{
    jint returnCode = jvm->GetEnv( (void **) &globalJVMTIInterface, JVMTI_VERSION_1_0);
    if (returnCode != JNI_OK)
    {
        LOGE("The version of JVMTI requested (1.0) is not supported by this JVM");
        return JVMTI_ERROR_UNSUPPORTED_VERSION;
    }

    return JVMTI_ERROR_NONE;
}

JNIEXPORT void JNICALL Agent_OnUnload(JavaVM * jvm)
{

}
*/

JNIEXPORT jint JNICALL JNI_OnLoad( JavaVM * jvm, void * reserved )
{
    JNIEnv * env = nullptr;
    gJavaVM = jvm;

    LOGV("JNI_OnLoad is Main Thread ? %s",getpid() == gettid() ? "true" : "false");

    LOGV("isPrime verbose, Address of x is %p", (void *) &jvm);
    LOGD("isPrime debug %d", 3);
    LOGI("isPrime info %s, %s", "prova 1", "prova 2");
    LOGW("isPrime warn");
    LOGE("isPrime error");
    LOGF("isPrime fatal");

    Log::v("native", "A isPrime verbose");
    Log::d("native", "A isPrime debug");
    Log::i("native", "A isPrime info");
    Log::w("native", "A isPrime warn");
    Log::e("native", "A isPrime error");
    Log::f("native", "A isPrime fatal");


    LOGV( "JNI_OnLoad called" );
    jint returnCode = jvm->GetEnv( ( void * * ) & env, JNI_VERSION_1_6 );
    if ( returnCode != JNI_OK )
    {
        LOGE( "Failed to get the environment using GetEnv(), received %d", returnCode );
        return JNI_ERR;
    }
    return JNI_VERSION_1_6;
}

JNIEXPORT void JNICALL JNI_OnUnload( JavaVM * jvm, void * reserved ) {
    LOGV( "JNI_OnUnload called" );
}


extern "C"
JNIEXPORT jstring JNICALL
Java_com_example_android_nativeapp_NativeManager_stringFromJNI(JNIEnv *env, jobject thiz) {
    std::string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}

extern "C"
JNIEXPORT jstring JNICALL
Java_com_example_android_nativeapp_NativeManager_stringNumber(JNIEnv *env, jobject thiz) {
    std::string hello = "2003";
    return env->NewStringUTF(hello.c_str());
}

extern "C"
JNIEXPORT jboolean JNICALL
Java_com_example_android_nativeapp_NativeManager_isPrime(JNIEnv *env, jobject thiz, jint num) {
    PrimeNumber primeNumber(num);
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


    Log::v("GetEnv:", " Subscribe to Listener  OK \n");
    if (NULL == store_method) return;

}extern "C"
JNIEXPORT jint JNICALL
Java_com_example_android_nativeapp_NativeManager_numberOfObjects(JNIEnv *env, jobject thiz) {
    return 10;
}

extern "C"
JNIEXPORT jlong JNICALL
Java_com_example_android_nativeapp_NativeManager_createNativeObject(JNIEnv *env, jclass clazz, jint number) {
    PrimeNumber* pointer = new PrimeNumber(number);
    if (!pointer) {
        //jniThrowRuntimeException(env, "Unable to allocate native PrimeNumber");
        return 0;
    }
    //pointer->incStrong(env);
    return reinterpret_cast<jlong>(pointer);
}

extern "C"
JNIEXPORT void JNICALL
Java_com_example_android_nativeapp_NativeManager_destroyNativeObject(JNIEnv *env, jclass clazz, jlong reference) {
    PrimeNumber *pointer = reinterpret_cast<PrimeNumber *>(reference);
    //pointer->~PrimeNumber();
    delete pointer;
}
extern "C"
JNIEXPORT void JNICALL
Java_com_example_android_nativeapp_NativeManager_logNativeObject(JNIEnv *env, jclass clazz, jlong reference) {
    PrimeNumber *pointer = reinterpret_cast<PrimeNumber *>(reference);
    LOGV("%d is isPrime? %s", pointer->GetNumber(), pointer->isPrime() ? "true" : "false");
}


/*
extern "C"
JNIEXPORT jlong JNICALL
Java_com_example_android_nativeapp_NativeManager_getSize(JNIEnv *env, jobject thiz, jobject o) {
    return sizeof(o);
}
*/

extern "C"
JNIEXPORT jlong JNICALL
Java_com_example_android_nativeapp_NativeManager_getSize(JNIEnv *env, jobject thiz, jobject object) {
    //LOGV("Size of java object with address %p", (void *) &object);
    return sizeof(object);// size of reference, not size of object

    /*
    jlong objectSize;
    globalJVMTIInterface->GetObjectSize(globalJVMTIInterface, object, &objectSize);
    return objectSize;
    */
}




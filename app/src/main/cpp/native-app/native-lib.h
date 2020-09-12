#include <jni.h>

#ifndef _Included_NATIVE_LIB
#define _Included_NATIVE_LIB
#ifdef __cplusplus
extern "C" {
#endif

JNIEXPORT jstring JNICALL
Java_com_example_android_nativeapp_NativeManager_stringFromJNI(JNIEnv *env, jobject thiz);

JNIEXPORT jstring JNICALL
Java_com_example_android_nativeapp_NativeManager_stringNumber(JNIEnv *env, jobject thiz);

JNIEXPORT jboolean JNICALL
Java_com_example_android_nativeapp_NativeManager_isPrime(JNIEnv *env, jobject thiz, jint num);

JNIEXPORT jint JNICALL
Java_com_example_android_nativeapp_NativeManager_numberOfObjects(JNIEnv *env, jobject thiz);

JNIEXPORT jlong JNICALL
Java_com_example_android_nativeapp_NativeManager_createNativeObject(JNIEnv *env, jclass clazz,
                                                                    jint number);

JNIEXPORT void JNICALL
Java_com_example_android_nativeapp_NativeManager_destroyNativeObject(JNIEnv *env, jclass clazz,
                                                                     jlong reference);

JNIEXPORT void JNICALL
Java_com_example_android_nativeapp_NativeManager_logNativeObject(JNIEnv *env, jclass clazz,
                                                                 jlong reference);

JNIEXPORT jlong JNICALL
Java_com_example_android_nativeapp_NativeManager_getSize(JNIEnv *env, jobject thiz, jobject object);

JNIEXPORT void JNICALL
Java_com_example_android_nativeapp_NativeManager_initObject(JNIEnv *env, jobject thiz,
                                                            jstring identifier);

JNIEXPORT void JNICALL
Java_com_example_android_nativeapp_NativeManager_destroyObject(JNIEnv *env, jobject thiz,
                                                               jstring identifier);

JNIEXPORT void JNICALL
Java_com_example_android_nativeapp_NativeManager_startTimer(JNIEnv *env, jclass clazz,
                                                            jstring identifier, jlong time_millis,
                                                            jstring msg, jboolean async);

#ifdef __cplusplus
}
#endif
#endif

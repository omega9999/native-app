#pragma once
#include <android/log.h>
#include <iostream>
#include <stdio.h>      /* printf */
#include <stdarg.h>     /* va_list, va_start, va_arg, va_end */

using namespace std;

class Log {
public:
    static void v(std::string tag, std::string text);
    static void d(std::string tag, std::string text);
    static void i(std::string tag, std::string text);
    static void w(std::string tag, std::string text);
    static void e(std::string tag, std::string text);
    static void f(std::string tag, std::string text);
};

#define LOG_TAG_PREFIX "c++: "
#define __FILENAME__ (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)
#define  LOG_TAG   /* LOG_TAG_PREFIX */ __FILENAME__
#define  LOGV(...)  __android_log_print(ANDROID_LOG_VERBOSE, LOG_TAG, __VA_ARGS__)
#define  LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)
#define  LOGI(...)  __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)
#define  LOGW(...)  __android_log_print(ANDROID_LOG_WARN, LOG_TAG, __VA_ARGS__)
#define  LOGE(...)  __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)
#define  LOGF(...)  __android_log_print(ANDROID_LOG_FATAL, LOG_TAG, __VA_ARGS__)


/*
#pragma once

#ifdef ANDROID

#include <android/log.h>

#define  LOG_TAG    "diaengine_jni"

void LogD( const char * pFormat, ... );
void LogI( const char * pFormat, ... );
void LogE( const char * pFormat, ... );

#define  LOGD(...)  LogD(__VA_ARGS__)
#define  LOGI(...)  LogI(__VA_ARGS__)
#define  LOGE(...)  LogE(__VA_ARGS__)


#define  LOGAD(...)  __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)
#define  LOGAI(...)  __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)
#define  LOGAE(...)  __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)

#else

#include <stdio.h>

#define  LOGD(...)  printf(__VA_ARGS__)
#define  LOGI(...)  printf(__VA_ARGS__)
#define  LOGE(...)  printf(__VA_ARGS__)

#endif


 */


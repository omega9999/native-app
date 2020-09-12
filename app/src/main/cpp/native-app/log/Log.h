#pragma once

#include <android/log.h>
#include <string>
#include <unistd.h>

using namespace std;


// predefined macros: https://en.cppreference.com/w/cpp/preprocessor/replace

#define __FILENAME__ (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)
#define __FILENAME_NO_EXT__ (strrchr(__FILENAME__, '.') ? strrchr(__FILENAME__, '.') + 1 : __FILENAME__)
#define _FILE_NAME_S strcat(strcpy(new char[strlen(__FILENAME__) + strlen(" ") + 1],__FILENAME__)," ")
#define _FILE_NAME_ strcat(strcpy(new char[strlen(_FILE_NAME_S) + strlen(__func__) + 1],_FILE_NAME_S),__func__)
#define LOG_TAG_PREFIX    "c++_jni: "
#define LOG_TAG_THREAD    getpid() == gettid() ? " [M] " : " [w] "
#define LOG_TAG_SUFFIX  strcat(strcpy(new char[strlen(_FILE_NAME_) + strlen(LOG_TAG_THREAD) + 1],_FILE_NAME_),LOG_TAG_THREAD)
#define LOG_TAG  strcat(strcpy(new char[strlen(LOG_TAG_PREFIX) + strlen(LOG_TAG_SUFFIX) + 1],LOG_TAG_PREFIX),LOG_TAG_SUFFIX)




#define LOGV(...)  __android_log_print(ANDROID_LOG_VERBOSE, LOG_TAG, __VA_ARGS__)
#define LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)
#define LOGI(...)  __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)
#define LOGW(...)  __android_log_print(ANDROID_LOG_WARN, LOG_TAG, __VA_ARGS__)
#define LOGE(...)  __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)
#define LOGF(...)  __android_log_print(ANDROID_LOG_FATAL, LOG_TAG, __VA_ARGS__)


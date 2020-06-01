#include "Log.h"

void Log::v(std::string tag, std::string text ) {
    __android_log_print(ANDROID_LOG_VERBOSE, tag.c_str(), "%s\n", text.c_str());
}
void Log::d(std::string tag, std::string text ) {
    __android_log_print(ANDROID_LOG_DEBUG, tag.c_str(), "%s\n", text.c_str());
}
void Log::i(std::string tag, std::string text ) {
    __android_log_print(ANDROID_LOG_INFO, tag.c_str(), "%s\n", text.c_str());
}
void Log::w(std::string tag, std::string text ) {
    __android_log_print(ANDROID_LOG_WARN, tag.c_str(), "%s\n", text.c_str());
}
void Log::e(std::string tag, std::string text ) {
    __android_log_print(ANDROID_LOG_ERROR, tag.c_str(), "%s\n", text.c_str());
}
void Log::f(std::string tag, std::string text ) {
    __android_log_print(ANDROID_LOG_FATAL, tag.c_str(), "%s\n", text.c_str());
}


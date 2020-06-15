NativeApp


http://www.cplusplus.com/reference/clibrary/

https://developer.android.com/training/articles/perf-jni#java

https://github.com/zjw-swun/JVMTI_Demo

https://github.com/odnoklassniki/jvmti-tools


//check main thread java
Log.v(TAG, "is Main Thread ? %1$s",(Looper.myLooper() == Looper.getMainLooper()));

//check main thread c++
#include <unistd.h>
LOGV("is Main Thread ? %s",getpid() == gettid() ? "true" : "false");

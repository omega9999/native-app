NativeApp



c++: looper e funzioni lambda
https://www.codeproject.com/Articles/1169105/Cplusplus-std-thread-Event-Loop-with-Message-Queue
https://docs.microsoft.com/it-it/cpp/cpp/lambda-expressions-in-cpp?view=vs-2019



http://www.cplusplus.com/reference/clibrary/

https://developer.android.com/training/articles/perf-jni#java

https://github.com/zjw-swun/JVMTI_Demo

https://github.com/odnoklassniki/jvmti-tools


//check main thread java
Log.v(TAG, "is Main Thread ? %1$s",(Looper.myLooper() == Looper.getMainLooper()));

//check main thread c++
#include <unistd.h>
LOGV("is Main Thread ? %s",getpid() == gettid() ? "true" : "false");

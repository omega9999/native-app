#include <jni.h>

class ObserverChain {
public:
    ObserverChain(jweak pJobject, jmethodID pID, jmethodID pJmethodID);

    jweak store_Wlistener = NULL;
    jmethodID store_method = NULL;
    jmethodID store_methodVAL = NULL;

};

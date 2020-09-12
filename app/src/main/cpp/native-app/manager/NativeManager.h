#pragma once
#include <string>
#include <vector>
#include <map>
#include <functional>
#include <unistd.h>

#include "../utils/Utils.h"
#include "../log/Log.h"

using namespace std;

class NativeManager;
static std::map<std::string, NativeManager *> DEFINITION_MAP;

class NativeManager {

public:
    NativeManager(std::string identifier);

    ~NativeManager();


    NativeObject *getNativeObject() const {
        return _nativeObject;
    }

    void setNativeObject(NativeObject *nativeObject) {
        _nativeObject = nativeObject;
    }

    static void Destroy(std::string identifier) {
        auto it = DEFINITION_MAP.find(identifier);
        if (it != DEFINITION_MAP.end()) {
            NativeManager *manager = it->second;
            if (manager != nullptr) {
                manager->~NativeManager();
            }
        }
    }

private:
    std::string _identifier;
    NativeObject *_nativeObject;

};



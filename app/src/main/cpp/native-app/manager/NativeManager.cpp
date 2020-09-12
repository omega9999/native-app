#include "NativeManager.h"
#include <utility>


NativeManager::NativeManager(std::string identifier) {
    _identifier = std::move(identifier);
    _nativeObject = nullptr;
    DEFINITION_MAP.insert(std::make_pair(_identifier, this));
}

NativeManager::~NativeManager() {
    DEFINITION_MAP.erase(this->_identifier);
    if (_nativeObject != nullptr) {
        LOGV("_nativeObject->destroy()");
        _nativeObject->destroy();
    }
}


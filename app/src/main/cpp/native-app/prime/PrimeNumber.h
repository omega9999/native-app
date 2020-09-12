#include <iostream>
#include "../utils/Utils.h"
#include "../log/Log.h"

using namespace std;
class PrimeNumber : public NativeObject {
    int _number;
public:
    PrimeNumber(int x);
    ~PrimeNumber();
    int GetNumber();
    bool isPrime();

    void destroy() {
        delete this;
    }
};
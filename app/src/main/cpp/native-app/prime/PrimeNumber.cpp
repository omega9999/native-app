#include "PrimeNumber.h"
#include "../log/Log.h"

PrimeNumber::PrimeNumber(int num) {
    LOGV("PrimeNumber constructor of %d", num);
    _number = num;
}
PrimeNumber::~PrimeNumber() {
    LOGV("PrimeNumber destructor of %d", _number);
}

bool PrimeNumber::isPrime() {
    //LOGV("isPrime into function %s","prova");
    bool isPrime = true;
    for (int i = 2; i <= _number / 2; i++) {
        if (_number % i == 0) {
            return false;
        } else {
            isPrime = true;
        }
    }
    return isPrime;
}

int PrimeNumber::GetNumber() {
    return _number;
}


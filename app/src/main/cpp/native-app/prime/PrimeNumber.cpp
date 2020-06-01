#include "PrimeNumber.h"
#include "../log/Log.h"

PrimeNumber::PrimeNumber(int num) {
    PrimeNumber::number = num;
}
bool PrimeNumber::isPrime() {
    LOGV("isPrime into function %s","prova");
    bool isPrime = true;
    for (int i = 2; i <= number / 2; i++) {
        if (number % i == 0) {
            return false;
        } else {
            isPrime = true;
        }
    }
    return isPrime;
}
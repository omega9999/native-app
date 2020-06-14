#include<iostream>
using namespace std;
class PrimeNumber {
    int _number;
public:
    PrimeNumber(int x);
    ~PrimeNumber();
    int GetNumber();
    bool isPrime();
};
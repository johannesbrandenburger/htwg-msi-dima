#include <openssl/sha.h>
#include <string>
#include <array>
#include <iostream>
#include <assert.h>
#include <list>
#include <vector>
#include <cmath>

using namespace std;

/*
 * Modular exponentiation
 * @param b base
 * @param n exponent
 * @param m modulus
 * @returns x = b^n mod m
*/
long long modexp(long long b, long long n, long long m) {
    long long result = 1;
    while (n > 0) {
        if (n % 2 == 1) {
            result = (result * b) % m;
        }
        n = n >> 1;
        b = (b * b) % m;
    }
    return result;
}

int main() {

    cout << "5^99 mod 11 = " << modexp(5, 99, 11) << endl;
    cout << "50^529 mod 13 = " << modexp(50, 529, 13) << endl;
    cout << "50^999 mod 17 = " << modexp(50, 999, 17) << endl;

    assert(modexp(5, 99, 11) == 9);
    assert(modexp(50, 529, 13) == 11);
    assert(modexp(50, 999, 17) == 16);

    // measure time between own implementation and built-in function
    int start = 0;
    int end = 0;
    int base = 50;
    int exponent = 11;
    int modulus = 17;
    float timeForOwnImplementation = 0;
    float timeForBuiltInFunction = 0;
    long long iterations = 100000000;
    long long power = 0;
    long long builtInResult = 0;
    long long ownResult = 0;

    start = clock();
    for (int i = 0; i < iterations; i++) {
        ownResult = modexp(base, exponent, modulus);
    }
    end = clock();
    timeForOwnImplementation = ((float)(end - start)) / CLOCKS_PER_SEC;
    cout << "Time for own implementation: " << timeForOwnImplementation << endl;
    cout << "Own result: " << ownResult << endl;

    start = clock();
    for (int i = 0; i < iterations; i++) {
        power = pow(base, exponent);
        builtInResult = power % modulus;
    }
    end = clock();
    timeForBuiltInFunction = ((float)(end - start)) / CLOCKS_PER_SEC;
    cout << "Time for built-in function: " << timeForBuiltInFunction << endl;
    cout << "Builtin result: " << builtInResult << endl;
    assert(ownResult == builtInResult);
    float factorToGetNanoSecondsPerIteration = 1000000000 / iterations;
    float difference = (timeForBuiltInFunction - timeForOwnImplementation) * factorToGetNanoSecondsPerIteration;
    float timeSavedInPercent = ((timeForBuiltInFunction - timeForOwnImplementation) / timeForBuiltInFunction) * 100;
    cout << "Own algo faster than built-in function in ns: " << difference << endl;
    cout << "Time saved in %: " << timeSavedInPercent << endl;

    return 0;


}
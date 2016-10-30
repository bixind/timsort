#include <iostream>
#include <iterator>
#include <vector>
#include <cstdlib>
#include <algorithm>
#include <ctime>
#include <cassert>
#include "timsort.h"
#include "tests.h"

using std::cout;
using std::endl;

bool comp(int a, int b) {
    return a < b;
}

int main() {
    srand(123);
//    cout << "C arrays and built-in comparator testing: ";
//    cout << statusAlert(testCArrays(100)) << ", ";
//    cout << statusAlert(testCArrays(1000)) << ", ";
//    cout << statusAlert(testCArrays(10000)) << ", ";
//    cout << statusAlert(testCArrays(100000)) << endl;
//    cout << "--------------------------------------------\n";
//    cout << "Random tests comparation:\n";
//    timeTestRandom(30);
//    timeTestRandom(40);
//    timeTestRandom(50);
//    timeTestRandom(1000);
//    timeTestRandom(10000);
//    timeTestRandom(100000);
//    timeTestRandom(1000000);
//    cout << "--------------------------------------------\n";
//    cout << "Partially sorted tests comparations:\n";
//    std::vector<size_t> length = {20, 40, 80, 128, 1024};
//    std::vector<size_t> count = {2, 4, 10, 100, 1000, 10000};
//    for (size_t i : length)
//        for (size_t j : count)
//            timeTestPartiallySorted(i, j);
//    cout << "--------------------------------------------\n";
//    cout << "Points with compare function:\n";
//    cout << statusAlert(testStructComparation(10)) << ", ";
//    cout << statusAlert(testStructComparation(100)) << ", ";
//    cout << statusAlert(testStructComparation(1000)) << ", ";
//    cout << statusAlert(testStructComparation(10000)) << ", ";
//    cout << statusAlert(testStructComparation(100000)) << endl;
//    cout << "Strings with functor:\n";
//    cout << statusAlert(testStringComparation(10, 10)) << ", ";
//    cout << statusAlert(testStringComparation(100, 100)) << ", ";
//    cout << statusAlert(testStringComparation(1000, 1000)) << ", ";
//    cout << statusAlert(testStringComparation(100, 10000)) << ", ";
//    cout << statusAlert(testStringComparation(10000, 100)) << endl;
//    cout << "--------------------------------------------\n";
    cout << "Parameters tests:\n" << endl;
    std::vector<IParameters*> params(10);
    params[0] = nullptr;
    cout << "minRun size:\n";
    for (size_t i = 1; i < 10; ++i) {
        params[i] = new TestParameters(i * 10, 7);
    }
    for (size_t i = 10; i < 10000000; i *= 10)
        parametersTesting(params, i);
    cout << "Gallop trigger\n";
    for (size_t i = 1; i < 10; ++i) {
        params[i] = new TestParameters(32, i);
    }
    for (size_t i = 10; i < 10000000; i *= 10)
        parametersTesting(params, i);
    return 0;
}
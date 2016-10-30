#ifndef TIMSORT_TESTS_H
#define TIMSORT_TESTS_H

#include "timsort.h"
#include <vector>
#include <ctime>

long long elapsed() {
    static long long t;
    long long d, t1 = clock();
    d = t1 - t;
    t = t1;
    return d;
}

std::string statusAlert(bool status) {
    if (status)
        return "OK";
    else
        return "FAILED";
}

bool testCArrays(size_t n = 1000) {
    int *arr = new int[n];
    int *control = new int[n];
    for (size_t i = 0; i < n; ++i)
        arr[i] = control[i] = rand();
    std::sort(control, control + n);
    TimSort(arr, arr + n);
    bool fl = true;
    for (size_t i = 0; i < n; ++i)
        fl &= (arr[i] == control[i]);
    return fl;
}

template <class T, class Comparator>
void timeTest(std::vector<T> v, Comparator comp) {
    std::vector<int> v1 = v;
    elapsed();
    std::sort(v.begin(), v.end(), comp);
    std::cout << "STL sort: " << elapsed() << std::endl;
    TimSort(v1.begin(), v1.end(), comp);
    std::cout << "TimSort: " << elapsed() << std::endl;
    std::cout << "Status: " << statusAlert(v1 == v) << std::endl;
    for (size_t i = 0; i < v.size(); ++i)
        if (v[i] != v1[i]) {
            std::cout << i << std::endl;
            break;
        }
    std::cout << std::endl;
}

template <class T>
void timeTest(std::vector<T> v) {
    class Comparator {
    public:
        bool operator()(const T &a, const T &b) const {
            return a < b;
        }
    } comp;
    timeTest(v, comp);
}

void timeTestRandom(size_t n) {
    std::vector<int> v(n);
    std::cout << "Size: " << n << std::endl;
    for (size_t i = 0; i < n; ++i)
        v[i] = rand();
    timeTest(v);
}

void timeTestPartiallySorted(size_t len, size_t cnt) {
    std::vector<int> v(len * cnt);
    std::cout << "Sizes: " << len << std::endl;
    std::cout << "Count: " << cnt << std::endl;
    for (size_t i = 0; i < cnt; ++i) {
        v[i * len] = rand() % 1000;
        for (size_t j = 1; j < len; ++j)
            v[i * len + j] = v[i * len + j - 1] + rand() % 1000;
    }
    timeTest(v);
}

struct Point {
    int x, y, z;
    Point(): x(0), y(0), z(0) {}
    Point(int x, int y, int z): x(x), y(y), z(z) {}
};

bool operator==(const Point &a, const Point &b) {
    return (a.x == b.x && a.y == b.y && a.z == b.z);
}

bool comparePoints(const Point &a, const Point &b) {
    if (a.x == b.x) {
        if (a.y == b.y)
            return a.z < b.z;
        return a.y < b.y;
    }
    return a.x < b.x;
}

bool testStructComparation(size_t n = 1000) {
    std::vector<Point> v(n), v1(n);
    for (size_t i = 0; i < n; ++i)
        v1[i] = v[i] = Point(rand(), rand(), rand());
    TimSort(v.begin(), v.end(), comparePoints);
    std::sort(v1.begin(), v1.end(), comparePoints);
    return (v == v1);
}

class StringComparator {
public:
    bool operator()(const std::string &a, const std::string &b) const {
        return a < b;
    }
};

std::string randString(size_t maxLength) {
    size_t stringLength = rand() % maxLength;
    std::string s;
    s.resize(stringLength);
    for (size_t i = 0; i < stringLength; ++i)
        s[i] = rand() % 26 + 'a';
    return s;
}

bool testStringComparation(size_t n = 1000, size_t maxLength = 100) {
    std::vector<std::string> v(n), v1(n);
    for (size_t i = 0; i < n; ++i)
        v1[i] = v[i] = randString(maxLength);
    StringComparator comp;
    TimSort(v.begin(), v.end(), comp);
    std::sort(v1.begin(), v1.end(), comp);
    return (v == v1);
}

void parametersTesting(std::vector<IParameters*> &params, size_t size) {
    std::cout << "testing " << params.size() << " variants on size " << size << ":\n";
    std::vector<int> v(size), v1(size), buf;
    for (size_t i = 0; i < size; ++i)
        v1[i] = v[i] = rand();
    sort(v1.begin(), v1.end());
    for (size_t i = 0; i < params.size(); ++i) {
        buf = v;
        elapsed();
        TimSort(buf.begin(), buf.end(), params[i]);
        std::cout << statusAlert(buf == v1) << ", " << elapsed() << "; ";
    }
    std::cout << std::endl;
}

class TestParameters: public DefaultParameters {
    unsigned minRunSize, gallop;
public:
    TestParameters(unsigned minrun, unsigned gallop): minRunSize(minrun), gallop(gallop) {}
    virtual unsigned minRun(unsigned) const {
        return minRunSize;
    }

    virtual unsigned getGallop() const {
        return 7;
    }
};

#endif //TIMSORT_TESTS_H

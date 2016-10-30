#ifndef TIMSORT_TIMSORT_H
#define TIMSORT_TIMSORT_H

#include <iostream>
#include <iterator>
#include <vector>
#include <cstdlib>
#include <algorithm>
#include "parameters.h"
#include "runs.h"
#include "stackRuns.h"

template <class RAIterator, class Comparator>
void TimSort(RAIterator first, RAIterator last, Comparator &comp, IParameters *params = nullptr) {
    bool usingDefault = false;
    if (!params) {
        params = new DefaultParameters();
    }
    int minRun = params->minRun(last - first);
    std::vector<Run<RAIterator> > stack;
    RAIterator it = first;
    while (it != last) {
        RAIterator left = it, right;
        ++it;
        if (it == last) {
            right = it;
        } else {
            if (comp(*left, *it)) {
                while (it != last && comp(*(it - 1), *it))
                    ++it;
            } else {
                while (it != last && comp(*(it - 1), *it)) {
                    ++it;
                }

                RAIterator l = left, r = it - 1;
                while (l < r)
                    std::swap(*l++, *r--);
            }
            while (it != last && (std::distance(left, it) < minRun || last - it < minRun)) {
                RAIterator r = it;
                while (r != left && comp(*r, *(r - 1)))
                    std::swap(*(r - 1), *r), --r;
                ++it;
            }
            right = it;
        }
        addRun(stack, Run<RAIterator>(left, right), comp, params);
        continue;
    }
    Run<RAIterator> run = stack.back();
    stack.pop_back();
    while (!stack.empty()) {
        run = mergeRuns(stack.back(), run, comp, params);
        stack.pop_back();
    }
    if (usingDefault)
        delete params;
}

template <class RAIterator>
void TimSort(RAIterator first, RAIterator last, IParameters* params = nullptr) {
    params = params;
    class Comparator {
    public:
        bool operator()(const typename std::iterator_traits<RAIterator>::value_type &a, const typename std::iterator_traits<RAIterator>::value_type &b) const {
            return a < b;
        }
    } comp;
    TimSort(first, last, comp, params);
}

#endif
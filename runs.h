#ifndef TIMSORT_RUNS_H
#define TIMSORT_RUNS_H

#include "sortingAlgorithms.h"

template <class RAIterator>
struct Run{
    RAIterator first, second;
    Run(): first(), second() {}
    Run(RAIterator a, RAIterator b): first(a), second(b) {}
};

template <class RAIterator>
int getRunLength(Run<RAIterator> run) {
    return std::distance(run.first, run.second);
}

template <class RAIterator, class Comparator>
Run<RAIterator> mergeRuns(const Run<RAIterator> &a, const Run<RAIterator> &b, Comparator &comp, IParameters *parameters) {
    int blockSize = round(sqrt(b.second - a.first));
    size_t redCnt = 0, blueCnt = 0;
    RAIterator it = a.first;
    while ((a.second - it) > blockSize)
        it += blockSize, ++redCnt;
    RAIterator yellowPos = it;
    int shift;
    if (b.second - b.first >= blockSize) {
        it += blockSize;
        while ((b.second - it) >= blockSize)
            it += blockSize, ++blueCnt;
        it = yellowPos + blockSize;
        for (size_t i = 0; i < blueCnt; ++i)
            swapRange(yellowPos, it, blockSize), yellowPos += blockSize, it += blockSize;
        size_t count = redCnt + blueCnt;
        SelectionSort(RangeIterator<RAIterator>(a.first, blockSize), RangeIterator<RAIterator>(yellowPos, blockSize),
                      comp);
        it = a.first;
        for (size_t i = 1; i < count; ++i) {
            bufferedMerge(it + (i - 1) * blockSize, it + i * blockSize, it + (i + 1) * blockSize, comp, yellowPos,
                          parameters);
        }
        it = a.first + (count - 1) * blockSize;
        SelectionSort(it, b.second, comp);
        shift = (b.second - it) - blockSize;
        yellowPos = b.second - blockSize;

    } else {
        SelectionSort(b.second - 2 * blockSize, b.second, comp);
        shift = blockSize;
        yellowPos = b.second - blockSize;
    }
    for (RAIterator i = a.first; i < a.first + shift; ++i)
        for (RAIterator j = i + shift; j < yellowPos; j += shift) {
            std::swap(*i, *j);
        }
    SelectionSort(a.first, a.first + shift, comp);
    bufferedMerge(a.first + blockSize, a.first + shift, yellowPos, comp, yellowPos, parameters);
    bufferedMerge(a.first, a.first + blockSize, yellowPos, comp, yellowPos, parameters);
    SelectionSort(yellowPos, b.second, comp);
    return Run<RAIterator>(a.first, b.second);
}

#endif //TIMSORT_RUNS_H

#ifndef TIMSORT_SORTINGALGORITHMS_H
#define TIMSORT_SORTINGALGORITHMS_H

#include <algorithm>
#include "parameters.h"



template <class RAIterator, class Comparator>
void bufferedMerge(RAIterator start, RAIterator mid, RAIterator finish, Comparator &comp, RAIterator bufBegin, IParameters *parameters) {
    const int gallopTrigger = parameters->getGallop();
    RAIterator bufIt = bufBegin;
    for (RAIterator it = start; it != mid; ++it, ++bufIt) {
        std::swap(*bufIt, *it);
    }
    RAIterator leftIt, rightIt, leftEnd, rightEnd;
    rightIt = mid;
    leftIt = bufBegin;
    bufIt = start;
    leftEnd = bufBegin + (mid - start);
    rightEnd = finish;
    int rgal = 0, lgal = 0;
    while (leftIt != leftEnd && rightIt != rightEnd) {
        if (lgal >= gallopTrigger || rgal >= gallopTrigger) {
            RAIterator leftFinish = leftEnd, rightFinish = rightEnd;
            if (rgal >= gallopTrigger) {
                std::swap(leftFinish, rightFinish);
                std::swap(rightIt, leftIt);
            }
            int step = 1;
            while (leftIt + step < leftFinish && comp(*(leftIt + step), *rightIt))
                step *= 2;
            step /= 2;
            while (step > 0) {
                for (int i = 0; i < step; ++i)
                    std::swap(*bufIt++, *leftIt++);
                while (step > 0 && (leftIt + step >= leftFinish || !comp(*(leftIt + step), *rightIt)))
                    step /= 2;
            }
            if (rgal >= gallopTrigger) {
                std::swap(leftFinish, rightFinish);
                std::swap(rightIt, leftIt);
            }
            lgal = 0;
            rgal = 0;
        } else {
            std::swap(*bufIt++, (comp(*leftIt, *rightIt) ? (++lgal, rgal = 0, *leftIt++) : (lgal = 0, ++rgal, *rightIt++)));
        }
    }
    while (leftIt != leftEnd)
        std::swap(*bufIt++, *leftIt++);
    while (rightIt != rightEnd)
        std::swap(*bufIt++, *rightIt++);
};

template <class RAIterator>
void swapRange(RAIterator a, RAIterator b, size_t size) {
    for (size_t i = 0; i < size; ++i) {
        std::swap(*a++, *b++);
    }
}

template <class RAIterator>
class RangeIterator: public std::iterator<std::forward_iterator_tag,
        typename std::iterator_traits<RAIterator>::value_type,
        typename std::iterator_traits<RAIterator>::difference_type,
        typename std::iterator_traits<RAIterator>::pointer,
        typename std::iterator_traits<RAIterator>::reference> {
    size_t blockSize;
    RAIterator first;
public:
    RangeIterator(RAIterator it, size_t block): blockSize(block), first(it) {}

    RangeIterator& operator++() {
        first += blockSize;
        return *this;
    }

    bool operator!=(RangeIterator<RAIterator> b) const {
        return (blockSize != b.blockSize || first != b.first);
    }

    bool operator<(RangeIterator<RAIterator> b) const {
        return first < b.first;
    }

    const RAIterator getPos() const {
        return first;
    }

    typename std::iterator_traits<RAIterator>::reference operator*() const {
        return *first;
    }

    size_t getBlock() const {
        return blockSize;
    }
};

namespace std {
    template<class RAIterator>
    void iter_swap(RangeIterator<RAIterator> a, RangeIterator<RAIterator> b) {
        swapRange(a.getPos(), b.getPos(), a.getBlock());
    }
}

template <class RAIterator, class Comparator>
void SelectionSort(RAIterator first, RAIterator last, Comparator &comp) {
    for (RAIterator i = first; i != last; ++i) {
        RAIterator minPos = i;
        for (RAIterator j = i; j != last; ++j) {
            if (comp(*j, *minPos)) {
                minPos = j;
            }
        }
        std::iter_swap(minPos, i);
    }
}


#endif //TIMSORT_SORTINGALGORITHMS_H

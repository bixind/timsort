#ifndef TIMSORT_STACKRUNS_H
#define TIMSORT_STACKRUNS_H

#include <vector>
#include "runs.h"
#include "parameters.h"

template <class RAIterator, typename Comparator>
void addRun(std::vector<Run<RAIterator> > &stack, Run<RAIterator> run, Comparator &comp, IParameters *parameters) {
    if (stack.size() == 1 && parameters->needMerge(getRunLength(stack.back()), getRunLength(run))) {
        run = mergeRuns(stack.back(), run, comp, parameters);
        stack.pop_back();
        addRun(stack, run, comp, parameters);
        return;
    }
    if (stack.size() >= 2) {
        int lenX = getRunLength(stack[stack.size() - 2]);
        int lenY = getRunLength(stack.back());
        int lenZ = getRunLength(run);
        if (parameters->whatMerge(lenX, lenY, lenZ) == WM_MergeYZ) {
            run = mergeRuns(stack.back(), run, comp, parameters);
            stack.pop_back();
            addRun(stack, run, comp, parameters);
            return;
        }

        if (parameters->whatMerge(lenX, lenY, lenZ) == WM_MergeXY) {
            Run<RAIterator> bufrun = mergeRuns(stack[stack.size() - 2], stack.back(), comp, parameters);
            stack.pop_back();
            stack.pop_back();
            addRun(stack, bufrun, comp, parameters);
            addRun(stack, run, comp, parameters);
            return;
        }
    }
    stack.push_back(run);
}

#endif //TIMSORT_STACKRUNS_H

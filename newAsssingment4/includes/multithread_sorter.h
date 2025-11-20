#ifndef MULTITHREAD_SORTER_H
#define MULTITHREAD_SORTER_H

#include "learner.h"
#include <vector>

class MultiThreadSorter {
public:
    // Sorts learners by full name using at least 2 threads
    static void parallelSort(std::vector<Learner> &arr);

private:
    static void mergeSort(std::vector<Learner> &arr, int left, int right);
    static void merge(std::vector<Learner> &arr, int left, int mid, int right);
};

#endif

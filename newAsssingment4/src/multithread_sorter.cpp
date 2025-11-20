#include "../includes/multithread_sorter.h"
#include <thread>
#include <chrono>
#include <iostream>

// ---------------- merge ----------------
void MultiThreadSorter::merge(std::vector<Learner> &arr,
                              int left, int mid, int right)
{
    std::vector<Learner> temp(right - left + 1);
    int i = left;
    int j = mid + 1;
    int k = 0;

    while (i <= mid && j <= right) {
        if (arr[i].getName() <= arr[j].getName())
            temp[k++] = arr[i++];
        else
            temp[k++] = arr[j++];
    }
    while (i <= mid) temp[k++] = arr[i++];
    while (j <= right) temp[k++] = arr[j++];

    for (int t = 0; t < k; t++)
        arr[left + t] = temp[t];
}


// ---------------- mergeSort ----------------
void MultiThreadSorter::mergeSort(std::vector<Learner> &arr,
                                  int left, int right)
{
    if (left >= right) return;

    int mid = (left + right) / 2;

    mergeSort(arr, left, mid);
    mergeSort(arr, mid + 1, right);
    merge(arr, left, mid, right);
}


// ---------------- parallelSort ----------------
void MultiThreadSorter::parallelSort(std::vector<Learner> &arr)
{
    if (arr.size() <= 1) return;

    int n = arr.size();
    int mid = n / 2;

    std::cout << "\n--- Starting parallel sort ---\n";

    // Thread 1 sorts left half
    auto t1Func = [&]() {
        auto start = std::chrono::high_resolution_clock::now();
        mergeSort(arr, 0, mid - 1);
        auto end = std::chrono::high_resolution_clock::now();

        std::cout << "Thread 1 (left half) sort time: "
                  << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()
                  << " ms\n";
    };

    // Thread 2 sorts right half
    auto t2Func = [&]() {
        auto start = std::chrono::high_resolution_clock::now();
        mergeSort(arr, mid, n - 1);
        auto end = std::chrono::high_resolution_clock::now();

        std::cout << "Thread 2 (right half) sort time: "
                  << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()
                  << " ms\n";
    };

    // Launch threads
    std::thread t1(t1Func);
    std::thread t2(t2Func);

    // Wait for both
    t1.join();
    t2.join();

    // Merge in main thread (single point, no race)
    auto startMerge = std::chrono::high_resolution_clock::now();
    merge(arr, 0, mid - 1, n - 1);
    auto endMerge = std::chrono::high_resolution_clock::now();

    std::cout << "Final merge time (main thread): "
              << std::chrono::duration_cast<std::chrono::milliseconds>(endMerge - startMerge).count()
              << " ms\n";

    std::cout << "--- Sorting complete ---\n\n";
}

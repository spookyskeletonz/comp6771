#ifndef BUCKET_SORT_H
#define BUCKET_SORT_H

#include <vector>
#include <thread>

struct BucketSort {
    
    // vector of numbers
    std::vector<unsigned int> numbersToSort;
    unsigned int numCores;
    // vector of running threads
    std::vector<std::thread> openThreads;
    unsigned int numThreads = 0;
   
    void sort(unsigned int numCores);

    //recursively bucketsort
    std::vector<unsigned int> recurseBucket(std::vector<unsigned int>, unsigned int, unsigned int);
};

#endif

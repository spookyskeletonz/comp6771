#include "BucketSort.h"

#include <algorithm>
#include <thread>
#include <iostream>
#include <cmath>
#include <string>

// TODO: replace this with a parallel version. 
void BucketSort::sort(unsigned int numCores) {
    this->numCores = numCores;
    std::string maxElem = std::to_string(*std::max_element(numbersToSort.begin(), numbersToSort.end()));
    numbersToSort = recurseBucket(numbersToSort, 0, maxElem.length());
}

std::vector<unsigned int> BucketSort::recurseBucket(std::vector<unsigned int> parentBucket, unsigned int index, unsigned int maxDepth){
    /*  base case. if there is 1 or 0 elements in bucket return bucket. if we reach maxDepth of recursion
        (which is set as the length of the longest integer in numsToSort) we return. note: if we have more than 0
        or 1 elements they are either duplicates or numbers like 40 and 400 which could end up in the same bucket.
        we call sort to put these in lexographical order, so that 400 does not appear before 40. 
        it is the only reference to sort in this algorithm
    */
    if(parentBucket.size() == 1 || parentBucket.size() == 0 || index == maxDepth){
        std::sort(parentBucket.begin(), parentBucket.end());
        return parentBucket;
    }
    /*  for each element in the parent bucket we apply this algorithm to put it in its correct child bucket.
        we have a counter of the currentIndex and compare it to the index we want to check on. while the
        currentIndex is not at the index we mod the element by its power of 10. the starting power is given by
        finding the log base 10 of the element. when we get to the index we divide it by its power of 10 instead
        this will give us the bucket to push it into. eg checking index 2 of 12345 (0th) -> 2345 (1st) 
        -> 345 (2nd))-> 3
    */
    std::vector<unsigned int> buckets[10] {std::vector<unsigned int>()};
    for(auto it = parentBucket.begin(); it != parentBucket.end(); ++it){
        unsigned int elem = *it;
        unsigned int currentIndex = 0;
        unsigned int power = std::log10(elem);
        /*  I dedicate this loop in the algorithm to Jack Cooper, a mate of mine
            whose birthday I missed to write this.
        */
        while(currentIndex != index && elem != 0){
            elem = elem % (unsigned int) std::pow(10, power);
            power--;
            currentIndex++;
        }
        if(elem != 0)elem = elem / std::pow(10, power);
        buckets[elem].push_back(*it);
    }
    /*  here we are creating threads for the top layer of bucket creation. then each of the buckets is run in each
        thread. the subsequent child buckets do not have their own threads
    */
    for(unsigned int i = 0; i < 10; i++){
        if(index == 0){
            //thread initial 10 bucket top layer creation
            if(this->numThreads < this->numCores){
                this->numThreads++;
                this->openThreads.push_back(std::thread {[&](int ti) {
                    //new thread for bucket[i]
                    buckets[ti] = recurseBucket(buckets[ti], index + 1, maxDepth);
                    this->numThreads--;
                }, i});
            }
            if(this->numThreads == this->numCores) {
                /*  wait for first thread in vector to finish. note this may not be the smallest, but waiting 
                    for one to finish has a likely probability to be faster than waiting for them all to finish 
                    since we will most likely not be choosing the largest one
                */
                this->openThreads.at(0).join();
                this->openThreads.erase(this->openThreads.begin());
            }
        } else {
            //non threaded recursion calls for after top layer
            buckets[i] = recurseBucket(buckets[i], index + 1, maxDepth);
        }
    }
    if(index == 0 && this->numThreads != 0){
        for(auto it = this->openThreads.begin(); it != this->openThreads.end(); ++it){
            it->join();
        }
    }
    //reassemble the buckets in this call into a vector and return
    std::vector<unsigned int> result;
    for(unsigned int i = 0; i < 10; i++){
        result.insert(result.end(), buckets[i].begin(), buckets[i].end());
    }
    
    return result;

}








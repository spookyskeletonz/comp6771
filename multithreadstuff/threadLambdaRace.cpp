#include <iostream>
#include <thread>

// NOTE: do not compile this with -O2 it optimises out the ++
// call and prevents the race condition from happening.

int main() {
    int i = 1;
    const long numIterations = 1000000;
    std::thread t1{[&] {
        for (int j = 0; j < numIterations; ++j) {
            i++;
        }
    }};
    std::thread t2{[&] {
        for (int j = 0; j < numIterations; ++j) {
            i--;
        }
    }};
    t1.join();
    t2.join();
    std::cout << i << std::endl;
}

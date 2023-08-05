#include <iostream>
#include <thread> 
#include <atomic> 

// https://en.cppreference.com/w/cpp/language/memory_model
// https://en.cppreference.com/w/cpp/atomic/atomic

int main(){

    std::atomic<int> counter = 0;

    auto work = [&counter](){
        for (int i=0; i<10000; i++){
            counter += 1;
        }
    };

    std::thread t1(work);
    std::thread t2(work);

    t1.join();
    t2.join();

    std::cout << "counter: " << counter << std::endl;

    return 0;
}
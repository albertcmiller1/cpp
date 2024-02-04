#include <iostream>
#include <thread> 
#include <vector> 
#include <mutex>

// https://www.youtube.com/watch?v=nSY3gXMp-ZQ&list=PLxNPSjHT5qvvIGGhRnFOGA4CbX1oTrt6z&index=42&ab_channel=CoffeeBeforeArch

int main(){

    std::mutex m;

    // lambda function 
    auto print_thread_id = [&m](int id){
        std::lock_guard<std::mutex> lg(m);
        std::cout << "printing from thread: " << id << std::endl;
        m.unlock();
    };

    std::vector<std::thread> my_threads;

    for (int i=0; i<3; i++){
        my_threads.emplace_back(print_thread_id, i);
        my_threads[i].join();
    }

    return 0;
}
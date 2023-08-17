// #include <iostream>
// #include <thread> 
// #include <atomic> 

// // https://en.cppreference.com/w/cpp/language/memory_model
// // https://en.cppreference.com/w/cpp/atomic/atomic

// int main(){

//     std::atomic<int> counter = 0;

//     auto work = [&counter](){
//         for (int i=0; i<10000; i++){
//             counter += 1;
//         }
//     };

//     std::thread t1(work);
//     std::thread t2(work);

//     t1.join();
//     t2.join();

//     std::cout << "counter: " << counter << std::endl;

//     return 0;
// }

#include <thread>
#include <iostream>
#include <vector>
#include <unistd.h>

void yello(){
    while (true){
        sleep(1);
        std::cout << "Hello00 from thread " << std::this_thread::get_id() << std::endl;
    }
}

void hello(){
    while (true){
        sleep(1);
        std::cout << "Hello from thread " << std::this_thread::get_id() << std::endl;
    }
}

int main(){
    std::vector<std::thread> threads;

    threads.push_back(std::thread(hello));
    threads.push_back(std::thread(yello));
    // for(int i = 0; i < 5; ++i){
    //     threads.push_back(std::thread(hello));
    // }

    for(auto& thread : threads){
        thread.join();
    }

    return 0;
}
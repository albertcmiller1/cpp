#include <iostream>
#include <thread> 
#include <vector> 

void print_thread_id(int id){
    std::cout << "printing from thread: " << id << std::endl;
}

int main(){
    std::vector<std::thread> my_threads;

    // std::thread t1(print_thread_id, 1);
    // // will give an error if we dont use join()
    // t1.join(); // wait for t1 to finish 


    for (int i=0; i<3; i++){
        // my_threads.push_back(print_thread_id, i);
        my_threads.emplace_back(print_thread_id, i);
        my_threads[i].join();
    }

    return 0;
}
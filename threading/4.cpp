#include <iostream>
#include <thread> 

void print_thread_id(int id){
    std::cout << "printing from thread: " << id << std::endl;
}

int main(){

    // std::thread t1(print_thread_id, 1);
    // will give an error if we dont use join()
    // t1.join(); // wait for t1 to finish 


    std::jthread t1(print_thread_id, 1);




    return 0;
}
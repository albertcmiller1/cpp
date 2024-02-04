#include <iostream>
#include <thread> 
#include <mutex> 
#include <future>

int sum = 0;
std::mutex m;

void add(int num){
    m.lock();
    for (int i=0; i<num; i++){
        sum++;
    }
    m.unlock();
}

void slow(){
    std::thread t1(add, 100000000);
    std::thread t2(add, 100000000);
    std::thread t3(add, 100000000);

    t1.join();
    t2.join();
    t3.join();
}


int add_local(int num){
    int local_sum = 0;
    for (int i=0; i<num; i++){
        local_sum++;
    }
    return local_sum;
}

void fast(){
    auto future_1 = std::async(add_local, 100000000);
    auto future_2 = std::async(add_local, 100000000);
    auto future_3 = std::async(add_local, 100000000);

    int local_1 = future_1.get();
    int local_2 = future_2.get();
    int local_3 = future_3.get();

    sum = local_1 + local_2 +local_3 ;
}

int main(){
    // slow(); // 0.631 total
    fast(); // 0.120 total

    std::cout << "sum: " << sum << std::endl;

    return 0;
}
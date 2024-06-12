#include <iostream>

// Vectors
#include <vector>
void vectors_test(){
    std::vector<int> v1;
    std::vector<int> v2 {1, 2, 3};
    std::vector<int> v3 (26); 

    v1.push_back(11);
    std::cout << v1[0] << std::endl;

    for (int i=0; i<v3.size(); i++){
        std::cout << v3[i] << std::endl;
    }

    bool is_empty = v1.empty();

    int end = v2.back();
    v2.pop_back();
}


// Sets 
#include <set>
void set_test(){
    std::set<int> s1;
    std::set<int> s2 { 1, 2, 3, 4, 5 };
    std::vector<int> v {7, 8, 9};
    std::set<int> s3 (v.begin(), v.end());

    s1.insert(69);
    s1.erase(69);

    int num_elements = s2.size();
}


// Hash Maps
#include <unordered_map>
void map_test(){
    std::unordered_map<int, int> map1;
    std::unordered_map<int, int> map2 {{1, 11}, {2, 22}};

    if (map2.count(2)){
        std::cout << map2[2] << std::endl;
    } else {
        map2[2]=22;
    }


    int size = map2.size();

    for (auto [key, val] : map2){
        std::cout << key << ": " << val << std::endl;
    }
    for (auto x: map2){
        int key = x.first;
        int val = x.second;
    }
}


// Queues 
#include <queue>
void queue_test(){
    // if we want to push and pop from both sides of the queue, need to use deque (double ended queue) instead. 
    std::queue<int> q1;
    std::deque<int> q2;

    q2.push_front(1);
    q2.push_back(2);
    int back = q2.back();
    int front = q2.front();
    q2.pop_back();
    q2.pop_front();



    q1.push(66); // push to back of queue
    q1.push(77);

    int front2 = q1.front();
    int back2 = q1.back();

    q1.pop(); // pops from left side of queue 

}


// Heaps 
// priority queue is included in the queue package. 
void test_heap(){
    // Max heap by default 
    std::priority_queue<int> heap1; // cant initialize 
    std::vector<int> arr {1, 2, 3};
    std::priority_queue<int> heap2 (arr.begin(), arr.end());

    heap1.push(11);
    heap1.push(22);
    heap1.push(33);

    int top = heap1.top();
    heap1.pop();

    bool is_empty = heap1.empty();

    int size = heap2.size();
}



// Main Entry 
int main(){
    vectors_test();
    queue_test();
    test_heap();
    // set_test();
    // map_test();
    return 0;
}

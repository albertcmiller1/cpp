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



// Main Entry 
int main(){
    vectors_test();
    // set_test();
    // map_test();
    return 0;
}
